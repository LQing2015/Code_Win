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
	//常规方法,考虑链表的先驱
	//这样就要考虑head被删除时候的情形
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
	//不考虑先驱,实际删除时总是将被删除节点覆盖,同时删除它后面的一个节点
	//这样可以不用考虑头节点被删除的情况!!但是要考虑,最后一个节点被删除的情况
	//ps:注意删除最后一个节点,
	
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
