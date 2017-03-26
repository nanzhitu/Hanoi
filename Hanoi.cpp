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
/*                创建栈                    */
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
/*           判断栈是否为空栈               */
int isEmptyStack_link(PLinkStack plstack)
{
     return (plstack->top == NULL);
}


/********************************************/
/*                 进栈                     */
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
/*                 出栈                     */
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
/*              取栈顶元素                  */
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
/*              显示移动函数                */
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
/*              主处理函数               */
/*核心三步骤：                           */
/*    1.将n-1个圆盘有A-->B               */
/*    2.将n-1个圆盘有A-->C               */
/*    3.将n-1个圆盘有B-->C               */
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
	//创建四个栈
PLinkStack Ltree=createEmptyStack_link();
PLinkStack root=createEmptyStack_link();
PLinkStack Rtree=createEmptyStack_link();
PLinkStack end=createEmptyStack_link();
                                   //给初始并进栈
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
			//左中右出栈，入end栈
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
	            //中栈出一个
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
		//左中右入栈	
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
		//出右栈一个，同时左中右入栈
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
		//输出end栈
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
	printf("请输入初始栈中元素个数：");
	scanf("%d",&MAX);

if(MAX%2==1)
hanoi('A','C','B',MAX);
else
hanoi('A','B','C',MAX);
	return 0;
}

