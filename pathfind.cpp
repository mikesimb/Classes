
#include <stdlib.h>
#include <iostream>
#include "pathfind.h"

bool NodeSort(pNode node1,pNode node2)
{
    return (node1->F > node2->F);
}

CPathFind::CPathFind() {
    // TODO Auto-generated constructor stub
    m_map = NULL;
    m_row = 0;
    m_col = 0;

    //int** path = NULL;

    m_startx = 0;
    m_starty = 0;
    m_endx = 0;
    m_endy = 0;

    m_step = 0;

}

CPathFind::~CPathFind() {
    // TODO Auto-generated destructor stub

}

void CPathFind::SetMap(int row, int col, int** map) {
    if (map != NULL) {
        m_row = row;
        m_col = col;
        m_map = map;
    }

    m_path = new int *[m_row];
     for(int i = 0;i < m_row;i++)
     {
      m_path[i]=new int[m_col];
     }
    int* a = (int*)&map[0];
    int* b = (int*)m_path[0];

    for (int i = 0 ;i< m_row ;i++)
    {
        for(int j= 0 ;j< m_col;j++)
        {
            b[j]=a[j];
          }
        a =a+ m_col;
        b =b+ m_col;
    }
}



int CPathFind::CalcG(int x, int y) {
    return (10 * (abs(m_endx - x) + abs(m_endy - y)));
}

pNode CPathFind::CreateFirstNode(int x, int y)
{
    pNode node = new Node;
    node->x = x;
    node->y = y;
    node->H = 0;
    node->G = CalcG(x, y);
    node->F = node->H + node->G;
    node->father = NULL;
    return node;

}

void CPathFind::InitNode(int startx,int starty,int endx,int endy)
{
    m_startnode = new Node();
    m_startnode->x = startx;
    m_startnode->y = starty ;
    m_startnode->G = CalcG(startx,starty);
    m_startnode->H = 0 ;
    m_startnode->F = m_startnode->G+ m_startnode->H;
    m_startnode->father = NULL;

    m_endnode = new Node();
    m_endnode->x = endx;
    m_endnode->y = endy ;
    m_endnode->G = CalcG(endx,endy);
    m_endnode->H = 0 ;
    m_endnode->F = m_endnode->G+ m_endnode->H;
    m_endnode->father = NULL;


}

bool CPathFind::CheckIsDestination(pNode node)
{
    //判断是否已经搜寻到目标节点
           if (node->x == m_endx && node->y == m_endy)
           {
               cout << "到达目标地点!!!" << endl;
               if(m_endnode !=NULL)
               {
               m_endnode->G = node->G;
               m_endnode->H = node->H;
               m_endnode->F = node->F;
               m_endnode->father = node->father;
               return true;
               }
               else
                   return false;
           }
           else
               return false;



}


void CPathFind::generatePath()
{

    Node *nodeChild = m_endnode;
    Node *nodeParent = m_endnode->father;
    while((nodeChild->x != m_startnode->x) or (nodeChild->y != m_startnode->y))
    {
        ((int*)m_path[nodeChild->x])[nodeChild->y] = 2;//标记为路径上的点
        cout<<"Path:"<<nodeChild->x<<nodeChild->y<<endl;
        nodeChild = nodeParent;
        if (nodeParent !=NULL)
        nodeParent = nodeParent->father;
    }
    ((int*)m_path[m_startnode->x])[m_startnode->y]= 2;//标记为路径上的点
}



bool CPathFind::GetShiftByDirectory(int dir , int * x , int* y)
{
    switch (dir) {
    case 0:
        *x = -1;
        *y = 0;
        break;
    case 1:
        *x = -1;
        *y = 1;
        break;
    case 2:
        *x= 0;
        *y= 1;
        break;
    case 3:
        *x = 1;
        *y = 1;
        break;
    case 4:
        *x=  0 ;
        *y = 1 ;
        break;
    case 5:
        *x = -1;
        *y = 1;
        break;
    case 6:
        *x = 0;
        *y = -1;
        break;
    case 7:
        *x = -1;
        *y = -1;
        break;
    default:
        x = 0 ;
        y = 0 ;
        break;
    }

    return true;


}
//该函数是判断数据是否违法
bool CPathFind::isIllegle(int x, int y)
{

    //Printmap();
    int * a = (int*)((&m_map[0]));
    for (int k = 0 ;k<x ;k++)
    {
        a = a+m_col;
    }
     cout<<"---------------begin"<<x<<"----------------"<<endl;
    for(int i =0;i<16;i++)
    {
        cout<<a[i];
    }
    cout<<""<<endl;

    cout<<"---------------end----------------"<<endl;
    int value =  a[y];
      cout<<"isIllegle:"<<x<<y<<endl;
    if (x >= 0 && x < m_row &&
        y >= 0 && y < m_col &&
        value == 1)
        return true;
    else
    {
        cout<<"无效点"<<endl;
        return false;
    }
}



