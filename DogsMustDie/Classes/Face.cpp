#include "Face.h"
#include "Defines.h"

Face::Face() :
	m_nForceSide(kForceSideCat)
{

}

void Face::initWithForceSide( int force )
{	
	CCSprite::init();

	m_nForceSide = force;
	if(m_nForceSide == kForceSideCat)
	{
		this->initWithFile("Cat_normal.png");
	}
	else if(m_nForceSide == kForceSideDog)
	{
		this->initWithFile("Dog_normal.png");
	}
}

Face* Face::createWithForceSide( int force )
{
	Face* pReturn = new Face();
	pReturn->initWithForceSide(force);
	pReturn->autorelease();

	return pReturn;
}


