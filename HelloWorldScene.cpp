#include "HelloWorldScene.h"
#include "AStarPath.h"
#include "stdlib.h"

USING_NS_CC;

const int UnitX = 64;
const int UnitY = 64;

const int ScreenRowCount = 16;
const int ScreenColCount = 8 ;
int map[8][16]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},};

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
{
    m_CurrentMapStartPos = CCPointZero;
}

void HelloWorld::initmapdata()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSize mapsize = m_mapSprite->getContentSize();
    //计算场景的边界
    m_border = (visibleSize.height - mapsize.height) / UnitY;
    m_border = (int)m_border /2 * UnitY;
    
    //设定当前的地图宽高
    m_Mapsize = CCSize(19, 6);
    //屏幕绘制为逻辑地图的第几列开始
    m_CurrentMapStartPos = CCPoint(0,0);
    //当前自己再地图中的位置
    m_CurrentPos = CCPoint(0,0);
    //根据当前的地图算绘制。。19
    //根据当前的位置计算绘制坐标
    //逻辑地图的位置继续按屏幕坐标
    CCPoint pos;
    pos.x = m_CurrentMapStartPos.x * 64;
    pos.y = m_CurrentMapStartPos.y * 64+m_border;
    m_mapSprite->setPosition(pos);
    //设置当前的位置
    m_pSprite->setAnchorPoint(ccp(0,0));
    SetPlayerPos(m_CurrentPos.x, m_CurrentPos.y);
}




void HelloWorld::SetPlayerPos(int mapX, int mapY)
{
    int x = mapX - m_CurrentMapStartPos.x;
    int y = mapY - m_CurrentMapStartPos.y;
    m_pSprite->setAnchorPoint(ccp(0,0));
    m_pSprite->setPosition(ccp(x * 64+8 ,y * 64 + m_border ));
    
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    setTouchEnabled(true);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
    
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    m_lbl_CurrentPos = CCLabelTTF::create("轩辕剑--天之痕", "Arial", 36);
    
    // position the label on the center of the screen
    m_lbl_CurrentPos->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - m_lbl_CurrentPos->getContentSize().height));
    
    

    // add the label as a child to this layer
    this->addChild(m_lbl_CurrentPos, 1);

    m_mapSprite = CCSprite::create("resouces/Map/8-1.png");
    m_mapSprite->setAnchorPoint(ccp(0,0));
    m_mapSprite->setPosition(ccp(0,(visibleSize.height-m_mapSprite->getContentSize().height) /2));
    m_mapSprite->setOpacityModifyRGB(true);
    m_mapSprite->setOpacity(200);
    this->addChild(m_mapSprite,0);
    
    
    cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("resouces/role/player.plist");
    m_pSprite = CCSprite::createWithSpriteFrameName("walk_0_7.png");
   // m_pSprite->setPosition(ccp(m_CurrentPos.x*64+32,(m_CurrentPos.y)*64+m_border));
    spriteBatchNode=CCSpriteBatchNode::create("resouces/role/player.png");
	spriteBatchNode->addChild(m_pSprite);
    addChild(spriteBatchNode);
    
    
  	
	PlayerIsIdle = true;

    initmapdata();
    
    
    return true;
}

void HelloWorld::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 //todo list;
    
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


void HelloWorld::draw()
{
    //这里需要绘制格子了。。
    CCPoint pt1;
    CCPoint pt2;
    for (int i = 0 ; i < 16 ; i++)
    {
        for (int j =0 ; j < 8; j++) {
            int x = m_CurrentMapStartPos.y +j;
            int y = m_CurrentMapStartPos.x +i;
            if (map[x][y] != 1) {
                ccDrawColor4B(255, 0, 0, 125);
                
            }
            else
            {
                if(map[x][y] == 2){
                    ccDrawColor4B(0, 255, 255, 125);
                }
                else
                {
                    ccDrawColor4B(0, 255, 0, 125);
                }
                
            }
            pt1.x = i*64 ;
            pt1.y = j*64+m_border;
            pt2.x = (i+1)*64;
            pt2.y = (j+1)*64+m_border;
            ccDrawRect(pt1, pt2);
            
            {
               char  num[20];
               CCTexture2D* tex = new CCTexture2D();
               sprintf(num, "%d,%d",(int)m_CurrentMapStartPos.x + i,(int)m_CurrentMapStartPos.y +j);
                tex->initWithString(num, "Arial", 15);
               CCRect rect = CCRectMake(pt1.x,pt1.y,30,30);
               tex->drawInRect(rect);
               tex->autorelease();
            }
            
        }
    }
    
    char  PlayerPos[20];
    CCTexture2D* tex = new CCTexture2D();
    sprintf(PlayerPos, "playerPos:%d,%d",(int)m_CurrentPos.x,(int)m_CurrentPos.y);
    tex->initWithString(PlayerPos, "Arial", 15);
    CCRect rect = CCRectMake(10,700,100,30);
    tex->drawInRect(rect);
    tex->autorelease();
    
    char  CurrentmapstartPos[20];
    CCTexture2D* tex1 = new CCTexture2D();
    sprintf(CurrentmapstartPos, "CurrentmapstartPos:%d,%d",(int)m_CurrentMapStartPos.x,(int)m_CurrentMapStartPos.y);
    tex1->initWithString(CurrentmapstartPos, "Arial", 15);
    CCRect rect1 = CCRectMake(10,730,100,30);
    tex1->drawInRect(rect1);
    tex1->autorelease();
    


    CCLayer::draw();
    
    
}



