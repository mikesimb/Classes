//
//  AStarPath.h
//  Sky
//
//  Created by zhang zaiwei on 13-11-18.
//
//

#ifndef __Sky__AStarPath__
#define __Sky__AStarPath__

#include <queue>//为了使用优先级队列priority_queue
#include <stack>
#include <vector>

//迷宫地图中节点类型标记
enum{
    NODE_EMPTY,//可以通过的节点
    NODE_OBSTACLE,//障碍物，不可通过
    NODE_PATH//路径上的点
};

//记录路径上的点的坐标
typedef struct tagpathNode{
    int x,y;
}PathNode;

//节点数据结构定义
typedef struct tagNode{
    int x,y;//当前点在迷宫中的位置坐标
    int g;//起始点到当前点实际代价
    int h;//当前节点到目标节点最佳路径的估计代价
    int f;//估计函数：f = g + h。
    struct tagNode *father;//指向其父节点的指针
}Node;;


//定义STL优先队列的排序方式
class HeapCompare_f{
public:
    bool operator()(Node* x,Node* y) const
    {
        return x->f > y->f;//依据估价函数进行排序：升序排列
    }
};

//迷宫寻路：A*算法
class AStarPathFinding{
public:
    
private:
    char *m_mapFileName;//存储地图信息的文件名
    int m_rows,m_cols;//迷宫的高度和宽度
    int **m_maze;//迷宫布局
    int m_startX,m_startY;//起始点坐标
    int m_endX,m_endY;//目标点坐标
    int dx[8];
    int dy[8];//8个子节点移动方向：上、下、左、右、左上、右上、右下、左下
    
    Node *startNode,*endNode;//起始节点和目标节点
    int **m_path;//记录路径信息
    int m_steps;//搜索所花费的总步数
    
    //OPEN表：采用C++ STL中vector实现优先级队列功能
    //注意：存储的是Node*指针
    std::vector<Node*> OPENTable;
    //CLOSED表：存储的也是Node*指针
    std::vector<Node*> CLOSEDTable;
    
public:
    //构造函数
    AStarPathFinding();
    ~AStarPathFinding();//析构函数
    void init();//初始化
    
    //设置地图信息
    void SetupMap(int row,int col ,int * cmap);
    //读取地图信息
    bool readMap();
    //寻路主函数
    virtual bool pathFinding();
    
    virtual bool PathFinding(int startx,int starty,int endx,int endy);
    //产生路径信息
    void generatePath();
    //打印路径信息
    void printPath();
    //估计当前点到目标点的距离：曼哈顿距离
    int judge(int x,int y);
    //判断某一节点是否合法
    bool isIllegle(int x,int y);
    
    void test(int * map);
};

#endif /* defined(__Sky__AStarPath__) */
