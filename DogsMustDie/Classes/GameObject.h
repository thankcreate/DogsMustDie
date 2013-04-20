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
	virtual void destroyInNextUpdate();

	bool willBeDestoried(){return m_bWillBeDestroied;}
	bool hasBeenDestroied(){return m_bHasBeenDestroied;}

	// 这里借用下isDirty这个名字，但是表达的意思与MVC模式中常见的那个isDirty没什么关系
	// 本处isDirty指该GameObject已经被删除，或者即将在下一轮update中被删除	
	// 注意: 星星的isDirty比较特殊
	virtual bool isDirty() {return (m_bWillBeDestroied || m_bHasBeenDestroied); }

protected:
	// 目前的GameObject使用的是标记删除，而不是从内存上析构掉
	// 这样虽然引起一些额外的内存消耗，但是可以减少潜在的崩溃
	bool m_bWillBeDestroied;
	bool m_bHasBeenDestroied;
};

#endif // GameObject_h__