CCAction* HelloWorld::createAction(int begin,int end,char* cacheActionName,int Directory,CCPoint point){
	CCAnimationCache *animCache = CCAnimationCache::sharedAnimationCache();
	CCArray *array = CCArray::createWithCapacity(end-begin);
    int dir =-1;
    if (dirction == 6)
        dir =  2;
    else
        dir = dirction;
	char name[20];
	for(int i = begin ;i<end;i++){
		sprintf(name,"walk_%d_%d.png",dir,i);
		CCSpriteFrame* frame =cache->spriteFrameByName(name);
		array->addObject(frame);
	}
    
	CCAnimation *plistAnimation = CCAnimation::createWithSpriteFrames(array,0.2f);
    char ActionName[20];
    sprintf(ActionName, "%s%d", cacheActionName,dir);
    //CCLOG(ActionName);
	CCAnimationCache::sharedAnimationCache()->addAnimation(plistAnimation, cacheActionName);
    
	array->removeAllObjects();
    
	CCAnimation *animation = animCache->animationByName(cacheActionName);
	animation->setRestoreOriginalFrame(true);
	CCAnimate *ani=CCAnimate::create(animation);
	CCActionInterval* plistSeq=(CCActionInterval*)(CCSequence::create(ani,
                                                                      CCFlipX::create(dirction==6? true:false),
                                                                      ani->copy()->autorelease(),
                                                                      NULL
                                                                      ));
	return CCRepeatForever::create(plistSeq);
}


void HelloWorld::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

CCPoint HelloWorld::TransformCoodrToMap(cocos2d::CCPoint devicepoint)
{
    int mx =  (int)(devicepoint.x) / 64 ;
    int my =  (int)(devicepoint.y -m_border) /64;
    CCPoint pt = CCPoint(mx+m_CurrentMapStartPos.x,my+m_CurrentMapStartPos.y);
    return pt;
}

CCPoint HelloWorld::TransformCoodrToDevice(CCPoint Mappos)
{
    int mx =  (Mappos.x -m_CurrentMapStartPos.x)* 64+8  ;
    int my =  (int)Mappos.y * 64+m_border ;
    
    CCPoint pt = CCPoint(mx,my);
    return pt;
}


int HelloWorld::getDirectory(int mx,int my)
{
    int x = mx-(int)m_CurrentPos.x;
    int y = my-(int)m_CurrentPos.y;
    
    
    if ((x<0)&&(y>0))
    {
        CCLOG("X 7= %d,Y =%d",x,y);
        return  7;
    }
    if ( (x ==0) &&(y >0))
    {
        CCLOG("X 0= %d,Y =%d",x,y);
        return 0;
    }
    if ( (x >0) &&(y >0))
    {
        CCLOG("X 1= %d,Y =%d",x,y);
        return 1;
    }
    if ( (x >0) &&(y ==0))
    {
        CCLOG("X 2= %d,Y =%d",x,y);
        return 2;
    }
    
    if ( (x >0) &&(y <0))
    {
        CCLOG("X 3= %d,Y =%d",x,y);
        return 3;
    }
    if ( (x ==0) &&(y <0))
    {
        CCLOG("X 4= %d,Y =%d",x,y);
        return 4;
    }
    if ( (x <0) &&(y <0))
    {
        CCLOG("X 5= %d,Y =%d",x,y);
        return 5;
    }
    if ( (x <0) &&(y ==0))
    {
        CCLOG("X 6= %d,Y =%d",x,y);
        return 6;
    }
    CCLOG("X= %d,Y =%d",x,y);
    return -1;
}

void HelloWorld::MoveMapTo(CCPoint pos)
{
    
    CCPoint mappos = m_mapSprite->getPosition();
    if(dirction == 0)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y +1));
        
    }else    if(dirction == 1)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y +1));

        if ((m_CurrentMapStartPos.x+ScreenRowCount) <= m_Mapsize.width)
        {
            mappos.x -= 64;
            m_CurrentMapStartPos.x++;
        }
    }
    else  if(dirction ==2)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y ));
        if ((m_CurrentMapStartPos.x+ScreenRowCount) <= m_Mapsize.width)
        {
            mappos.x -= 64;
            m_CurrentMapStartPos.x++;
        }
        
    }
    else if(dirction == 3)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y-1 ));
        if ((m_CurrentMapStartPos.x+ScreenRowCount) <= m_Mapsize.width)
        {
            mappos.x -= 64;
            m_CurrentMapStartPos.x++;
        }
    }
    else if(dirction == 4)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y-1 ));
