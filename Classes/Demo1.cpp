/**
*@file Demo1.cpp
*@brief ¸ÅÊö
*
*ÏêÏ¸¸ÅÊö
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-14 22:01
*/
#include "Demo1.h"

USING_NS_CC;

CCScene* Demo1::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Demo1 *layer = Demo1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Demo1::init()
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
	size.width = 0.f;
	size.height = 0.f;
	m_map = MapLayer::create(100, 100, ccp(visibleSize.width/2.f, visibleSize.height/2.f), size, 5.f);
	m_map->setPosition(ccp(visibleSize.width/2.f, visibleSize.height/2.f));
	this->addChild(m_map, -1);

	/// Î¯ÍÐ´¥ÃþÐ­Òé
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	return true;
}


void Demo1::menuCloseCallback(CCObject* pSender)
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

bool Demo1::ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	return true;
}

void Demo1::ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent )
{
	CCPoint	touchPoint	= pTouch->getLocationInView();
	touchPoint			= CCDirector::sharedDirector()->convertToGL(touchPoint);
	m_map->dealTouch(touchPoint);
}

void Demo1::draw()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	glLineWidth( 5.0f );
	CCPoint point1 = ccp(visibleSize.width/2.f - 5.f, visibleSize.height/2.f + 5.f);
	CCPoint point2 = ccp(visibleSize.width/2.f + 5.f, visibleSize.height/2.f - 5.f);
	ccDrawRect(point1, point2);
	glLineWidth( 1.0f );
}
