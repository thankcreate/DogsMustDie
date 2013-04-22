#include "Face.h"
#include "Defines.h"

Face::Face() :
	m_nForceSide(kForceSideCat),
	m_pLeftWing(NULL),
	m_pRightWing(NULL)
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

void Face::setWingsVisiable( bool visible )
{
	if(!m_pLeftWing)
	{
		if(m_nForceSide == kForceSideCat)
			setLeftWing(CCSprite::create("Cat_wing.png"));
		else if(m_nForceSide == kForceSideDog)
			setLeftWing(CCSprite::create("Dog_wing.png"));
		m_pLeftWing->setPosition(ccp(-6, 20));
		this->addChild(m_pLeftWing);
	}

	if(!m_pRightWing)
	{
		if(m_nForceSide == kForceSideCat)
			setRightWing(CCSprite::create("Cat_wing.png"));
		else if(m_nForceSide == kForceSideDog)
			setRightWing(CCSprite::create("Dog_wing.png"));
		m_pRightWing->setScaleX(-1);
		m_pRightWing->setPosition(ccp(52, 20));
		this->addChild(m_pRightWing);
	}

	m_pLeftWing->setVisible(visible);
	m_pRightWing->setVisible(visible);


}


