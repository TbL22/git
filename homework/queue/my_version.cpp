//实验4：循环队列和链队列的实现
#include<iostream>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0
#define MAXSIZE 100

typedef struct{
    int date[MAXSIZE];
    int front;
    int rear;
}CircularQueue;

typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*QueuePtr;

typedef struct{
    QueuePtr front;
    QueuePtr rear;
}LinkedQueue;

Status InitCircularQueue(CircularQueue &Q){
    Q.front=0;
    Q.rear=0;
    return Ok;
}

bool IsEmptyCircular(CircularQueue &Q){
    return Q.front==Q.rear;
}

bool IsFullCircular(CircularQueue &Q){
    //留出一个空位置，用于区分队空和队满
    return (Q.rear+1)%MAXSIZE==Q.front;
}

Status GetHeadCircular(CircularQueue &Q,int &e){
    if(IsEmptyCircular(Q))
        return ERROR;
    e=Q.date[Q.front];
    return Ok;
}

Status EnCircularQueue(CircularQueue &Q,int e){
    if(IsFullCircular(Q))
        return ERROR;
    Q.date[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXSIZE;
    return Ok;
}

//沿用实验文件中的函数名LinkPop，完成循环队列出队
Status LinkPop(CircularQueue &Q,int &e){
    if(GetHeadCircular(Q,e)==ERROR)
        return ERROR;
    Q.front=(Q.front+1)%MAXSIZE;
    return Ok;
}

int QueueLength(CircularQueue &Q){
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

Status InitLinkedQueue(LinkedQueue &Q){
    Q.front=new LNode;
    Q.front->next=NULL;
    Q.rear=Q.front;
    return Ok;
}

bool IsEmptyLinked(LinkedQueue &Q){
    return Q.front==Q.rear;
}

Status GetHeadLinked(LinkedQueue &Q,int &e){
    if(Q.front==NULL||IsEmptyLinked(Q))
        return ERROR;
    e=Q.front->next->date;
    return Ok;
}

Status EnLinkedQueue(LinkedQueue &Q,int e){
    if(Q.front==NULL)
        return ERROR;
    LNode *p=new LNode;
    p->date=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return Ok;
}

Status DeLinkedQueue(LinkedQueue &Q,int &e){
    if(GetHeadLinked(Q,e)==ERROR)
        return ERROR;
    LNode *p=Q.front->next;
    Q.front->next=p->next;
    //删去最后一个元素后，队尾重新指向头结点
    if(Q.rear==p)
        Q.rear=Q.front;
    delete p;
    return Ok;
}

Status DestroyLinkedQueue(LinkedQueue &Q){
    int e;
    while(DeLinkedQueue(Q,e)==Ok);
    //元素全部出队后，再释放头结点
    delete Q.front;
    Q.front=NULL;
    Q.rear=NULL;
    return Ok;
}

int main(){
    CircularQueue Q;
    LinkedQueue L;
    int a[4]={15,8,23,14};
    int b[4]={18,5,36,24};
    int i,e;

    cout<<"===== 循环队列测试 ====="<<endl;
    InitCircularQueue(Q);
    cout<<"入队元素：";
    for(i=0;i<4;i++){
        EnCircularQueue(Q,a[i]);
        if(i!=0)
            cout<<", ";
        cout<<a[i];
    }
    cout<<endl;
    if(GetHeadCircular(Q,e)==Ok)
        cout<<"当前队头元素："<<e<<endl;
    if(LinkPop(Q,e)==Ok)
        cout<<"出队元素："<<e<<endl;
    if(GetHeadCircular(Q,e)==Ok)
        cout<<"当前队头元素："<<e<<endl;
    cout<<"当前队列长度："<<QueueLength(Q)<<endl;
    cout<<"===== 循环队列测试结束 ====="<<endl;
    cout<<endl;

    cout<<"===== 链队列测试 ====="<<endl;
    InitLinkedQueue(L);
    cout<<"入队元素：";
    for(i=0;i<4;i++){
        EnLinkedQueue(L,b[i]);
        if(i!=0)
            cout<<", ";
        cout<<b[i];
    }
    cout<<endl;
    if(GetHeadLinked(L,e)==Ok)
        cout<<"当前队头元素："<<e<<endl;
    if(DeLinkedQueue(L,e)==Ok)
        cout<<"出队元素："<<e<<endl;
    if(GetHeadLinked(L,e)==Ok)
        cout<<"当前队头元素："<<e<<endl;
    DestroyLinkedQueue(L);
    cout<<"===== 链队列测试结束 ====="<<endl;
    return 0;
}
