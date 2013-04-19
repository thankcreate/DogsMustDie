#include "Planet.h"
#include "Defines.h"
#include "Face.h"
#include "FightObject.h"

#define  DEFAULT_COUNT 50

#define BASE_INCREASE_INTERVAL 2.0f
#define LEVEL_COEFFICIENT 0.2

Planet::Planet() :	
	m_pFace(NULL),
	m_pFightUnitLabel(NULL),
	m_nLevel(0),
	m_fLastTimeIncreased(0)
{
	m_nFightUnitCount = DEFAULT_COUNT;
}



bool Planet::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!FightObject::init());		
		m_nFightType = kFightPlanet;
		bRet = true;
	}while(0);

	return bRet;
}

void Planet::setFightUnitCount( int input )
{
	FightObject::setFightUnitCount(input);
	if(m_pFightUnitLabel)
	{
		CCString* pStr = CCString::createWithFormat("%d", getFightUnitCount());
		m_pFightUnitLabel->setString(pStr->getCString());
	}
}

int Planet::getMaximumUnitCount()
{
	return 50;
}

void Planet::initWithForceSide( int force )
{
	Planet::init();
	m_nForceSide = force;
	
	// 星球
	if(force == kForceSideCat)
	{
		initWithFile("Planet_cat.png");
	}
	else if(force == kForceSideDog)
	{
		initWithFile("Planet_dog.png");
	}
	else
	{
		return;
	}

	// 中间的脸
	CCSize planetSize = boundingBox().size;
	if(!m_pFace)
	{
		Face* pFace = Face::createWithForceSide(force);
		setFace(pFace);
		m_pFace->setPosition(ccp(planetSize.width / 2 - 2, planetSize.height / 2 - 3));
		this->addChild(m_pFace);
	}
	else
		m_pFace->initWithForceSide(force);
	

	// 右上角的数字
	CCString* pStr = CCString::createWithFormat("%d",  getFightUnitCount());
	if(!m_pFightUnitLabel)
	{
		setFightUnitLabel(CCLabelTTF::create(pStr->getCString(), "00 Starmap Truetype.ttf", 19));
		ccColor3B ccMyOrange={255, 104, 0};
		m_pFightUnitLabel->setColor(ccMyOrange);
		m_pFightUnitLabel->setPosition(ccp(planetSize.width - 14 , planetSize.height - 16));
		this->addChild(m_pFightUnitLabel);
	}
	else
		m_pFightUnitLabel->setString(pStr->getCString());


	// b2Body创建	
}



Planet* Planet::createWithForceSide( int force )
{
	Planet* pReturn = new Planet();
	pReturn->initWithForceSide(force);
	pReturn->autorelease();
	return pReturn;
}

float Planet::getIncreaseInterval()
{
	float coe = 1;
	for(int i = 0 ; i < m_nLevel; i++)
	{
		coe *= (1 - LEVEL_COEFFICIENT);
	}
	return BASE_INCREASE_INTERVAL * coe;
}


void Planet::myUpdate(float dt)
{
	FightObject::myUpdate(dt);
	if(m_fTime - m_fLastTimeIncreased > getIncreaseInterval())
	{
		m_fLastTimeIncreased = m_fTime;
		increaseFightUnitCount(1);
	}
}

CCPoint Planet::getBox2dObjectSize()
{
	return ccp(60, 60);
}
