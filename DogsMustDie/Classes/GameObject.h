#ifndef GameObject_h__
#define GameObject_h__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "Defines.h"

using namespace cocos2d;
// ע�⣬�����Խ�ֹ����CCSpriteʹ��getTag����setTag
// ��ΪTag�����ѱ��ҷֳ����Σ��߶δ�type���Ͷδ�tag
class GameObject : public CCSprite
{
public:
	GameObject();
	~GameObject();
	CREATE_FUNC(GameObject);

	bool init();

	virtual void createBox2dObject(b2World* world);

	eGameObjectType getType();
	void setType(int input);

	b2Body *m_pBody;
	b2World *m_pWorld;
};

#endif // GameObject_h__