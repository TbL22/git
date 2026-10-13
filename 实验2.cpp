//实验2：有序单链表的归并运算
#include<iostream>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0

typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*LinkList;

Status InitList(LinkList &L){
    L=new LNode;
    L->next=NULL;
    return Ok;
}

//头插法：输入顺序与链表顺序相反
Status CreateListHead(LinkList &L,int n){
    if(L==NULL||n<0)
        return ERROR;
    for(int i=0;i<n;i++){
        LNode *p=new LNode;
        if(!(cin>>p->date)){
            delete p;
            return ERROR;
        }
        p->next=L->next;
        L->next=p;
    }
    return Ok;
}

//尾插法：输入顺序与链表顺序相同
Status CreateListTail(LinkList &L,int n){
    if(L==NULL||n<0)
        return ERROR;
    LNode *r=L;
    while(r->next!=NULL)
        r=r->next;
    for(int i=0;i<n;i++){
        LNode *p=new LNode;
        if(!(cin>>p->date)){
            delete p;
            return ERROR;
        }
        p->next=NULL;
        r->next=p;
        r=p;
    }
    return Ok;
}

LNode *LocateElem(LinkList L,int e){
    if(L==NULL)
        return NULL;
    LNode *p=L->next;
    while(p!=NULL&&p->date!=e)
        p=p->next;
    return p;
}

LNode *GetElem(LinkList L,int i){
    if(L==NULL||i<1)
        return NULL;
    LNode *p=L->next;
    int j=1;
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    return p;
}

Status ListInsert(LinkList &L,int i,int e){
    if(L==NULL||i<1)
        return ERROR;
    LNode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return ERROR;
    LNode *s=new LNode;
    s->date=e;
    s->next=p->next;
    p->next=s;
    return Ok;
}

Status ListDelete(LinkList &L,int i,int &e){
    if(L==NULL||i<1)
        return ERROR;
    LNode *p=L;
    int j=0;
    while(p!=NULL&&j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL||p->next==NULL)
        return ERROR;
    LNode *q=p->next;
    e=q->date;
    p->next=q->next;
    delete q;
    return Ok;
}

Status DestroyList(LinkList &L){
    while(L!=NULL){
        LNode *p=L;
        L=L->next;
        delete p;
    }
    return Ok;
}

void PrintList(LinkList L){
    if(L==NULL){
        cout<<endl;
        return;
    }
    LNode *p=L->next;
    while(p!=NULL){
        cout<<p->date<<" ";
        p=p->next;
    }
    cout<<endl;
}

//La、Lb均须升序，Lc调用前为NULL，三个链表变量须不同
//归并直接使用原结点，结束后La、Lb置空，由Lc管理全部结点
Status MergeList(LinkList &La,LinkList &Lb,LinkList &Lc){
    if(La==NULL||Lb==NULL||La==Lb||Lc!=NULL)
        return ERROR;
    LNode *pa=La->next;
    LNode *pb=Lb->next;
    Lc=La;
    LNode *pc=Lc;
    while(pa!=NULL&&pb!=NULL){
        if(pa->date<=pb->date){
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else{
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    if(pa!=NULL)
        pc->next=pa;
    else
        pc->next=pb;
    delete Lb;
    La=NULL;
    Lb=NULL;
    return Ok;
}

int main(){
    LinkList La=NULL,Lb=NULL,Lc=NULL;
    InitList(La);
    InitList(Lb);
    int n,e;

    cout<<"===== 建立单链表 La（头插法） ====="<<endl;
    cout<<"请输入链表中节点数量：";
    cin>>n;
    if(!cin||n<0){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"请输入 "<<n<<" 个元素（降序输入，头插后升序）：";
    if(CreateListHead(La,n)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"La 的元素：";
    PrintList(La);

    cout<<"===== 建立单链表 Lb（尾插法） ====="<<endl;
    cout<<"请输入链表中节点数量：";
    cin>>n;
    if(!cin||n<0){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"请输入 "<<n<<" 个元素（升序输入，尾插后升序）：";
    if(CreateListTail(Lb,n)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"Lb 的元素：";
    PrintList(Lb);

    cout<<"===== 测试查找操作（按值查找） ====="<<endl;
    cout<<"请输入想要在单链表 La 中查找的值：";
    if(!(cin>>e)){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    LNode *p=LocateElem(La,e);
    if(p!=NULL)
        cout<<"元素 "<<e<<" 在 La 中找到，值为："<<p->date<<endl;
    else
        cout<<"元素 "<<e<<" 在 La 中未找到"<<endl;

    cout<<"===== 测试查找操作（按位置查找） ====="<<endl;
    p=GetElem(La,2);
    if(p!=NULL)
        cout<<"La 第 2 个元素为："<<p->date<<endl;
    else
        cout<<"La 中不存在第 2 个元素"<<endl;

    //按照实验用例，在第2个位置插入10，再删除第3个元素
    cout<<"===== 测试插入操作 ====="<<endl;
    if(ListInsert(La,2,10)==Ok){
        cout<<"插入成功，La 的新元素：";
        PrintList(La);
    }
    else
        cout<<"插入失败，位置无效"<<endl;

    cout<<"===== 测试删除操作 ====="<<endl;
    if(ListDelete(La,3,e)==Ok){
        cout<<"删除成功，La 的新元素：";
        PrintList(La);
    }
    else
        cout<<"删除失败，位置无效"<<endl;

    cout<<"===== 归并 La 和 Lb ====="<<endl;
    if(MergeList(La,Lb,Lc)==Ok){
        cout<<"归并后的 Lc 元素：";
        PrintList(Lc);
    }
    else
        cout<<"归并失败"<<endl;

    DestroyList(La);
    DestroyList(Lb);
    DestroyList(Lc);
    return 0;
}
