

#include <stdio.h>
#include "myhead.h"
#include <stdlib.h>
Bool visits[MAX_VERTEX_NUM];//定义顶点辅助数组，记录顶点是否访问过
int count=0;//定义全局变量，辅助数组finished使用
struct ArcBox * edg[MAX_VERTEX_NUM];//定义全局弧指针数组，记录弧地址，方便把弧的是否访问过的状态重置
/*
   初始化有向图
 */
struct OlGraph init(void){
    int i,j,k,m;
    char data1,data2;//用来接受顶点的信息，根据信息查找顶点的位置
    struct OlGraph g;
    int locateVex(struct OlGraph g,char data);//声明查找顶点位置的函数
    printf("请输入图的顶点数:");
    scanf("%d",&g.vexnum);
    printf("请输入图的边数:");
    scanf("%d",&g.arcnum);
    //开始初始化顶点和弧
    for(i=0;i<g.vexnum;i++){//初始化顶点
        printf("请输入第%d个顶点:",i+1);
        scanf(" %c",&g.xlist[i].data);
        g.xlist[i].firstin=NULL;
        g.xlist[i].firstout=NULL;
        visits[i]=False;
    }
    for(j=0;j<g.arcnum;j++){//初始化弧
        struct ArcBox * p = malloc(sizeof(struct ArcBox));//开辟存储弧的空间
        if(p==NULL){//如果开辟失败，程序终止
           exit(-1);
                }
        printf("请输入第%d条边的起点:",j+1);
        scanf(" %c",&data1);
        printf("请输入第%d条边的终点:",j+1);
        scanf(" %c",&data2);
        k=locateVex(g,data1);
        m=locateVex(g,data2);
        p->headvex=m;//对弧的头结点赋值
        p->tailvex=k;//对弧的尾结点赋值
        p->hlink=NULL;
        p->tlink=NULL;
        p->mark=False;//弧的状态置为未访问状态
        if(g.xlist[m].firstin==NULL){//m结点是头结点，需要动态改变该结点第一个以该结点为头结点的弧
            g.xlist[m].firstin=p;
        }else{
            p->hlink=g.xlist[m].firstin;
            g.xlist[m].firstin=p;
        }
        if(g.xlist[k].firstout==NULL){//k结点是尾结点，需要动态改变该结点第一个以该结点为尾结点的弧
            g.xlist[k].firstout=p;
        }else{
            p->tlink=g.xlist[k].firstout;
            g.xlist[k].firstout=p;
        }
        edg[j]=p;//把弧的指针存储到 弧指针数组中
    }
    return g;
}

/*
  根据顶点的信息查找顶点在图中的位置
 */
int locateVex(struct OlGraph g,char data){
    int i;
    for(i=0;data!=g.xlist[i].data;i++);
    return i;
}

/*
 生成有向图的强连通分量的顶点集
 */
void DFSTraverse(struct OlGraph g){
    int i,k,s;
    int finished[MAX_VERTEX_NUM];//该数组存储退出DFS函数的顶点（按照退出的顺序，先退出来的顶点先记录。记录的是顶点的位置）,作用是：方便反向深度遍历顶点
    void DFS(struct OlGraph g,int i,int finished[]);//声明深度遍历顶点的函数
    void DFSRever(struct OlGraph g,int i,int finished[]);//声明按照数组finished中存储的顶点，从finished[n-1]元素中存储的顶点开始深度遍历的函数 (n是存储的顶点个数)
    for(i=0;i<g.vexnum;i++){//开始遍历顶点
        if(visits[i]==True){//如果访问过，就跳过
            continue;
        }
        DFS(g,i,finished);//调用函数
        //finished[count++]=i;
    }
    for(k=0;k<g.vexnum;k++){//把顶点访问的标志重置到开始状态
        visits[k]=False;
    }
    for(s=0;s<g.arcnum;s++){//把弧的访问标志重置到开始状态
        edg[s]->mark=False;
    }
    while(count>=1){//按照finished数组中存放的顶点，开始深度遍历
        if(visits[finished[count-1]]==True){//如果该顶点访问过就跳过
            continue;
        }
        visits[finished[count-1]]=True;//置该顶点的访问状态为已访问
        printf("%c",g.xlist[finished[count-1]].data);//打印该顶点的信息，其实就是对该顶点进行操作，访问
        DFSRever(g,finished[count-1],finished);//调用函数遍历
        printf("\n.........\n");
        count--;//访问下一顶点
    }
}
void DFSRever(struct OlGraph g,int i,int finished[]){
    int j;
    int getTailAdjVex(struct OlGraph g,int i);//声明查找以该顶点为头的弧的尾顶点的函数
    for(j=getTailAdjVex(g, i);j>=0;j=getTailAdjVex(g, i)){
        if(visits[j]==True){
            continue;
        }
        visits[j]=True;
        DFSRever(g,j,finished);//递归调用，查找i结点的邻接点的邻接点
        printf("%c",g.xlist[j].data);//访问i结点的邻接点
    }
}
void DFS(struct OlGraph g,int i,int finished[]){
    visits[i]=True;
    int w;
    int getHeadAdjVex(struct OlGraph g,int i);//声明以该结点为尾的弧的头结点的函数
    for(w=getHeadAdjVex(g,i);w>=0;w=getHeadAdjVex(g,i)){
        if(visits[w]==True){
            continue;
        }
        DFS(g,w,finished);//递归调用，其实就是深度遍历
    }
    finished[count++]=i;//退出函数时把该结点存储到finished数组中
}

/*
 查找以该结点为尾的弧的头结点
 */
int getHeadAdjVex(struct OlGraph g,int i){
    struct ArcBox * p=g.xlist[i].firstout;
    if(p==NULL){
        return -1;
    }
    //for(p=g.xlist[i].firstout;p->mark==True;p=p->tlink);
    while(p->mark==True){
        p=p->tlink;
        if(p==NULL){
            return -1;
        }
    }
    p->mark=True;
    return p->headvex;
  
}

/*
 查找以该顶点为头的弧的尾顶点
 */
int getTailAdjVex(struct OlGraph g,int i){
    struct ArcBox * p=g.xlist[i].firstin;
    if(p==NULL){
        return -1;
    }
    //for(;p->mark==True;p=p->hlink);
    while(p->mark==True){
        p=p->hlink;
        if(p==NULL){
            return -1;
        }
    }
    p->mark=True;
    return p->tailvex;
}

