/**
*@file MapLayer.cpp
*@brief ����
*
*��ϸ����
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

///@brief ��ͼ�����ݳ�ʼ��
///
///��ϸ˵��
///@param[in|out] ��������in��out��ʾ���뻹�����
///@pre ǰ������
///@return ˵��
///@retval ����ֵ ˵��, ����ǿ�ѡ��
///@post ˵��������ɺ������״̬
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 11:18

void MapLayer::initData( const int rowBK, const int columnBK, const cocos2d::CCPoint center, const cocos2d::CCSize size, float moveSpeed )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/// ��ӱ�������---���Ը����Լ���Ŀ����
	m_pArrayBK = CCArray::createWithCapacity(rowBK*columnBK);
	for (int row = 0; row < rowBK; ++row)
	{
		for (int column = 0; column < columnBK; ++column)
		{
			CCSprite* bkSprite = CCSprite::create("HelloWorld.png");	///< ��������
			/// ����λ��---��������Ϊ��0,0��һ�㲻��Ҫ�䶯����
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

	/// �����ӿ���Ϣ
	m_pointCenter	= center;
	m_sizeView		= size;

	/// ��ʼ������----�ɸ����Լ���Ŀ����
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

///@brief �������ÿ�ε��
///@param[in] point---��������꣨��ת�����꣩
///@pre 
///@return ������ʱ�亯��
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 13:42
void MapLayer::dealTouch( cocos2d::CCPoint point )
{
	CCPoint positionRole	= m_pRole->getPosition();	///< ��ȡ��ɫ����λ��
	CCPoint positionMap		= this->getPosition();		///< ��ȡ��ͼ����

	m_moveVector			= -point+positionMap+positionRole;	///< ��ȡҪ�ƶ�����
	m_fMoveDistance			= 0.f;

	/// ����ʱ�亯��
	this->schedule(schedule_selector(MapLayer::onDealTouch));
}

///@brief ÿ�δ��������
///@param[in|out] 
///@pre ǰ������
///@return ˵��
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:16
void MapLayer::onDealTouch( float delta )
{
	CCPoint pointBy = ccpNormalize(m_moveVector)*m_fMoveSpeed;

	do 
	{
		/// ����Ԥ�ж������Ƿ񽫻ᳬ���ӿ���
		if (isRoleOutView(pointBy))
		{
			m_iMoveState = MAP_E_MOVE_ALL;	///< ��ͼ������һ���ƶ�
		}
		else
		{
			m_iMoveState = MAP_E_MOVE_ROLE;	///< ֻ�ƶ����Ǽ���
		}

		/// Ԥ�ж��Ƿ�ᳬ����ͼ��Ļ��
		if (isBKOut(pointBy) && m_iMoveState == MAP_E_MOVE_ALL)
		{
			m_iMoveState = MAP_E_MOVE_ROLE;
		}

		if (isCollision(ccpMult(pointBy, 2.f)))
		{
			m_iMoveState = MAP_E_MOVE_STOP;
		}

	} while (0);

	/// �����ƶ�״̬�ƶ���ͼ
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

///@brief Ԥ���жϵ�ͼ�Ƿ�ᳬ����Ļ��
///@param[in] 
///@pre ǰ������
///@return ˵��
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:27
bool MapLayer::isBKOut( cocos2d::CCPoint pointBy )
{
 	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	///< �ж������ͼ�Ƿ�ᳬ����Ļ��
	for(int i = 0; i < m_iBKColumn; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex(i);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.height/2.f > point.y)
		{
			return true;
		}
	}
	///< �ж������ͼ�Ƿ�ᳬ����Ļ��
	for(int i = 0; i < m_iBKRow; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex((i+1)*m_iBKColumn-1);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.width/2.f > point.x)
		{
			return true;
		}
	}

	///< �ж������ͼ�Ƿ�ᳬ����Ļ��
	for(int i = 0; i < m_iBKColumn; ++i)
	{
		CCSprite* bkSprite = (CCSprite*)m_pArrayBK->objectAtIndex((m_iBKRow-1)*m_iBKColumn + i);
		CCPoint point = bkSprite->getPosition() + pointBy + this->getPosition();
		if(visibleSize.height/2.f < point.y)
		{
			return true;
		}
	}

	///< �ж������ͼ�Ƿ�ᳬ����Ļ��
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

///@brief Ԥ���ж������Ƿ�ᳬ����Ļ��
///@param[in|out] ��������in��out��ʾ���뻹�����
///@pre ǰ������
///@return ˵��
///@retval ����ֵ ˵��, ����ǿ�ѡ��
///@post ˵��������ɺ������״̬
///@author DionysosLai 906391500@qq.com
///@version 1.0
///@data 2014-6-8 14:27
bool MapLayer::isRoleOutView( cocos2d::CCPoint pointBy )
{
	CCPoint pointRole = m_pRole->getPosition();				///< ��ȡ����λ��
	CCPoint subRoleMap = pointRole + this->getPosition();	///< ������λ��ת��������λ��
	CCPoint subRoleView = subRoleMap - m_pointCenter;		///< ��ȡ��������λ�����ӿ�λ��ƫ��

	if (abs(subRoleView.x - pointBy.x) > m_sizeView.width/2.f || abs(subRoleView.y - pointBy.y) > m_sizeView.height/2.f)
	{
		return true;
	}
	
	return false;
}

///@brief �򵥸���
///
///��ϸ˵��
///@param[in|out] ��������in��out��ʾ���뻹�����
///@pre ǰ������
///@return ˵��
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

///@brief �򵥸���
///
///��ϸ˵��
///@param[in|out] ��������in��out��ʾ���뻹�����
///@pre ǰ������
///@return ˵��
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