bool CPathFind::PathFind(int startx, int starty, int endx, int endy) {
    InitNode(startx,starty,endx,endy);
    //首先做几个预先判断
    if ((startx == endx) && (starty == endy)) {
        cout << "起点就是终点";
    }
    m_startx = startx;
    m_starty = starty;
    m_endx = endx;
    m_endy = endy;
    pNode node = CreateFirstNode(startx, starty);
    //将这个节点放入openlist
    m_openlist.push_back(node);
    //对这个地方进行排序
    push_heap(m_openlist.begin(),m_openlist.end(),NodeSort);
    pNode tmpnode = NULL;
    for(;;)
    {
        if(m_openlist.empty())
        {
            cout<<"错误:不能找到目标节点"<<endl;
            return false;
        }
        tmpnode = m_openlist.front();
        ++m_step;
        pop_heap(m_openlist.begin(),m_openlist.end(),NodeSort);
        m_openlist.pop_back();
        if (!CheckIsDestination(tmpnode))
        {
            //这里不是是目标地点
            for(int i = 0 ;i<8 ;i++)
            {
                int nextx ;
                int nexty ;
                GetShiftByDirectory(i,&nextx,&nexty);
                nextx = tmpnode->x + nextx;
                nexty = tmpnode->y + nexty;
                //判断这个点是可以通过的
                cout<<"next is"<<nextx<<":"<<nexty<<endl;
                if(isIllegle(nextx,nexty))
                {
                   //这里可以通过
                    //计算这个点的G值
                    int newGvalue;
                    if(i % 2 ==0)
                      newGvalue = tmpnode->G+10;
                    else
                      newGvalue = tmpnode->G+14;

                    vector<pNode>::iterator OpenIt;
                    //说明该节点在OPEN表中
                    for(OpenIt=m_openlist.begin();OpenIt<m_openlist.end();OpenIt++)
                    {
                        if (((*OpenIt)->x == nextx)&&((*OpenIt)->y ==nexty))
                        {
                             break;
                        }
                    }

                    if(OpenIt != m_openlist.end())
                    {
                       if ((*OpenIt)->G <= newGvalue)
                           continue;
                    }
                    //说明该节点在close表中
                    vector<pNode>::iterator CloseIt;

                    for(CloseIt=m_closelist.begin();CloseIt<m_closelist.end();CloseIt++)
                    {
                        if (((*CloseIt)->x == nextx)&&((*CloseIt)->y ==nexty))
                        {
                             break;
                        }
                    }

                    if(CloseIt != m_closelist.end())
                    {
                       if ((*CloseIt)->G <= newGvalue)
                           continue;
                    }

                    //如果都不满足上边的条件那么说明这个节点是最优节点
                    Node *bestNode = new Node;
                    bestNode->x = nextx;
                    bestNode->y = nexty;
                    bestNode->father = tmpnode;
                    bestNode->G = newGvalue;
                    bestNode->H = CalcG(nextx,nexty);
                    bestNode->F = bestNode->G + bestNode->H;

                    if (CloseIt != m_closelist.end())
                    {
                        delete(*CloseIt);
                        m_closelist.erase(CloseIt);
                    }

                    if (OpenIt != m_openlist.end())
                    {
                        delete(*OpenIt);
                        m_openlist.erase(OpenIt);
                        make_heap(m_openlist.begin(),m_openlist.end(),NodeSort);

                    }
                    m_openlist.push_back(bestNode);
                    push_heap(m_openlist.begin(),m_openlist.end(),NodeSort);
                    for(vector<pNode>::iterator k = m_openlist.begin() ;k<m_openlist.end();k++)
                    {
                        cout<<"x:"<<(*k)->x<<",y:"<<(*k)->y<<endl;


                    }
                    cout<<" isIlleglea is true"<<endl;
                }
                else
                {
                    cout<<" isIlleglea is false"<<endl;
                    //不能通过
                }


            }
            m_closelist.push_back(tmpnode);


        }
        else
        {
                generatePath();
                return true;
         }


    }


}
void CPathFind::Printmap()
{
    int * a = (int*)(&m_map[0]);
    for(int j = 0 ;j<m_row;j++)
    {
        for(int i= 0 ;i<m_col;i++)
        {
            cout<<a[i]<<";";
        }
        cout<<""<<endl;
        a = (int*)(&m_map[0])+(j+1)*m_col;
    }



}


void CPathFind::PrintPath()
{
    int * a = (int*) m_path[0];
    for(int i = 0 ;i<m_row;i++)
    {
        for(int j= 0 ;j<m_col;j++)
        {
            cout<<a[j]<<";";
        }
        cout<<""<<endl;
        a = a+m_col;
    }

}




