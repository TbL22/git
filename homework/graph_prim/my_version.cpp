//实验8：基于邻接矩阵建无向图，用Prim算法求最小生成树
#include<iostream>
#include<climits>
using namespace std;
typedef int Status;
#define Ok 1
#define ERROR 0
#define MAXSIZE 100
#define INF INT_MAX

typedef struct{
    char vexs[MAXSIZE];
    int arcs[MAXSIZE][MAXSIZE];
    int vexnum;
    int arcnum;
}AMGraph;

typedef struct{
    int adjvex;
    int lowcost;
}CloseEdge;

int LocateVex(AMGraph &G,char v){
    for(int i=0;i<G.vexnum;i++){
        if(G.vexs[i]==v)
            return i;
    }
    return -1;
}

Status CreateUDN(AMGraph &G){
    int i,j,k,w;
    char v1,v2;
    cout<<"请输入总顶点数，总边数，以空格隔开:";
    if(!(cin>>G.vexnum>>G.arcnum))
        return ERROR;
    if(G.vexnum<1||G.vexnum>MAXSIZE||G.arcnum<0
        ||G.arcnum>G.vexnum*(G.vexnum-1)/2)
        return ERROR;

    cout<<endl<<"输入点的名称，如 a"<<endl;
    for(i=0;i<G.vexnum;i++){
        cout<<"请输入第"<<i+1<<"个点的名称:";
        if(!(cin>>G.vexs[i]))
            return ERROR;
        for(j=0;j<i;j++){
            if(G.vexs[j]==G.vexs[i])
                return ERROR;
        }
    }
    for(i=0;i<G.vexnum;i++){
        for(j=0;j<G.vexnum;j++)
            G.arcs[i][j]=(i==j?0:INF);
    }

    cout<<endl<<"输入边依附的顶点及权值，如 a b 5"<<endl;
    for(k=0;k<G.arcnum;k++){
        cout<<"请输入第"<<k+1<<"条边依附的顶点及权值:";
        if(!(cin>>v1>>v2>>w))
            return ERROR;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        //顶点必须存在，不输入自环、重复边，INF保留为无边标记
        if(i==-1||j==-1||i==j||w==INF)
            return ERROR;
        if(G.arcs[i][j]!=INF)
            return ERROR;
        G.arcs[i][j]=w;
        G.arcs[j][i]=w;
    }
    return Ok;
}

Status MiniSpanTree_Prim(AMGraph &G,char u){
    int k=LocateVex(G,u);
    if(k==-1)
        return ERROR;
    CloseEdge closeEdge[MAXSIZE];
    //单独记录是否入树，使权值为0的边也能正常参与比较
    bool visited[MAXSIZE]={false};
    int a[MAXSIZE],b[MAXSIZE];
    int i,j,min;
    for(j=0;j<G.vexnum;j++){
        closeEdge[j].adjvex=k;
        closeEdge[j].lowcost=G.arcs[k][j];
    }
    visited[k]=true;
    closeEdge[k].lowcost=0;

    for(i=0;i<G.vexnum-1;i++){
        min=INF;
        k=-1;
        for(j=0;j<G.vexnum;j++){
            if(!visited[j]&&closeEdge[j].lowcost<min){
                min=closeEdge[j].lowcost;
                k=j;
            }
        }
        if(k==-1)
            return ERROR;
        //先记录边，确认图连通后再统一输出
        a[i]=closeEdge[k].adjvex;
        b[i]=k;
        visited[k]=true;
        closeEdge[k].lowcost=0;
        for(j=0;j<G.vexnum;j++){
            if(!visited[j]&&G.arcs[k][j]<closeEdge[j].lowcost){
                closeEdge[j].adjvex=k;
                closeEdge[j].lowcost=G.arcs[k][j];
            }
        }
    }
    for(i=0;i<G.vexnum-1;i++)
        cout<<"边 "<<G.vexs[a[i]]<<"--->"<<G.vexs[b[i]]<<endl;
    return Ok;
}

int main(){
    AMGraph G;
    cout<<"************用邻接矩阵构造的图**************"<<endl<<endl;
    if(CreateUDN(G)==ERROR){
        cout<<endl<<"输入错误，无法创建无向图！"<<endl;
        return 0;
    }
    cout<<endl<<"无向图G创建完成！"<<endl<<endl;
    cout<<"******利用普里姆算法构造最小生成树结果：******"<<endl;
    //与实验用例一致，从输入的第一个顶点开始
    if(MiniSpanTree_Prim(G,G.vexs[0])==ERROR)
        cout<<"图不连通，不存在最小生成树！"<<endl;
    return 0;
}
