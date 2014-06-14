/**
*@file Demo2.h
*@brief demo2， 一个简单类似《天天酷跑》游戏---只有地图驱动
*
*详细概述
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-14 22:10
*/

#ifndef __DEMO2_SCENE_H__
#define __DEMO2_SCENE_H__

#include "cocos2d.h"
#include "MapLayer.h"

class Demo2 : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(Demo2);
public:
	MapLayer* m_map;

};

#endif // __DEMO2_SCENE_H__