#include <iostream>
#include <algorithm>
using namespace std;

#define N 15
#define REP(i,b,e) for(int (i)=(b);(i)<(e);++(i))

int P[N];
//KMP
void next_p(char* str,int * P)
{
	int k=-1,i=0;P[0]=-1;
	while(i<strlen(str))
	{
		if(k==-1||str[k]==str[i])
		{
			++i,++k;
			P[i]=k;
		}else
			k=P[k];
	}
}
char* KMP(char *str,char* sub)
{
	int i=0,j=0;
	next_p(sub,P);
	while(i!=strlen(str)&&j!=strlen(sub))
	{
		if(j==-1||str[i]==sub[j])
			++i,++j;
		else
			j=P[j];
	}
	return j==strlen(sub)?str+i-j:NULL;
}
int main(int argc,char *argv[])
{
	char str[]="asdfghjkl";
	cout<<str<<endl;
	cout<<KMP(str,"fg")<<endl;
	system("pause");
	return 0;
}
