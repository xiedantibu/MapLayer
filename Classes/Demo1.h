/**
*@file Demo1.h
*@brief demo1 º”‘ÿ100*100µÿÕº
*
*œÍœ∏∏≈ ˆ
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-14 21:59
*/
#ifndef __DEMO1_SCENE_H__
#define __DEMO1_SCENE_H__

#include "cocos2d.h"
#include "MapLayer.h"

class Demo1 : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(Demo1);
public:
	MapLayer* m_map;

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

	virtual void draw();
};

#endif // __DEMO1_SCENE_H__
