/**
*@file MapLayer.cpp
*@brief 概述
*
*详细概述
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-8 11:09
*/
#include "MapLayer.h"

USING_NS_CC;

MapLayer::MapLayer()
{

}

MapLayer::~MapLayer()
{

}

MapLayer* MapLayer::create( const int rowBK, const int columnBK, const cocos2d::CCPoint center, const cocos2d::CCSize size, float moveSpeed)
{
	MapLayer* pRet = new MapLayer();
	if (pRet && pRet->init(rowBK, columnBK, center, size, moveSpeed))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool MapLayer::init( const int rowBK, const int columnBK, const cocos2d::CCPoint center, const cocos2d::CCSize size, float moveSpeed )
{
	if (!CCLayer::init())
	{
		return false;
	}

	initData(rowBK, columnBK, center, size, moveSpeed);
	return true;
}

///@brief 地图层数据初始化
///
///详细说明
///@param[in|out] 参数名，in，out表示输入还是输出
///@pre 前者条件
///@return 说明
///@retval 返回值 说明, 这个是可选的
///@post 说明函数完成后的世界状态
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 11:18

void MapLayer::initData( const int rowBK, const int columnBK, const cocos2d::CCPoint center, const cocos2d::CCSize size, float moveSpeed )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/// 添加背景精灵---可以根据自己项目更改
	m_pArrayBK = CCArray::createWithCapacity(rowBK*columnBK);
	for (int row = 0; row < rowBK; ++row)
	{
		for (int column = 0; column < columnBK; ++column)
		{
			CCSprite* bkSprite = CCSprite::create("HelloWorld.png");	///< 创建精灵
			/// 设置位置---中心设置为（0,0）一般不需要变动代码
			CCPoint point;
			if (0 == columnBK%2)
			{
				point.x = (column-columnBK/2)*visibleSize.width + visibleSize.width/2.f;
			}
			else
			{
				point.x = (column-columnBK/2)*visibleSize.width;
			}

			if (0 == rowBK%2)
			{
				point.y = (rowBK/2-row)*visibleSize.height - visibleSize.height/2.f;
			}
			else
			{
				point.y = (rowBK/2-row)*visibleSize.height;
			}
			bkSprite->setPosition(point);
			this->addChild(bkSprite, ZBK);

			m_pArrayBK->addObject(bkSprite);
		}
	}

	m_pArrayBK->retain();

	/// 设置视口信息
	m_pointCenter	= center;
	m_sizeView		= size;

	/// 初始化主角----可根据自己项目更改
	m_pRole = CCSprite::create("CloseNormal.png");
	m_pRole->setPosition(ccp(0,0));
	this->addChild(m_pRole, ZROLE);

	m_fMoveDistance = 0.f;
	m_fMoveSpeed	= moveSpeed;
	m_iMoveState	= MAP_E_MOVE_ALL;
	m_iBKRow		= rowBK;
	m_iBKColumn		= columnBK;

	m_matter = CCSprite::create("CloseNormal.png");
	m_matter->setPosition(ccp(200, 200));
	this->addChild(m_matter);
}

///@brief 处理外界每次点击
///@param[in] point---外界点击坐标（需转换坐标）
///@pre 
///@return 将开启时间函数
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 13:42
void MapLayer::dealTouch( cocos2d::CCPoint point )
{
	CCPoint positionRole	= m_pRole->getPosition();	///< 获取角色坐标位置
	CCPoint positionMap		= this->getPosition();		///< 获取地图坐标

	m_moveVector			= -point+positionMap+positionRole;	///< 获取要移动向量
	m_fMoveDistance			= 0.f;

	/// 开启时间函数
	this->schedule(schedule_selector(MapLayer::onDealTouch));
}

