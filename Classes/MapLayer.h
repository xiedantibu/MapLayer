/**
*@file MapLayer.h
*@brief ��ͼ��ʵ��
*
*��ϸ����
*
*@author DionysosLai email:906391500@qq.com
*@version 1.0
*@data 2014-6-8 10:57
*/

#include "cocos2d.h"

class MapLayer : public cocos2d::CCLayer
{
public:
	MapLayer();
	virtual ~MapLayer();

public:
	///@brief ������ͼ��---���Ը����Լ���Ŀ��Ҫ������Դ����
	///@param[in] ��������rowBK---���������� columnBK--��ͼ���� center---�ӿ����ģ��������Ļ���ģ����� visibleSize.width/2.f, visibleSize.height/2��
	/// size---�ӿڴ�С Ϊ0����һ����
	///@pre ��ͼ����--���������ݵȣ������Լ���Դ���������
	///@return ˵��
	static MapLayer* create(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);
	virtual bool init(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);

	///@brief �������ÿ�ε��
	///@param[in] point---��������꣨��ת�����꣩
	///@pre 
	///@return ������ʱ�亯��
	void dealTouch(cocos2d::CCPoint point);

	///@brief �ж������Ƿ��������ײ
	///@param[in|out] ��������in��out��ʾ���뻹�����
	///@pre ǰ������
	///@return ˵��
	bool isCollision(cocos2d::CCPoint pointBy);

	bool isCollsionRect(cocos2d::CCPoint a0, float aWidth, float aHeight, 
		cocos2d::CCPoint b0, float bWight, float bHeight);
protected:
	///@brief ÿ�δ��������
	///@param[in|out] 
	///@pre ǰ������
	///@return 
	void onDealTouch(float delta);

private:
	enum	/// ͼ��˳��
	{
		ZBK = -1,		///< ����
		ZMATTER,		///< ��Ʒ
		ZROLE,			///< ����
	};

	enum	/// �ƶ�״̬
	{
		MAP_E_MOVE_ALL,		///< ��ͼ�ͽ�ɫ���ƶ�
		MAP_E_MOVE_ROLE,	///< ��ɫ�ƶ�
		MAP_E_MOVE_STOP,	///< ��ͼ�ͽ�ɫ�������ƶ�
	};

private:
	void initData(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);
	///@brief Ԥ���жϵ�ͼ�Ƿ�ᳬ����Ļ��
	///@param[in] point--��ͼ�ƶ�����
	///@pre ǰ������
	///@return true--�� false--����
	bool isBKOut(cocos2d::CCPoint pointBy);
	///@brief Ԥ���ж������Ƿ�ᳬ����Ļ��
	///@param[in] point--��ͼ�ƶ�����
	///@pre ǰ������
	///@return true--�� false--����
	bool isRoleOutView(cocos2d::CCPoint pointBy);

	cocos2d::CCArray* m_pArrayBK;		///< ������ͼ����
	int m_iBKRow;						///< ������ͼ����
	int m_iBKColumn;					///< ������ͼ����

	cocos2d::CCPoint m_pointCenter;		///< �ӿ����ĵ�
	cocos2d::CCSize m_sizeView;			///< �ӿڴ�С

	cocos2d::CCSprite* m_pRole;			///< ��ͼ����----������� ���Ը����Լ���Ŀ����

	float m_fMoveDistance;				///< ��¼ÿ���ƶ��ľ���
	cocos2d::CCPoint m_moveVector;		///< �ƶ�����
	float m_fMoveSpeed;					///< �ƶ��ٶ�

	int m_iMoveState;					///< �ƶ�״̬

	cocos2d::CCSprite*  m_matter;

};