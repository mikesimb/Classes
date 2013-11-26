#ifndef PATHFIND_H
#define PATHFIND_H
#include <vector>

using namespace std;

typedef struct tagNode {
    int x;
    int y;
    int H;
    int G;
    int F;
    tagNode* father;

}*pNode, Node;



class CPathFind {
public:
    CPathFind();
    virtual ~CPathFind();
    void SetMap(int row, int col, int ** map);
    bool PathFind(int startx, int starty, int endx, int endy);
    //检查节点是否是目标节点
    bool CheckIsDestination(pNode node);
    bool GetShiftByDirectory(int dir , int* x , int* y);
    bool isIllegle(int x, int y);

    void PrintPath();
    void Printmap();



protected:
    void InitNode(int startx, int starty, int endx, int endy);

    pNode CreateFirstNode(int x, int y);
    int CalcG(int x, int y);

    void generatePath();

private:
    //地图数据，没有地图数据肯定什么都做不了
    int** m_map;
    int m_row;
    int m_col;

    //最后的路径
    int** m_path;

    int m_startx;
    int m_starty;
    int m_endx;
    int m_endy;

    int m_step;


    tagNode* m_endnode;
    tagNode* m_startnode;
    //寻路算法需要的2个队列
    vector<pNode> m_openlist;
    vector<pNode> m_closelist;

};

bool NodeSort(pNode node1,pNode node2);

#endif // PATHFIND_H