///@brief 每次处理外界点击
///@param[in|out] 
///@pre 前者条件
///@return 说明
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:16
void MapLayer::onDealTouch( float delta )
{
	CCPoint pointBy = ccpNormalize(m_moveVector)*m_fMoveSpeed;

	do 
	{
		/// 首先预判断主角是否将会超出视口外
		if (isRoleOutView(pointBy))
		{
			m_iMoveState = MAP_E_MOVE_ALL;	///< 地图和主角一起移动
		}
		else
		{
			m_iMoveState = MAP_E_MOVE_ROLE;	///< 只移动主角即可
		}

		/// 预判断是否会超出地图屏幕外
		if (isBKOut(pointBy) && m_iMoveState == MAP_E_MOVE_ALL)
		{
			m_iMoveState = MAP_E_MOVE_ROLE;
		}

		if (isCollision(ccpMult(pointBy, 2.f)))
		{
			m_iMoveState = MAP_E_MOVE_STOP;
		}

	} while (0);

	/// 根据移动状态移动地图
	switch (m_iMoveState)
	{
	case MAP_E_MOVE_ALL:
		{
			CCPoint pointMap = this->getPosition();
			pointMap = pointMap + pointBy;
			this->setPosition(pointMap);

			CCPoint pointRole = m_pRole->getPosition();
			pointRole = pointRole - pointBy;
			m_pRole->setPosition(pointRole);
		}
		break;
	case MAP_E_MOVE_ROLE:
		{
			CCPoint pointRole = m_pRole->getPosition();
			pointRole = pointRole - pointBy;
			m_pRole->setPosition(pointRole);
		}
		break;
	case MAP_E_MOVE_STOP:
		{
			CCPoint pointRole = m_pRole->getPosition();
			pointRole = pointRole + ccpMult(pointBy, 2.f);
			m_pRole->setPosition(pointRole);
			this->unschedule(schedule_selector(MapLayer::onDealTouch));
		}
		break;
	default:
		break;
	}

	m_fMoveDistance = m_fMoveDistance + m_fMoveSpeed;
	float length = ccpLength(m_moveVector);
	if (length < m_fMoveDistance)
	{
		this->unschedule(schedule_selector(MapLayer::onDealTouch));
	}
}

///@brief 预先判断地图是否会超出屏幕外
///@param[in] 
///@pre 前者条件
///@return 说明
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:27
bool MapLayer::isBKOut( cocos2d::CCPoint pointBy )
{
 	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	///< 判断上面地图是否会超出屏幕外
	for(int i = 0; i < m_iBKColumn; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex(i);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.height/2.f > point.y)
		{
			return true;
		}
	}
	///< 判断右面地图是否会超出屏幕外
	for(int i = 0; i < m_iBKRow; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex((i+1)*m_iBKColumn-1);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.width/2.f > point.x)
		{
			return true;
		}
	}

	///< 判断下面地图是否会超出屏幕外
	for(int i = 0; i < m_iBKColumn; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex((m_iBKRow-1)*m_iBKColumn + i);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.height/2.f < point.y)
		{
			return true;
		}
	}

	///< 判断左面地图是否会超出屏幕外
	for(int i = 0; i < m_iBKRow; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex(i*m_iBKColumn);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.width/2.f < point.x)
		{
			return true;
		}
	}

	return false;
}

///@brief 预先判断主角是否会超出屏幕外
///@param[in|out] 参数名，in，out表示输入还是输出
///@pre 前者条件
///@return 说明
///@retval 返回值 说明, 这个是可选的
///@post 说明函数完成后的世界状态
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:27
bool MapLayer::isRoleOutView( cocos2d::CCPoint pointBy )
{
	CCPoint pointRole = m_pRole->getPosition();				///< 获取主角位置
	CCPoint subRoleMap = pointRole + this->getPosition();	///< 将主角位置转换成世界位置
	CCPoint subRoleView = subRoleMap - m_pointCenter;		///< 获取主角世界位置与视口位置偏差

	if (abs(subRoleView.x - pointBy.x) > m_sizeView.width/2.f || abs(subRoleView.y - pointBy.y) > m_sizeView.height/2.f)
	{
		return true;
	}
	
	return false;
}

///@brief 简单概述
///
///详细说明
///@param[in|out] 参数名，in，out表示输入还是输出
///@pre 前者条件
///@return 说明
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 18:46
bool MapLayer::isCollision( cocos2d::CCPoint pointBy)
{
	if (isCollsionRect(m_pRole->getPosition()-pointBy, m_pRole->getContentSize().width/2.f, m_pRole->getContentSize().height/2.f,
		m_matter->getPosition(), m_matter->getContentSize().width/2.f, m_matter->getContentSize().height/2.f))
	{
		return true;
	}

	return false;
}

///@brief 简单概述
///
///详细说明
///@param[in|out] 参数名，in，out表示输入还是输出
///@pre 前者条件
///@return 说明
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 18:52
bool MapLayer::isCollsionRect( cocos2d::CCPoint a0, float aWidth, float aHeight, cocos2d::CCPoint b0, float bWight, float bHeight )
{
	float distanceX = abs(a0.x - b0.x);
	float distanceY = abs(a0.y - b0.y);

	if (distanceX < (aWidth + bWight)/2.f && distanceY < (aHeight + bHeight)/2.f)
	{
		return true;
	}
	
	return false;
}