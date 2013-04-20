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

	virtual void myUpdate(float dt);

	b2Body *m_pBody;
	b2World *m_pWorld;

	float m_fTime;


	virtual CCPoint getBox2dObjectSize();
	virtual void destroyInNextUpdate();

	bool willBeDestoried(){return m_bWillBeDestroied;}
	bool hasBeenDestroied(){return m_bHasBeenDestroied;}

	// ���������isDirty������֣����Ǳ�����˼��MVCģʽ�г������Ǹ�isDirtyûʲô��ϵ
	// ����isDirtyָ��GameObject�Ѿ���ɾ�������߼�������һ��update�б�ɾ��	
	// ע��: ���ǵ�isDirty�Ƚ�����
	virtual bool isDirty() {return (m_bWillBeDestroied || m_bHasBeenDestroied); }

protected:
	// Ŀǰ��GameObjectʹ�õ��Ǳ��ɾ���������Ǵ��ڴ���������
	// ������Ȼ����һЩ������ڴ����ģ����ǿ��Լ���Ǳ�ڵı���
	bool m_bWillBeDestroied;
	bool m_bHasBeenDestroied;
};

#endif // GameObject_h__
