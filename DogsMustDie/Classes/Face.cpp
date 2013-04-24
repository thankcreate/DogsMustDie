#include "Face.h"
#include "Defines.h"



Face::Face() :
	m_nForceSide(kForceSideCat),
	m_pLeftWing(NULL),
	m_pRightWing(NULL),
	m_bIsInCry(false)
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
	else if(m_nForceSide == kForceSideMiddle)
	{
		int index = CCRANDOM_0_1() * 3;
		//  ��һ������0 - 3֮�������������Ҫȥ��3
		if(index == 3)
			index = 2;
		CCString* pLogoFileName = CCString::createWithFormat("Middle_logo_%d.png", index);
		this->initWithFile(pLogoFileName->getCString());
	}

	if(m_pLeftWing)
		setWingsVisiable(m_pLeftWing->isVisible());
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
	if(m_nForceSide == kForceSideMiddle)
		return;

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

void Face::restore(float dt)
{	
	m_bIsInCry = false;
	if(m_nForceSide == kForceSideCat)
	{
		this->initWithFile("Cat_normal.png");
	}
	else if(m_nForceSide == kForceSideDog)
	{
		this->initWithFile("Dog_normal.png");
	}
}

// ���ڻ����һ��cry������δrestore���ڼ��ִ�������һ��cry
// ��Ҫ�ں�һ��cry�н�ǰһ��restore�Ӷ�����ȡ��
// ���Ե�ǰΪʱ��㣬����scheduleһ��restore
void Face::cry()
{
	if(m_nForceSide == kForceSideMiddle)
		return;

	if(!m_bIsInCry)
	{
		if(m_nForceSide == kForceSideCat)
		{
			this->initWithFile("Cat_cry.png");
		}
		else if(m_nForceSide == kForceSideDog)
		{
			this->initWithFile("Dog_cry.png");
		}
		m_bIsInCry = true;
	}
	else
	{
		this->unschedule(schedule_selector(Face::restore));
	}

	this->scheduleOnce(schedule_selector(Face::restore), CRY_DURATION);
}


