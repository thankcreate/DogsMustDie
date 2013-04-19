#include "GameObject.h"
#include "Defines.h"

GameObject::GameObject() :
	m_pBody(NULL),
	m_pWorld(NULL),
	m_fTime(0),
	m_bWillBeDestroied(false)
{

}

GameObject::~GameObject()
{

}

bool GameObject::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCSprite::init());

		bRet = true;
	}while(0);

	return bRet;
}

eGameObjectType GameObject::getType()
{
	return (eGameObjectType) GET_TYPE(this);
}

void GameObject::setType(int input)
{
	SET_TYPE(this,input);
}

void GameObject::createBox2dObject( b2World* world )
{
	m_pWorld = world;
	CCPoint size = getBox2dObjectSize();
	if(size.x == 0 || size.y == 0)
		return;

	CCPoint position = this->getPosition();
	b2BodyDef bodyDef;		

	bodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);	
	bodyDef.fixedRotation = true;

	m_pBody  = m_pWorld->CreateBody(&bodyDef);	
	m_pBody->SetType(b2_dynamicBody);
	m_pBody->SetUserData(this);
	
	b2PolygonShape shape;
	shape.SetAsBox(size.x  / 2 / PTM_RATIO, size.y / 2 / PTM_RATIO);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1;
	fixtureDef.friction =100;
	fixtureDef.restitution = 0;	
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;

	m_pBody->CreateFixture(&fixtureDef);	
}

void GameObject::myUpdate( float dt )
{
	m_fTime += dt;
	if(m_bWillBeDestroied)
	{
		m_bWillBeDestroied = false;
		if(m_pWorld && m_pBody)
		{
			m_pWorld->DestroyBody(m_pBody);
			m_pBody = NULL;
		}
		this->setVisible(false);
	}
	// To be implemented in inherit class
}

CCPoint GameObject::getBox2dObjectSize()
{
	return CCPointZero;
}


void GameObject::destroyInNextUpdate()
{
	m_bWillBeDestroied = true;
}
