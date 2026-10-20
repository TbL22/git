//顺序栈、链栈的基本操作及进制转换
#include<iostream>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0
#define MAXSIZE 100

typedef struct{
    int *base;
    int *top;
    int stacksize;
}SqStack;

typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*LinkStack;

Status InitStack(SqStack &S){
    S.base=new int[MAXSIZE];
    S.top=S.base;
    S.stacksize=MAXSIZE;
    return Ok;
}

Status GetTop(SqStack S,int &e){
    if(S.base==NULL||S.top==S.base)
        return ERROR;
    e=*(S.top-1);
    return Ok;
}

Status Push(SqStack &S,int e){
    if(S.base==NULL||S.top-S.base==S.stacksize)
        return ERROR;
    *S.top=e;
    S.top++;
    return Ok;
}

Status Pop(SqStack &S,int &e){
    if(GetTop(S,e)==ERROR)
        return ERROR;
    S.top--;
    return Ok;
}

Status DestroyStack(SqStack &S){
    delete[] S.base;
    S.base=NULL;
    S.top=NULL;
    S.stacksize=0;
    return Ok;
}

Status InitLinkStack(LinkStack &S){
    S=NULL;
    return Ok;
}

Status GetLinkTop(LinkStack S,int &e){
    if(S==NULL)
        return ERROR;
    e=S->date;
    return Ok;
}

Status LinkPush(LinkStack &S,int e){
    LNode *p=new LNode;
    p->date=e;
    p->next=S;
    S=p;
    return Ok;
}

Status LinkPop(LinkStack &S,int &e){
    if(GetLinkTop(S,e)==ERROR)
        return ERROR;
    LNode *p=S;
    S=S->next;
    delete p;
    return Ok;
}

Status DestroyLinkStack(LinkStack &S){
    LNode *p;
    while(S!=NULL){
        p=S;
        S=S->next;
        delete p;
    }
    return Ok;
}

//除以进制取余数，余数依次入栈，再逆序出栈
Status Conversion(int n,int d){
    if(n<0||d<2||d>16)
        return ERROR;
    SqStack S;
    InitStack(S);
    int e;
    do{
        if(Push(S,n%d)==ERROR){
            DestroyStack(S);
            return ERROR;
        }
        n=n/d;
    }while(n!=0);
    cout<<"与其等值的"<<d<<"进制数是：";
    while(Pop(S,e)==Ok){
        if(e<10)
            cout<<e;
        else
            cout<<char('A'+e-10);
    }
    cout<<endl;
    DestroyStack(S);
    return Ok;
}

int main(){
    SqStack S;
    LinkStack L;
    int a[5]={2,14,8,32,24};
    int b[5]={12,4,18,7,32};
    int i,e,n,d;
    cout<<"===== 测试顺序栈基本操作 ====="<<endl;
    InitStack(S);
    for(i=0;i<5;i++)
        Push(S,a[i]);
    GetTop(S,e);
    cout<<"顺序栈栈顶元素："<<e<<endl;
    cout<<"顺序栈出栈元素：";
    while(Pop(S,e)==Ok)
        cout<<e<<" ";
    cout<<endl;
    DestroyStack(S);

    cout<<"===== 测试链栈基本操作 ====="<<endl;
    InitLinkStack(L);
    for(i=0;i<5;i++)
        LinkPush(L,b[i]);
    GetLinkTop(L,e);
    cout<<"链栈栈顶元素："<<e<<endl;
    cout<<"链栈出栈元素：";
    while(LinkPop(L,e)==Ok)
        cout<<e<<" ";
    cout<<endl;
    DestroyLinkStack(L);

    cout<<"===== 进制转换 ====="<<endl;
    cout<<"输入一个非负十进制数：";
    if(!(cin>>n)){
        cout<<"输入错误！"<<endl;
        return 0;
    }
    cout<<"输入一个想要转换为的进制：";
    if(!(cin>>d)){
        cout<<"输入错误！"<<endl;
        return 0;
    }
    if(Conversion(n,d)==ERROR)
        cout<<"输入错误，十进制数应非负，进制应在2到16之间！"<<endl;
    return 0;
}
