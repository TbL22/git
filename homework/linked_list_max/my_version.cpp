//设计一个算法通过一趟遍历确定长度为n的单链表中值最大的结点
#include<iostream>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0
typedef struct LNode{
    int date;
    struct LNode *next;
}LNode,*LinkList;
Status InitLIst(LinkList &L){
    L=new LNode;
    if(L=NULL)
    return ERROR;
    L->next=NULL;
}
int findMaxLnode(LinkList &L,int n){
    int i=0;
    if(n<2)
    return 1;
    while(L->next=NULL){
        LNode *p=new LNode;
        p=L;
        p=p->next;
        L=p->next;
        int i=0;
        while(i<n-1){
            if(p->date>L->date)
            L=L->next;
            p=L;
            L=L->next;
        }
        i++;
    }
    cout<<p<<endl;
    return 1
}
int main(){
    int n;
    cin>>n;
    LinkList L;
    InitLIst L;
    findMaxLnode(L,n);
}

