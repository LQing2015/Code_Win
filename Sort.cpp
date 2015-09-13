#include <iostream>
#include <algorithm>
using namespace std;

#define N 15
#define REP(i,b,e) for(int (i)=(b);(i)<(e);++(i))
//几种排序
void QSort(int* arr,int p1,int p2)
{
	if(p1<p2)
	{
		int i=p1,j=p2;
		while(i!=j)
		{
			while(j!=i&&arr[j]>=arr[p1])--j;
			while(i!=j&&arr[i]<=arr[p1])++i;
			if(i<j)swap(arr[i],arr[j]);
		}
		swap(arr[i],arr[p1]);
		QSort(arr,p1,i-1);
		QSort(arr,i+1,p2);
	}
}
void bubleSort(int* arr,int n)
{
	for(int j=n;j>0;--j)
		for(int i=1;i<j;++i)
			if(arr[i]<arr[i-1])
				swap(arr[i],arr[i-1]);
}
void insertSort(int *arr,int n)
{
	for(int k=1;k<n;k++)
		for(int j=k;j>0;--j)
			if(arr[j]<arr[j-1])
				swap(arr[j],arr[j-1]);
			else
				break;
}
void selectSort(int *arr,int n)
{
	int min_Index=0;
	for(int i=0;i<n;++i)
	{
		min_Index=i;
		for(int j=i;j<n;++j)
			if(arr[min_Index]>arr[j])
				min_Index=j;
		swap(arr[min_Index],arr[i]);
	}
}
//归并
void merge(int* arr,int p1,int p2,int *buf )
{
	if(p1<p2)
	{
		int mid=(p1+p2)/2,i=p1,j=mid+1,k=p1;
		merge(arr,p1,mid,buf);
		merge(arr,mid+1,p2,buf);
		while(i<=mid&&j<=p2)
			buf[k++]=(arr[i]<arr[j])?arr[i++]:arr[j++];
		while(i<=mid)
			buf[k++]=arr[i++];
		while(j<=p2)
			buf[k++]=arr[j++];
		for(int kk=p1;kk<=p2;++kk)
			arr[kk]=buf[kk];
	}
}
void mergeSort(int* arr,int n)
{
	int * buf=(int* )malloc(n*sizeof(int));
	merge(arr,0,n-1,buf);
	free(buf);
}
//希尔排序
void ShellSort(int* arr,int n)
{
	int offset=n/2;
	while(offset>0)
	{
		for(int k=0;k<offset;++k)
		{
			//下面对第k组进行插入排序!
			for(int i=k+offset;i<n;i+=offset)
				for(int j=i;j>0;j-=offset)
					if(arr[j-offset]>arr[j])
						swap(arr[j],arr[j-offset]);
					else
						break;
		}
		offset/=2;
	}
}
int main(int argc,char* argv[])
{
	int num[N];
	REP(i,0,N) num[i]=i;
	//快排
	cout<<"快排: ";
	random_shuffle(num,num+N);
	QSort(num,0,N-1);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	//冒泡
	cout<<"冒泡: ";
	random_shuffle(num,num+N);
	bubleSort(num,N);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	//插入
	cout<<"插入: ";
	random_shuffle(num,num+N);
	insertSort(num,N);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	//选择
	cout<<"选择: ";
	random_shuffle(num,num+N);
	selectSort(num,N);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	//归并
	cout<<"归并: ";
	random_shuffle(num,num+N);
	mergeSort(num,N);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	//Shell
	cout<<"Shell: ";
	random_shuffle(num,num+N);
	ShellSort(num,N);
	REP(i,0,N)printf("%d%c",num[i],(i==N-1)?'\n':' ');
	system("pause");
	return 0;
}