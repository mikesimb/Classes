#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <map>

using namespace cocos2d;



class HelloWorld : public cocos2d::CCLayer
{
public:
    HelloWorld();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    CCSprite * m_mapSprite;
    
    virtual void draw();
    
    void registerWithTouchDispatcher();
	
	void ccTouchesEnded(cocos2d::CCSet * touches,cocos2d::CCEvent * event);
    void ccTouchesMoved(cocos2d::CCSet * touches,cocos2d::CCEvent * event);

    void MoveDone();
    
    CCAction* walkAction;
    
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
    
    CCAction *createAction(int begin,int end,char* cacheActionName,int Directory,CCPoint point);
    //将设备坐标转换为地图坐标
    CCPoint TransformCoodrToMap(CCPoint devicepoint);
    //将地图坐标转换为设备坐标
    CCPoint TransformCoodrToDevice(CCPoint Mappos);
    //根据地图坐标获取行走的方向
    int getDirectory(int mx,int my);
    
private:
    
    CCLabelTTF * m_lbl_CurrentPos;
    CCLabelTTF * m_lbl_Devicepos;
    CCSprite * m_pSprite;
    
    bool PlayerIsIdle;
    CCSpriteBatchNode * spriteBatchNode;
    CCSpriteFrameCache* cache;
    int dirction;
    //角色当前的地图位置
    CCPoint m_CurrentPos;
    //当前地图的起始位置
    CCPoint m_CurrentMapStartPos;
    
    CCSize m_Mapsize;
    std::list<int> Pathlist;
    int m_border;
    
    
    
    void initmapdata();
    
    void SetPlayerPos(int mapX,int mapY);
    
    void MoveMapTo(CCPoint pos);
    void MovePlayerTo(CCPoint PlayerPos);
    
    
    
    
    
    
    
    
    
};

#endif // __HELLOWORLD_SCENE_H__
