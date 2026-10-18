//实验2：有序单链表的归并运算
#include<iostream>
#include<new>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0
typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*LinkList;

Status InitLIst(LinkList &L){//初始化带头结点的单链表
    L=new(nothrow) LNode;
    if(L==NULL)
        return ERROR;
    L->next=NULL;
    return Ok;
}

Status CreateList(LinkList L,int n,int way){//way为1时头插，为2时尾插
    if(L==NULL || L->next!=NULL || n<0 || (way!=1 && way!=2))
        return ERROR;
    LNode *r=L;
    for(int i=0;i<n;i++){
        LNode *p=new(nothrow) LNode;
        if(p==NULL)
            return ERROR;
        if(!(cin>>p->date)){
            delete p;
            return ERROR;
        }
        if(way==1){//头插法，输入顺序与链表顺序相反
            p->next=L->next;
            L->next=p;
        }
        else{//尾插法，输入顺序与链表顺序相同
            p->next=NULL;
            r->next=p;
            r=p;
        }
    }
    return Ok;
}

LNode* LocateElem(LinkList L,int e){//按值查找，返回第一个匹配的结点
    if(L==NULL)
        return NULL;
    LNode *p=L->next;
    while(p!=NULL){
        if(p->date==e)
            return p;
        p=p->next;
    }
    return NULL;
}

LNode* GetElem(LinkList L,int i){//按位置查找，位置从1开始
    if(L==NULL || i<1)
        return NULL;
    LNode *p=L->next;
    int j=1;
    while(p!=NULL && j<i){
        p=p->next;
        j++;
    }
    return p;
}

Status ListInsert(LinkList L,int i,int e){//在第i个位置插入元素e
    if(L==NULL || i<1)
        return ERROR;
    LNode *p=L;
    int j=0;
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return ERROR;
    LNode *q=new(nothrow) LNode;
    if(q==NULL)
        return ERROR;
    q->date=e;
    q->next=p->next;
    p->next=q;
    return Ok;
}

Status ListDelete(LinkList L,int i){//删除第i个位置的结点
    if(L==NULL || i<1)
        return ERROR;
    LNode *p=L;
    int j=0;
    while(p!=NULL && j<i-1){
        p=p->next;
        j++;
    }
    if(p==NULL || p->next==NULL)
        return ERROR;
    LNode *q=p->next;
    p->next=q->next;
    delete q;
    return Ok;
}

void PrintList(LinkList L){//打印所有数据结点
    if(L==NULL)
        return;
    LNode *p=L->next;
    while(p!=NULL){
        cout<<p->date<<" ";
        p=p->next;
    }
    cout<<endl;
}

void DestroyList(LinkList &L){//释放头结点及所有数据结点
    while(L!=NULL){
        LNode *p=L;
        L=L->next;
        delete p;
    }
}

Status MergeList(LinkList &La,LinkList &Lb,LinkList &Lc){
    //La和Lb必须非递减有序，Lc必须为空，三个指针变量互不相同
    if(&La==&Lb || &La==&Lc || &Lb==&Lc)
        return ERROR;
    if(La==NULL || Lb==NULL || La==Lb || Lc!=NULL)
        return ERROR;
    LNode *pa=La->next;
    LNode *pb=Lb->next;
    Lc=La;//复用La的头结点
    LNode *r=Lc;
    while(pa!=NULL && pb!=NULL){
        if(pa->date<=pb->date){
            r->next=pa;
            r=pa;
            pa=pa->next;
        }
        else{
            r->next=pb;
            r=pb;
            pb=pb->next;
        }
    }
    if(pa!=NULL)
        r->next=pa;
    else
        r->next=pb;
    delete Lb;//Lb的头结点不再需要，数据结点已归入Lc
    La=NULL;
    Lb=NULL;//归并后只通过Lc使用和释放这些结点
    return Ok;
}

int main(){
    LinkList La=NULL,Lb=NULL,Lc=NULL;
    if(InitLIst(La)==ERROR || InitLIst(Lb)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    int n;
    cout<<"===== 建立单链表La（头插法） ====="<<endl;
    cout<<"请输入链表中节点数量：";
    if(!(cin>>n) || n<0){
        cout<<"节点数量无效"<<endl;
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"请输入"<<n<<"个元素（头插法，逆序生成链表）：";
    if(CreateList(La,n,1)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"La的元素：";
    PrintList(La);

    cout<<"===== 建立单链表Lb（尾插法） ====="<<endl;
    cout<<"请输入链表中节点数量：";
    if(!(cin>>n) || n<0){
        cout<<"节点数量无效"<<endl;
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"请输入"<<n<<"个元素（尾插法，顺序生成链表）：";
    if(CreateList(Lb,n,2)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"Lb的元素：";
    PrintList(Lb);

    int e;
    cout<<"===== 测试查找操作（按值查找） ====="<<endl;
    cout<<"请输入想要在单链表La中查找的值：";
    if(!(cin>>e)){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    LNode *p=LocateElem(La,e);
    if(p==NULL)
        cout<<"没有这个元素"<<endl;
    else
        cout<<"元素"<<e<<"在La中找到，值为："<<p->date<<endl;

    cout<<"===== 测试插入操作 ====="<<endl;
    if(ListInsert(La,2,10)==Ok){//按实验示例在第2个位置插入10
        cout<<"插入成功，La的新元素：";
        PrintList(La);
    }
    else
        cout<<"插入失败，位置无效或内存不足"<<endl;

    cout<<"===== 测试删除操作 ====="<<endl;
    if(ListDelete(La,3)==Ok){//按实验示例删除第3个位置的元素
        cout<<"删除成功，La的新元素：";
        PrintList(La);
    }
    else
        cout<<"删除失败，位置无效"<<endl;

    cout<<"===== 归并La和Lb ====="<<endl;
    if(MergeList(La,Lb,Lc)==ERROR){
        DestroyList(La);
        DestroyList(Lb);
        return 1;
    }
    cout<<"归并后的Lc元素：";
    PrintList(Lc);
    DestroyList(Lc);
    return 0;
}
