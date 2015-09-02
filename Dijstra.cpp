#include <iostream>
#include <queue>
#include <algorithm>
#include <iterator>
using namespace std;
#define INF 0xFFFF
#define N 10
int MAP[N][N];
int pv[N],dv[N];
bool know[N];

void InitMap()
{
	for(int i=0;i<N;++i)
	{
		pv[i]=0;
		dv[i]=INF;
		know[i]=false;
		for(int j=0;j<N;++j)
			MAP[i][j]=INF;
	}
}

void InitUnweight()
{
	MAP[1][2]=2;MAP[1][4]=1; 
	MAP[2][4]=3;MAP[2][5]=10;
	MAP[3][1]=4;MAP[3][6]=5;
	MAP[4][3]=2;MAP[4][6]=8;MAP[4][7]=4;MAP[4][5]=2;
	MAP[5][7]=6;
	MAP[7][6]=1;
}

void unWeight(int s,int n)
{
	queue<int> q;
	dv[s]=0;
	q.push(s);
	while(q.empty()==false)
	{
		int v=q.front();
		q.pop();
		for(int u=1;u<=n;++u)
		{
			if(MAP[v][u]!=INF&&dv[u]==INF)
			{
				dv[u]=dv[v]+1;
				pv[u]=v;
				q.push(u);
			}
		}
	}
}
void Dijstra(int s,int n)
{
	int v;dv[s]=0;
	while(true)
	{
		v=0;
		for(int i=1;i<=n;++i)
			if(dv[i]<dv[v]&&know[i]==false)
				v=i;
		if(dv[v]==INF)break;
		for(int u=1;u<=n;++u)
		{
			if(MAP[v][u]!=INF&&know[u]==false&&dv[u]>dv[v]+MAP[v][u])
			{
				dv[u]=dv[v]+MAP[v][u];
				pv[u]=v;
			}
		}
		know[v]=true;
	}
}
void Print(int dist)
{
	if(dist==0)
	{
		cout<<"END\n";
		return;
	}
	else
		cout<<dist<<"->";
	Print(pv[dist]);
}

int main(int argc,char* argv[])
{
	InitMap();
	InitUnweight();
	Dijstra(1,7);
	Print(1);
	Print(2);

	Print(4);
	Print(5);
	Print(6);
	Print(7);
	copy(dv,dv+7,ostream_iterator<int>(cout," "));
	cout<<"\n";
	system("pause");
	return 0;
}
