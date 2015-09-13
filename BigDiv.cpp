#include<iostream>
using namespace std;

#define SIZE 100
#define K 1000
class BigInt
{
public:
	BigInt(char * S)
	{
		len=strlen(S);
		for(int i=0;i<SIZE;++i)num[i]=0;
		for(int i=0;i<len;++i)num[len-i-1]=S[i]-'0';
	}	
	void print()
	{
		for(int i=len-1;i>=0;--i)
			cout<<num[i];
		cout<<endl;
	}
private:
	void Ins(int cur=0)
	{
		//在指定位上加一
		int carry=1;
		while(carry!=0||cur<len)
		{
			num[cur]+=carry;
			carry=num[cur]/10;
			num[cur++]%=10;
		}
		len=cur;
	}
	bool Sub(const BigInt& x,int cur=0)
	{
		if(len-cur<=x.len)
			for(int i=x.len-1;i>=0;--i)
			{
				if(num[cur+i]<x.num[i])return false;
				if(num[cur+i]>x.num[i])break;;
			}
		int brrow=0,cur_x=0;
		while(brrow!=0||cur<len)
		{
			int flag=(num[cur]<x.num[cur_x]+brrow)?1:0;
			num[cur]+=(10*flag-brrow-x.num[cur_x]);
			brrow=flag;
			++cur;++cur_x;
		}
		len=cur;
		while(num[len-1]==0)len--;
		return true;
	}
public:
	void Div(const BigInt& x,BigInt& ANS)
	{
		//A/B,A为余数,ANS为商
		int cur=len-1;
		while(cur>=0)
		{
			while(Sub(x,cur))
				ANS.Ins(cur);
			cur--;
		}
	}
private:
	int len;
	int num[SIZE];
};

int main(int argc,char* argv[])
{
	BigInt A("23");
	BigInt B("23");
	BigInt C("0");
	A.Div(B,C);
	C.print();
	A.print();
	system("pause");
	return 0;
}