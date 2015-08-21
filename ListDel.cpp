#include <iostream>
#include <algorithm>
using namespace std;

#define N 15
#define REP(i,b,e) for(int (i)=(b);(i)<(e);++(i))

struct node
{
	int v;
	node *next;
};

node* build(int n)
{
	node* cur,*head=NULL,*prev=NULL;
	REP(i,0,n)
	{
		cur=(node*)malloc(sizeof(node));
		cur->v=i;cur->next=NULL;
		if(head==NULL)
			head=prev=cur;
		else
		{
			prev->next=cur;
			prev=cur;
		}
	}
	return head;
}

void print(node* head)
{
	while(head!=NULL)
	{
		printf("%d%s",head->v,(head->next==NULL)?("\n"):" -> ");
		head=head->next;
	}
}

void delete_node(node* &head,int v)
{
	//���淽��,�������������
	//������Ҫ����head��ɾ��ʱ�������
	node* prev=NULL,*cur=head;
	while(cur!=NULL)
	{
		if(cur->v==v)
		{
			node* d_node=cur;
			if(prev==NULL)
				head=cur->next;
			else
				prev->next=cur->next;
			cur=cur->next;
			free(d_node);
		}else
		{
			prev=cur;
			cur=cur->next;
		}
	}
}

void delete_node2(node* head,int v)
{
	//����������,ʵ��ɾ��ʱ���ǽ���ɾ���ڵ㸲��,ͬʱɾ���������һ���ڵ�
	//�������Բ��ÿ���ͷ�ڵ㱻ɾ�������!!����Ҫ����,���һ���ڵ㱻ɾ�������
	//ps:ע��ɾ�����һ���ڵ�,
	
}

int main(int argc,char *argv[])
{
	node* head=build(10);
	print(head);
	delete_node2(head,9);
	print(head);
	system("pause");
	return 0;
}
