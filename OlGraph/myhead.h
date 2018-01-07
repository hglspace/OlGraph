#define MAX_VERTEX_NUM 4//人为设置顶点数为4
typedef int Bool;//自定义布尔型变量
#define True 1//以访问状态
#define False 0//未访问状态
//十字链表存储有向图
struct ArcBox{//弧结点
    int tailvex;//尾结点在图中的位置
    int headvex;//头结点在图中的位置
    struct ArcBox * hlink;//弧头相同的下一条弧
    struct ArcBox * tlink;//弧尾相同的下一条弧
    Bool mark;//访问的标志 True代表访问过，False代表没有访问过
};
struct VexNode{//顶点结点
    char data;//顶点信息
    struct ArcBox * firstin;//以该顶点为弧头的第一条弧
    struct ArcBox * firstout;//以该顶点为弧尾的第一条弧
};
struct OlGraph{
    struct VexNode xlist[MAX_VERTEX_NUM];//顶点结点数组
    int vexnum;//当前顶点数量
    int arcnum;//当前弧的数量
};

