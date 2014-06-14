#include "HelloWorldScene.h"
#include "Demo1.h"
#include "Demo2.h"
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
	
	CCMenuItemImage *pDemo1 = CCMenuItemImage::create(
		"demo1.png",
		"demo1.png",
		this,
		menu_selector(HelloWorld::menuDemo1eCallback));
	pDemo1->setPosition(ccp(visibleSize.width/4.f, visibleSize.height/2.f));

	CCMenuItemImage *pDemo2 = CCMenuItemImage::create(
		"demo2.png",
		"demo2.png",
		this,
		menu_selector(HelloWorld::menuDemo2eCallback));
	pDemo2->setPosition(ccp(visibleSize.width/4.f*3.f, visibleSize.height/2.f));

	CCMenu* pMenu = CCMenu::create(pDemo1, pDemo2, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
    
    return true;
}

void HelloWorld::menuDemo1eCallback( CCObject* pSender )
{
	CCScene* scene = Demo1::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}

void HelloWorld::menuDemo2eCallback( CCObject* pSender )
{
	CCScene* scene = Demo2::scene();
	CCDirector::sharedDirector()->replaceScene(scene);
}
