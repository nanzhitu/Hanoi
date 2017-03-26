// fsfsfsssfs.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "stdlib.h"
#include "string.h"

typedef struct
{
	char x;
	char y;
	char z;
	int n;
}DataType;

struct Node;
typedef struct Node * PNode;
struct Node
{
DataType info;
PNode link;
};

struct LinkStack
{
	PNode top;
};
typedef struct LinkStack * PLinkStack;





/********************************************/
/*                ����ջ                    */
PLinkStack createEmptyStack_link(void)
{
    PLinkStack plstack = (PLinkStack)malloc(sizeof(struct LinkStack));
    if (plstack!=NULL)
            plstack->top = NULL;
	else
        printf("Out of Space!!!\n");
        return plstack;
}


/********************************************/
/*           �ж�ջ�Ƿ�Ϊ��ջ               */
int isEmptyStack_link(PLinkStack plstack)
{
     return (plstack->top == NULL);
}


/********************************************/
/*                 ��ջ                     */
void push_link(PLinkStack plstack, DataType x)
{
	PNode p;
	p = (PNode)malloc(sizeof(struct Node));
    if(p==NULL)
        printf("Out of Space!!!\n");
    else{
        p->info=x;
        p->link=plstack->top;
		plstack->top=p;
    }
}


/********************************************/
/*                 ��ջ                     */
void pop_link(PLinkStack plstack)
{
	PNode p;
    if(isEmptyStack_link( plstack))
        printf("Empty stack pop\n");
    else
	{
		p=plstack->top;
        plstack->top = plstack->top->link;
		free(p);
	}
}


/********************************************/
/*              ȡջ��Ԫ��                  */
DataType top_link(PLinkStack plstack)
{
    if(plstack->top ==NULL)
	{
		printf("Stack is empty!\n");
		exit(0);
	}
    else
    return(plstack->top->info);
}

/********************************************/
/*              ��ʾ�ƶ�����                */
void move(char x,char y)
{
	static int count=0;
	printf("%c-->%c",x,y);
	count++;
	if(count==4)
	{
		printf("\n");
		count=0;
	}
	else
		printf("\t");
}



/*****************************************/
/*              ��������               */
/*���������裺                           */
/*    1.��n-1��Բ����A-->B               */
/*    2.��n-1��Բ����A-->C               */
/*    3.��n-1��Բ����B-->C               */
void hanoi(char A,char B,char C,int MAX)
{
	DataType God1,God2;	
if(MAX<=0)
exit(0);
	if(MAX==1)
	{
		move(A,C);
		exit(0);
	}
	//�����ĸ�ջ
PLinkStack Ltree=createEmptyStack_link();
PLinkStack root=createEmptyStack_link();
PLinkStack Rtree=createEmptyStack_link();
PLinkStack end=createEmptyStack_link();
                                   //����ʼ����ջ
		God2.x=A;God2.y=B,God2.z=C;God2.n=MAX;
		God1.x=God2.y;God1.y=God2.x;God1.z=God2.z;God1.n=God2.n-1;
		push_link(Ltree,God1);
		God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
		push_link(root,God1);
		God1.x=God2.x;God1.y=God2.z;God1.z=God2.y;God1.n=God2.n-1;
		push_link(Rtree,God1);

while(!(isEmptyStack_link(Rtree)&&isEmptyStack_link(root)))
{
	if(!isEmptyStack_link(Ltree))
	{
		God2=top_link(Ltree);
		pop_link(Ltree);
		if(God2.n==1)
		{
			//�����ҳ�ջ����endջ
    God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
	push_link(end,God1);
    God2=top_link(root);
	pop_link(root);
	God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
	push_link(end,God1);
	God2=top_link(Rtree);
	pop_link(Rtree);
	God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
	push_link(end,God1);
	            //��ջ��һ��
				if(!isEmptyStack_link(root))
				{
					God2=top_link(root);
					pop_link(root);
					God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
					push_link(end,God1);
				}
		}
		else
		{
		//��������ջ	
        God1.x=God2.y;God1.y=God2.x;God1.z=God2.z;God1.n=God2.n-1;
		push_link(Ltree,God1);
		God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
		push_link(root,God1);
		God1.x=God2.x;God1.y=God2.z;God1.z=God2.y;God1.n=God2.n-1;
		push_link(Rtree,God1);
		}
	}
	else
	{
		//����ջһ����ͬʱ��������ջ
        God2=top_link(Rtree);
		pop_link(Rtree);
     	God1.x=God2.y;God1.y=God2.x;God1.z=God2.z;God1.n=God2.n-1;
		push_link(Ltree,God1);
		God1.x=God2.x;God1.y=God2.y;God1.z=God2.z;God1.n=God2.n;
		push_link(root,God1);
		God1.x=God2.x;God1.y=God2.z;God1.z=God2.y;God1.n=God2.n-1;
		push_link(Rtree,God1);

	}
}
		//���endջ
		while(!isEmptyStack_link(end))
		{
			God1=top_link(end);
			pop_link(end);
			move(God1.x,God1.z);
		}
}


int main(int argc, char* argv[])
{
	int MAX;
	printf("�������ʼջ��Ԫ�ظ�����");
	scanf("%d",&MAX);

if(MAX%2==1)
hanoi('A','C','B',MAX);
else
hanoi('A','B','C',MAX);
	return 0;
}