//        if ((m_CurrentMapStartPos.x+ScreenRowCount) <= m_Mapsize.width)
//        {
//            mappos.x -= 64;
//            m_CurrentMapStartPos.x++;
//            MovePlayerTo(m_pSprite->getPosition());
//        }
    }
    else if(dirction == 5)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y-1 ));
        if (m_CurrentMapStartPos.x>0)
        {
            mappos.x += 64;
            m_CurrentMapStartPos.x--;
            //MovePlayerTo(m_pSprite->getPosition());
        }
        
    }else if(dirction == 6)
    {
        
        if (m_CurrentMapStartPos.x>0)
        {
            MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y ));
            mappos.x += 64;
            m_CurrentMapStartPos.x--;
            //MovePlayerTo(m_pSprite->getPosition());
        }
        else{
            MovePlayerTo(ccp(m_CurrentPos.x -1 ,m_CurrentPos.y));
        }
    }else if(dirction == 7)
    {
        MovePlayerTo(ccp(m_CurrentPos.x,m_CurrentPos.y+1 ));
        if (m_CurrentMapStartPos.x>0)
        {
            mappos.x += 64;
            m_CurrentMapStartPos.x--;
            //MovePlayerTo(m_pSprite->getPosition());
        }
    }
    
        
   
    CCActionInterval *actionTo=CCMoveTo::create(1.2f,mappos);
	CCAction *moveMapAction=CCSequence::create(
                                              actionTo,
                                              CCCallFunc::create(this,callfunc_selector(HelloWorld::MoveDone)),
                                              NULL
                                              );
    m_mapSprite->runAction(moveMapAction);
    
}


void HelloWorld::MovePlayerTo(CCPoint PlayerPos)
{
    
    
    if (dirction < 0 )
        return ;
    
    CCPoint location = TransformCoodrToDevice(PlayerPos);
    
    walkAction=createAction(0,7,"move",dirction,ccp(PlayerPos.x,PlayerPos.y));
    
    m_pSprite->setFlipX(dirction==6?true:false);
    
	
    CCPoint realDeast =ccp(location.x,location.y);
    CCActionInterval *actionTo=CCMoveTo::create(1.2f,realDeast);
	CCAction *moveToAction=CCSequence::create(
                                              actionTo,
                                              CCCallFunc::create(this,callfunc_selector(HelloWorld::MoveDone)),
                                              NULL
                                              );
    
    m_pSprite->runAction(walkAction);
    m_pSprite->runAction(moveToAction);
    //m_CurrentPos = CCPoint(PlayerPos);

    
}



void HelloWorld::ccTouchesEnded(cocos2d::CCSet *touches, cocos2d::CCEvent *event)
{
    m_pSprite->stopAllActions();
	
	
	CCTouch* touch=(CCTouch*)(touches->anyObject());
    //获取倒当前点击的坐标
    CCPoint location = touch ->getLocation();
    
    CCPoint mappt = TransformCoodrToMap(location);
    dirction=this->getDirectory((int)mappt.x,(int)mappt.y);
    if (dirction <0 ) return;
    //移动的时候的判定
    if((m_CurrentPos.x -8 < 0  )||((int)(m_CurrentPos.x + 8) >m_Mapsize.width))
    {
        MovePlayerTo(mappt);

    }
    else
    {
        MoveMapTo(mappt);
    }
    
    m_CurrentPos.x = mappt.x ;
    m_CurrentPos.y = mappt.y ;
    PlayerIsIdle = false;
    CCLOG("Currentpos.x = %f,Currentpos.y = %f",m_CurrentPos.x,m_CurrentPos.y);
    
    

}

void HelloWorld::MoveDone()
{
    PlayerIsIdle = true;
    m_pSprite->stopAllActions();
    CCAnimationCache *animCache = CCAnimationCache::sharedAnimationCache();
    
    char name[20];
    sprintf(name,"stand%d",dirction);
	CCAnimation *standAnimation = animCache->animationByName(name);
    if (standAnimation==NULL)
    {
        CCArray * standArray= CCArray::createWithCapacity(1);
        char standName[20];
		int dir ;
        if (dirction == 6 )
        {    dir = 2;}
        else
        { dir = dirction;}
        
        for(int i=7;i<8;i++){
			sprintf(standName,
                    "walk_%d_%d.png",dir,i);
            
			CCSpriteFrame* frame =cache->spriteFrameByName(standName);
			standArray->addObject(frame);
		}
		standAnimation =CCAnimation::createWithSpriteFrames(standArray,0.2f);
		animCache->addAnimation(standAnimation, name);
		standArray->removeAllObjects();
        delete standArray;
    }
    standAnimation->setRestoreOriginalFrame(true);
    CCAnimate *standAni=CCAnimate::create(standAnimation);
    CCActionInterval* s=(CCActionInterval*)(CCSequence::create(standAni,
                                                               standAni->copy()->autorelease(),
                                                               NULL
                                                               ));
    CCAction *frameAction=CCRepeatForever::create(s);
    
	
	m_pSprite->setFlipX(dirction == 6);
	m_pSprite->runAction(frameAction);
}


