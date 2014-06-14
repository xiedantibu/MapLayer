/**
*@file Demo2.cpp
*@brief ¸ÅÊö
*
*ÏêÏ¸¸ÅÊö
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-14 22:01
*/
#include "Demo2.h"

USING_NS_CC;

CCScene* Demo2::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	Demo2 *layer = Demo2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Demo2::init()
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
	m_map = MapLayer::create(1, 11, ccp(visibleSize.width/2.f, visibleSize.height/2.f), size, 5.f);
	m_map->setPosition(ccp(visibleSize.width/2.f, visibleSize.height/2.f));
	this->addChild(m_map, -1);

	m_map->dealTouch(ccp(visibleSize.width*10.5f, visibleSize.height/2.f));

	return true;
}


void Demo2::menuCloseCallback(CCObject* pSender)
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