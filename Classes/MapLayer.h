/**
*@file MapLayer.h
*@brief 地图层实现
*
*详细概述
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

	virtual void update(float delta);

public:
	///@brief 创建地图层---可以根据自己项目需要，更改源代码
	///@param[in] 参数名，rowBK---背景行数， columnBK--地图列数 center---视口中心（如果在屏幕中心，就是 visibleSize.width/2.f, visibleSize.height/2）
	/// size---视口大小 为0就是一个点
	///@pre 地图背景--和主角数据等，可以自己在源代码内添加
	///@return 说明
	static MapLayer* create(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);
	virtual bool init(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);

///@brief 处理外界每次点击
///@param[in] point---外界点击坐标（需转换坐标）
///@pre 
///@return 将开启时间函数
	void dealTouch(cocos2d::CCPoint point);

///@brief 判断主角是否和物体碰撞
///@param[in|out] 参数名，in，out表示输入还是输出
///@pre 前者条件
///@return 说明
	bool isCollision(cocos2d::CCPoint pointBy);
///@brief 判断两个矩形是否相交
///@param[in] a0---矩形1 aWidth--矩形1的宽度 aHeight---矩形1的高度
///@pre 
///@return true---相交 false---不相交
	bool isCollsionRect(cocos2d::CCPoint a0, float aWidth, float aHeight, 
		cocos2d::CCPoint b0, float bWight, float bHeight);
protected:
///@brief 每次处理外界点击
///@param[in|out] 
///@pre 前者条件
///@return 
	void onDealTouch(float delta);

private:
	enum	/// 图层顺序
	{
		ZBK = -1,		///< 背景
		ZMATTER,		///< 物品
		ZROLE,			///< 主角
	};

	enum	/// 移动状态
	{
		MAP_E_MOVE_ALL,		///< 地图和角色均移动
		MAP_E_MOVE_ROLE,	///< 角色移动
		MAP_E_MOVE_STOP,	///< 地图和角色均不能移动
	};

private:
	void initData(const int rowBK, const int columnBK, const cocos2d::CCPoint center, 
		const cocos2d::CCSize size, float moveSpeed);
///@brief 预先判断地图是否会超出屏幕外
///@param[in] point--地图移动向量
///@pre 
///@return true--会 false--不会
	void adjustBK(cocos2d::CCPoint pointBy);

///@brief 预先判断主角是否会超出屏幕外
///@param[in] pointBy--主角移动向量
///@pre 
///@return true--会 false--不会
	bool isRoleInView(cocos2d::CCPoint pointBy);

///@brief 判断哪些地图不在视口内，就不显示
///@param[] void
///@pre 在update内，每一帧都要调用
///@return 
	void setMapVisible(void);

///@brief 判断角色是否向视口移动趋势
///@param[in] pointBy--主角移动向量
///@pre 
///@return 
	bool roleToView(cocos2d::CCPoint pointBy);

	cocos2d::CCArray* m_pArrayBK;		///< 背景地图对象
	int m_iBKRow;						///< 背景地图行数
	int m_iBKColumn;					///< 背景地图列数

	cocos2d::CCPoint m_pointCenter;		///< 视口中心点
	cocos2d::CCSize m_sizeView;			///< 视口大小

	cocos2d::CCSprite* m_pRole;			///< 地图主角----这个参数 可以根据自己项目更改

	float m_fMoveDistance;				///< 记录每次移动的距离
	cocos2d::CCPoint m_moveVector;		///< 移动向量
	float m_fMoveSpeed;					///< 移动速度

	int m_iMoveState;					///< 移动状态

	cocos2d::CCSprite*  m_matter;

};