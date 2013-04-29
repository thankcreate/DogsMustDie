#include "Troops.h"
#include "Defines.h"
#include "Planet.h"
#include "Face.h"
#define DEFAULT_SPPED 55

Troops::Troops() :	
	m_pBubble(NULL),
	m_pFightUnitLabel(NULL),
	m_pHomePort(NULL),
	m_pTargetObject(NULL),	
	m_nTroopsType(kTroopsComomon),
	m_pCarriedStar(NULL),
	m_bIsInReturn(false),
	m_bHasGotStar(false),
	m_bIsHighSpeed(false),
	m_pFace(NULL)
{
}

bool Troops::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!FightObject::init());
		m_nFightType = kFightTroops;
		bRet = true;
	}while(0);

	return bRet;
}


void Troops::setFightUnitCount( int input )
{
	FightObject::setFightUnitCount(input);
	if(m_pFightUnitLabel)
	{
		CCString* pStr = CCString::createWithFormat("%d", getFightUnitCount());
		m_pFightUnitLabel->setString(pStr->getCString());
	}
}

int Troops::getMaximumUnitCount()
{
	return 50;
}


void Troops::initWithForceSide( int force )
{
	Troops::init();

	m_nForceSide = force;

	setFace(Face::createWithForceSide(force));
	m_pFace->setPosition(CCPointZero);	
	this->addChild(m_pFace);

	setBubble(CCSprite::create("Bubble.png"));
	m_pBubble->setPosition(ccp(27, -22));
	this->addChild(m_pBubble);

	CCString* pStr = CCString::createWithFormat("%d", 22);
	setFightUnitLabel(CCLabelTTF::create(pStr->getCString(), "00 Starmap Truetype.ttf", 19));
	ccColor3B ccMyOrange={255, 104, 0};
	m_pFightUnitLabel->setColor(ccMyOrange);
	m_pFightUnitLabel->setPosition(ccp(17, 15));
	m_pBubble->addChild(m_pFightUnitLabel);
}



Troops* Troops::createWithForceSide( int force )
{
	Troops* pReturn = new Troops();
	pReturn->initWithForceSide(force);
	pReturn->autorelease();
	return pReturn;
}

CCPoint Troops::getBox2dObjectSize()
{
	return ccp(44,44);
}

float Troops::getAbsoluteSpeed()
{
	if(m_bIsHighSpeed)
	{
		return DEFAULT_SPPED * 2;
	}
	return DEFAULT_SPPED;
}



void Troops::goHome()
{
	if(!m_pTargetObject || !m_pHomePort || !m_pBody)
		return;

	m_bIsInReturn = true;

	float distance = ccpDistance(m_pHomePort->getPosition(), m_pTargetObject->getPosition());
	CCPoint distanceVector = ccpSub(m_pHomePort->getPosition(), m_pTargetObject->getPosition());

	float absoluteSpeed = getAbsoluteSpeed();
	float b2SpeedX = absoluteSpeed / distance * distanceVector.x / PTM_RATIO;
	float b2SpeedY = absoluteSpeed / distance * distanceVector.y / PTM_RATIO;
	this->m_pBody->SetLinearVelocity(b2Vec2(b2SpeedX, b2SpeedY));
}

void Troops::gotoTarget()
{
	if(!m_pTargetObject || !m_pHomePort || !m_pBody)
		return;

	m_bIsInReturn = false;

	float distance = ccpDistance(m_pTargetObject->getPosition(), m_pHomePort->getPosition());
	CCPoint distanceVector = ccpSub(m_pTargetObject->getPosition(), m_pHomePort->getPosition());

	float absoluteSpeed = getAbsoluteSpeed();
	float b2SpeedX = absoluteSpeed / distance * distanceVector.x / PTM_RATIO;
	float b2SpeedY = absoluteSpeed / distance * distanceVector.y / PTM_RATIO;
	this->m_pBody->SetLinearVelocity(b2Vec2(b2SpeedX, b2SpeedY));
}

void Troops::setHasGotStar( bool got )
{
	if(m_nTroopsType != kTroopsForStar)
		return;

	m_bHasGotStar = got;
	if(got)
	{
		if(m_pCarriedStar == NULL)
		{
			setCarriedStar(CCSprite::create("Star.png"));
			m_pCarriedStar->setPosition(ccp(0, 22));
			m_pCarriedStar->setScale(0.5);
			this->addChild(m_pCarriedStar);
		}		
		m_pCarriedStar->setVisible(true);
	}
	else
	{
		if(m_pCarriedStar)
		{
			m_pCarriedStar->setVisible(false);
		}		
	}
}

void Troops::setHighSpeed( bool isHighSpeed )
{
	m_bIsHighSpeed = isHighSpeed;
	if(isHighSpeed)
	{
		if(m_pFace)
		{
			m_pFace->setWingsVisiable(true);
		}
	}
	else 
	{
		if(m_pFace)
		{
			m_pFace->setWingsVisiable(false);
		}
	}
}
