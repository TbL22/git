//实验6：哈夫曼树及哈夫曼编码的实现
#include<iostream>
#include<cstring>
#include<climits>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0

typedef struct{
    long long weight;
    int parent;
    int lch;
    int rch;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

//选出parent为0且权值最小的两个结点，权值相同时先选下标小的
Status Select(HuffmanTree HT,int n,int &s1,int &s2){
    s1=0;
    s2=0;
    for(int i=1;i<=n;i++){
        if(HT[i].parent==0){
            if(s1==0||HT[i].weight<HT[s1].weight){
                s2=s1;
                s1=i;
            }
            else if(s2==0||HT[i].weight<HT[s2].weight)
                s2=i;
        }
    }
    if(s1==0||s2==0)
        return ERROR;
    return Ok;
}

Status CreatHuffmanTree(HuffmanTree &HT,int n,long long w[]){
    if(n<1||n>INT_MAX/2||w==NULL)
        return ERROR;
    long long sum=0;
    for(int i=1;i<=n;i++){
        if(w[i]<0||sum>LLONG_MAX-w[i])
            return ERROR;
        sum+=w[i];
    }
    int m=2*n-1;
    HT=new HTNode[m+1];
    int i,s1,s2;
    for(i=1;i<=m;i++){
        HT[i].weight=0;
        HT[i].parent=0;
        HT[i].lch=0;
        HT[i].rch=0;
    }
    for(i=1;i<=n;i++)
        HT[i].weight=w[i];
    for(i=n+1;i<=m;i++){
        Select(HT,i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    return Ok;
}

Status CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n){
    if(HT==NULL||n<1)
        return ERROR;
    HC=new char *[n+1];
    HC[0]=NULL;
    //只有一个字符时，单独规定编码为0
    if(n==1){
        HC[1]=new char[2];
        strcpy(HC[1],"0");
        return Ok;
    }
    char *cd=new char[n];
    cd[n-1]='\0';
    int i,start,c,f;
    for(i=1;i<=n;i++){
        start=n-1;
        c=i;
        f=HT[i].parent;
        //从叶子向根回溯，左孩子记0，右孩子记1
        while(f!=0){
            --start;
            if(HT[f].lch==c)
                cd[start]='0';
            else
                cd[start]='1';
            c=f;
            f=HT[f].parent;
        }
        HC[i]=new char[n-start];
        strcpy(HC[i],cd+start);
    }
    delete[] cd;
    return Ok;
}

Status DestroyHuffmanTree(HuffmanTree &HT){
    delete[] HT;
    HT=NULL;
    return Ok;
}

Status DestroyHuffmanCode(HuffmanCode &HC,int n){
    if(HC!=NULL){
        for(int i=1;i<=n;i++)
            delete[] HC[i];
        delete[] HC;
        HC=NULL;
    }
    return Ok;
}

int main(){
    int n,i;
    HuffmanTree HT=NULL;
    HuffmanCode HC=NULL;
    cout<<"请输入叶子结点的个数："<<endl;
    if(!(cin>>n)||n<1||n>INT_MAX/2){
        cout<<"叶子结点的个数输入错误！"<<endl;
        return 0;
    }
    long long *w=new long long[n+1];
    cout<<"请输入叶子结点的权值："<<endl;
    for(i=1;i<=n;i++){
        if(!(cin>>w[i])||w[i]<0){
            cout<<"权值应为非负整数！"<<endl;
            delete[] w;
            return 0;
        }
    }
    if(CreatHuffmanTree(HT,n,w)==ERROR){
        cout<<"构造失败，请检查权值之和是否超出范围！"<<endl;
        delete[] w;
        return 0;
    }
    CreatHuffmanCode(HT,HC,n);
    cout<<"每个权值对应的字符的哈夫曼编码为："<<endl;
    for(i=1;i<=n;i++)
        cout<<HT[i].weight<<"对应的字符的编码为 "<<HC[i]<<endl;
    DestroyHuffmanCode(HC,n);
    DestroyHuffmanTree(HT);
    delete[] w;
    return 0;
}
