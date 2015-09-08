#include <tchar.h>
#include<Windows.h>
#include<iostream>
#include <process.h>
class CQueue
{
public:
	struct ELEMENT  
	{
		//表示请求的线程,和请求号
		int m_nTreadNum,m_nRequestNum;
	};
	typedef ELEMENT* PELEMENT;
private:
	PELEMENT m_pElements;
	int m_nMaxElements;
	HANDLE m_h[2];
	HANDLE &m_hmtxQ;//互斥量
	HANDLE &m_hsemNumElements;//信号量 
public:
	CQueue(int m_num):m_hmtxQ(m_h[0]),m_hsemNumElements(m_h[1])
	{
		m_pElements=(PELEMENT)HeapAlloc(GetProcessHeap(),0,sizeof(ELEMENT)*m_num);
		m_nMaxElements=m_num;
		m_hmtxQ=CreateMutex(NULL,FALSE,NULL);//初始化互斥量,False表示初始化线程并非初始拥有者
		m_hsemNumElements=CreateSemaphore(NULL,0,m_num,NULL);//当前资源数为0,因为队列中还没用元素可以出队
	}
	~CQueue()
	{
		CloseHandle(m_hmtxQ);
		CloseHandle(m_hsemNumElements);
		HeapFree(GetProcessHeap(),0,m_pElements);
	}
	BOOL Append(PELEMENT m_pElement,DWORD dwTimeout)
	{
		BOOL fok=FALSE;//表示信号量
		DWORD dw=WaitForSingleObject(m_hmtxQ,dwTimeout);
		if(dw==WAIT_OBJECT_0)
		{
			LONG lPrevCount;//之前拥有的资源数
			fok=ReleaseSemaphore(m_hsemNumElements,1,&lPrevCount);
			if(fok)
				m_pElements[lPrevCount]=*m_pElement;//有必要的话可以定义一个Copy
			else
				SetLastError(ERROR_DATABASE_FULL);
			ReleaseMutex(m_hmtxQ);
		}
		else
			SetLastError(ERROR_TIMEOUT);
		return fok;	
	}
	BOOL Remove(PELEMENT pElement,DWORD dwTimeout)
	{
		BOOL fok=(WaitForMultipleObjects(_countof(m_h),m_h,TRUE,dwTimeout)==WAIT_OBJECT_0);
		if(fok)
		{
			*pElement=m_pElements[0];
			MoveMemory(&m_pElements[0],&m_pElements[1],sizeof(ELEMENT)*(m_nMaxElements-1));
			ReleaseMutex(m_hmtxQ);
		}else
			SetLastError(ERROR_TIMEOUT);
		return fok;
	}

};

CQueue mqueue(10);

BOOL volatile g_shutDown=FALSE;
unsigned int __stdcall InputThread(void* pvParam)
{
	int ThreadNum=*((int*)pvParam);
	CQueue::ELEMENT e={ThreadNum,0};
	BOOL fok=FALSE;
	int req=0;
	while(!g_shutDown)
	{
		e.m_nRequestNum=req;
		fok=mqueue.Append(&e,1000);
		if(fok)
		{
			printf("InputThread %d:  %d\n",ThreadNum,e.m_nRequestNum);
			++req;
		}
		else
		{
			printf("InputThread %d:  Failed\n");
			Sleep(10000);	
		}
		
	}
	printf("Client  %d closed\n",ThreadNum);
	return 0;
}

unsigned int __stdcall OuputThread(void* pvParam)
{
	int ServerNum=*((int*)(pvParam));
	BOOL fok=FALSE;
	while(!g_shutDown)
	{
		CQueue::ELEMENT e;
		fok=mqueue.Remove(&e,1000);
		if(fok)
			printf("Sever %d :  %d:%d\n",ServerNum,e.m_nTreadNum,e.m_nRequestNum);
		Sleep(700);
	}
	printf("Server  %d closed\n",ServerNum);
	return 0;
}

int main(int argc,char* argv[])
{
	CQueue mqueue(10);
	int ClentID0=0,ClentID1=1;
	int ServerID=0;
	HANDLE chThread[3];
	chThread[0]=(HANDLE)_beginthreadex(NULL,0,InputThread,(void*)&ClentID0,0,NULL);
	chThread[1]=(HANDLE)_beginthreadex(NULL,0,InputThread,(void*)&ClentID1,0,NULL);
	chThread[2]=(HANDLE)_beginthreadex(NULL,0,OuputThread,(void*)&ServerID,0,NULL);
	getchar();
	g_shutDown=TRUE;
	WaitForMultipleObjects(3,chThread,TRUE,INFINITE);
	printf("CLOSE ALL\n");
	system("pause");
	return 0;
}