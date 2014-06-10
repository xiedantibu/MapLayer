#include "HelloWorldScene.h"

USING_NS_CC;

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	
	CCSize size;
	size.width = 5.f;
	size.height = 5.f;
	m_map = MapLayer::create(1, 3, ccp(visibleSize.width/2.f, visibleSize.height/2.f), size, 5.f);
	m_map->setPosition(ccp(visibleSize.width/2.f, visibleSize.height/2.f));
	this->addChild(m_map, -1);

	/// Î¯ÍÐ´¥ÃþÐ­Òé
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    return true;
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

bool HelloWorld::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void HelloWorld::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint	touchPoint	= pTouch->getLocationInView();
	touchPoint			= CCDirector::sharedDirector()->convertToGL(touchPoint);
	m_map->dealTouch(touchPoint);
}

void HelloWorld::draw()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	glLineWidth( 5.0f );
	CCPoint point1 = ccp(visibleSize.width/2.f - 5.f, visibleSize.height/2.f + 5.f);
	CCPoint point2 = ccp(visibleSize.width/2.f + 5.f, visibleSize.height/2.f - 5.f);
	ccDrawRect(point1, point2);
	glLineWidth( 1.0f );
}
