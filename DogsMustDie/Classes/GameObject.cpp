#include "GameObject.h"


GameObject::GameObject() :
	m_pBody(NULL),
	m_pWorld(NULL)
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
	// To be implemented in inherit class
}


