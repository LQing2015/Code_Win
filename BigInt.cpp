#include<iostream>
using namespace std;

#define SIZE 1000

const int K=10;

struct LargeInt
{
	int num[SIZE];
	int length;
	LargeInt(char * x):length(0)
	{
		length=strlen(x);
		for(int i=SIZE-1;i>=0;--i)num[i]=0;
		for(int i=length-1;i>=0;--i)num[length-i-1]=x[i]-'0';
		
	}
};
void PRINTBigInt(LargeInt x)
{
	for(int i=x.length-1;i>=0;--i)
		cout<<x.num[i];
	cout<<endl;
}
void Clear(LargeInt & x)
{
	for(int i=SIZE-1;i>=0;--i)x.num[i]=0;
}
void Increase(LargeInt& A)
{
	int carry=1,cur=0;
	while(cur<A.length||carry!=0)
	{
		A.num[cur]+=carry;
		carry=A.num[cur]/K;
		A.num[cur]%=K;
		cur++;
	}
	A.length=cur;
}
void Add(LargeInt& A,LargeInt& B,LargeInt& C)
{
	int carry=0,cur=0;
	while(carry!=0||cur<A.length||cur<B.length)
	{
		C.num[cur]=A.num[cur]+B.num[cur]+carry;
		carry=C.num[cur]/K;
		C.num[cur]%=K;
		cur++;
	}
	C.length=cur;
}
bool Sub(LargeInt& A,LargeInt& B,LargeInt& C)
{
	if(A.length<=B.length)
		for(int i=B.length-1;i>=0;--i)
			if(A.num[i]<B.num[i])
				return false;
	int brrow=0,cur=0;
	while(brrow!=0||cur<A.length)
	{
		int tmp=(A.num[cur]<B.num[cur]+brrow)?1:0;
		 C.num[cur]=A.num[cur]+K*tmp-B.num[cur]-brrow;
		 brrow=tmp;
		 cur++;
	}
	while(C.num[cur-1]==0)cur--;
	C.length=cur;
	return true;
}
void Mul(const LargeInt& A,const LargeInt& B,LargeInt& C)
{
	int cur=0;
	Clear(C);
	while(cur<B.length)
	{
		int carry=0,i=0;
		while(carry!=0||i<A.length)
		{
			C.num[i+cur]+=(A.num[i]*B.num[cur]+carry);
			carry=C.num[i+cur]/10;
			C.num[i+cur]%=K;
			++i;
		}
		C.length=cur+i;
		cur++;
	}
}
void Div(LargeInt& A,LargeInt& B,LargeInt& C,LargeInt& D)
{
	LargeInt one("1");
	D=A;
	while(Sub(D,B,D))
		Add(C,one,C);
}
void Factorial(int N,LargeInt& ANS)
{
	Clear(ANS);
	LargeInt I("1"),TMP("1");
	for(int i=1;i<=N;++i)
	{
		Mul(TMP,I,ANS);
		Increase(I);
		TMP=ANS;
	}
}
int main(int argc,char* argv[])
{
	LargeInt A("0");
	Factorial(14,A);
	PRINTBigInt(A);
	system("pause");
	return 0;
} 