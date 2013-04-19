#ifndef GameObject_h__
#define GameObject_h__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "Defines.h"

using namespace cocos2d;
// 注意，“绝对禁止”对CCSprite使用getTag或是setTag
// 因为Tag现在已被我分成两段，高段存type，低段存tag
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

	virtual void myUpdate(float dt);

	b2Body *m_pBody;
	b2World *m_pWorld;

	float m_fTime;


	virtual CCPoint getBox2dObjectSize();
	void destroyInNextUpdate();
	bool isWillBeDestoried(){return m_bWillBeDestroied;}
private:
	bool m_bWillBeDestroied;
};

#endif // GameObject_h__
