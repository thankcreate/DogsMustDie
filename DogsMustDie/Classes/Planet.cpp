#include "Planet.h"
#include "Defines.h"
#include "Face.h"
#include "FightObject.h"
#include "Rank.h"

#define DEFAULT_COUNT 50
#define BASE_INCREASE_INTERVAL 2.0f
#define LEVEL_COEFFICIENT 0.15f
#define SLOW_DOWN_COEFIICIENT 0.2f
#define SLOW_DOWN_DURATION 12.0f

Planet::Planet() :	
	m_pFace(NULL),
	m_pFightUnitLabel(NULL),
	m_nLevel(0),
	m_fLastTimeIncreased(0),
	m_pRank(NULL),
	m_bSpeedUped(false),
	m_pSlowDownMark(NULL),
	m_bSlowDowned(false),
	m_bIncreaseStopped(false)
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
	//if(input > getMaximumUnitCount())
	//	input = getMaximumUnitCount();
	FightObject::setFightUnitCount(input);
	if(m_pFightUnitLabel)
	{
		CCString* pStr = CCString::createWithFormat("%d", getFightUnitCount());
		m_pFightUnitLabel->setString(pStr->getCString());
	}
}

int Planet::getMaximumUnitCount()
{
	return 30 + 10 * m_nLevel;
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
	else if(force == kForceSideThird)
	{
		initWithFile("Planet_third.png");
	}
	else if(force == kForceSideMiddle)
	{
		initWithFile("Planet_middle.png");
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
		m_pFace->setPosition(ccp(planetSize.width / 2 + 3, planetSize.height / 2 - 3));
		this->addChild(m_pFace);
	}
	else
		m_pFace->initWithForceSide(force);

	
	

	// 右上角的数字
	CCString* pStr = CCString::createWithFormat("%d",  getFightUnitCount());
	if(!m_pFightUnitLabel)
	{
		setFightUnitLabel(CCLabelTTF::create(" ", "00 Starmap Truetype.ttf", 19));		
		m_pFightUnitLabel->setPosition(ccp(planetSize.width - 16 , planetSize.height - 16));
		this->addChild(m_pFightUnitLabel);
	}

	if(m_nForceSide != kForceSideMiddle)
	{
		ccColor3B ccMyOrange={255, 104, 0};
		m_pFightUnitLabel->setColor(ccMyOrange);
	}
	else
	{	
		ccColor3B ccMyGray={72, 72, 72};
		m_pFightUnitLabel->setColor(ccMyGray);
	}
	m_pFightUnitLabel->setString(pStr->getCString());


	// 每次init之后stopped都会被置为false
	// 主要是因为当把一个middel星设为stop后，被另一方占领需要自动恢复成正常增加
	m_bIncreaseStopped =false;
	// b2Body创建

	// setLevel(0);
	slowDownRestore(0);
	setScale(1);
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

	if(m_bSlowDowned)
	{
		coe *= (1 / (1 - SLOW_DOWN_COEFIICIENT));
	}

	return BASE_INCREASE_INTERVAL * coe;
}


void Planet::myUpdate(float dt)
{
	FightObject::myUpdate(dt);
	if(!m_bIncreaseStopped && m_fTime - m_fLastTimeIncreased > getIncreaseInterval())
	{
		m_fLastTimeIncreased = m_fTime;
		increaseFightUnitCount(1);
	}
}

CCPoint Planet::getBox2dObjectSize()
{
	return ccp(60, 60);
}

void Planet::levelUp()
{
	setLevel(m_nLevel + 1);
}

void Planet::setLevel(int level)
{
	if(level < 0 || level > MAX_PLANET_LEVEL)
		return;
	m_nLevel = level;

	if(!m_pRank)
	{
		setRank(Rank::createWithCount(level));
		m_pRank->setPosition(ccp(113,8));
		this->addChild(m_pRank);
	}
	else
	{
		m_pRank->initWithCount(level);
	}
	
}

void Planet::speedUp()
{
	m_bSpeedUped = true;
	
	if(m_pFace)
	{
		m_pFace->setWingsVisiable(true);
	}
}

void Planet::clearSpeedUp()
{
	m_bSpeedUped = false;

	if(m_pFace)
	{
		m_pFace->setWingsVisiable(false);
	}
}

void Planet::slowDown()
{
	// 当前的逻辑禁止在一个减速期间叠加另一个减速
	if(m_bSlowDowned)
		return;

	m_bSlowDowned = true;	

	if(!m_pSlowDownMark)
	{
		setSlowDownMark(CCSprite::create());
		m_pSlowDownMark->setPosition(ccp(113,65));
		this->addChild(m_pSlowDownMark);
	}

	m_pSlowDownMark->setVisible(true);	

	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("SlowDownMark.plist");
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_0.png"));	
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_1.png"));	
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_2.png"));	
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_3.png"));	
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_4.png"));	
	animation->addSpriteFrame(cache->spriteFrameByName("SlowDownMark_4.png"));
	animation->setDelayPerUnit(0.2f);
	CCAnimate* animate = CCAnimate::create(animation);
	m_pSlowDownMark->runAction(CCRepeatForever::create(animate));	

	this->scheduleOnce(schedule_selector(Planet::slowDownRestore) , SLOW_DOWN_DURATION);

	if(m_pFace)
		m_pFace->cry();
}

void Planet::slowDownRestore(float dt)
{
	this->unschedule(schedule_selector(Planet::slowDownRestore));
	if(!m_pSlowDownMark || !m_bSlowDowned)
		return;

	m_pSlowDownMark->setVisible(false);
	m_bSlowDowned = false;
	m_pSlowDownMark->stopAllActions();
}

void Planet::cry()
{
	if(m_pFace)
		m_pFace->cry();
}

void Planet::stopIncrease()
{
	m_bIncreaseStopped = true;
}

void Planet::startIncrease()
{
	m_bIncreaseStopped = false;
}