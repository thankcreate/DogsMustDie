#include "StageBaseLayer.h"
#include "StageSelectScene.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
#include "StageBaseScene.h"
#include "LineLayer.h"
#include "Planet.h"
#include "StarObject.h"
#include "CatTroops.h"
#include "StarObject.h"
#include "Box2D/Box2D.h"
#include "AudioManager.h"
#include "MiscTool.h"
#include "ForceSideInfo.h"


StageBaseLayer::StageBaseLayer()  :
	m_pParentScene(NULL),
	m_bIsSpeakerEnabled(false),
	m_pSpeakerBtn(NULL),	
	m_pLineLayer(NULL),
	m_pPlanetArray(NULL),
	m_pFrontSight(NULL),
	m_pFromObject(NULL),
	m_pToObject(NULL),
	m_pStarArray(NULL),
	m_pWorld(NULL),
	m_pUpdateArray(NULL),
	m_bIsUpdateStopped(false),
	m_pTroopsArray(NULL),
	m_pStarCountLabel(NULL),
	m_pFocusMark(NULL),
	m_pSkillUpgradeBtn(NULL),
	m_pSkillSpeedBtn(NULL),
	m_pSkillDownBtn(NULL),
	m_pFocusedPlanet(NULL),
	m_bInDeadOrWinState(NULL),
	m_fTime(0),
	m_nUnitLost(0),
	m_pLevelBorder(NULL),
	m_pLevelLabel(NULL),
	m_fLastRefreshAITime(0),
	m_fLastAddStarTime(0),	
	m_nLastAddStarIndex(-1),
	m_pForceInfoDic(NULL),
	m_bIsAIStopped(false)
{
	setPlanetArray(CCArray::createWithCapacity(30));
	setStarArray(CCArray::createWithCapacity(10));
	setUpdateArray(CCArray::createWithCapacity(100));
	setTroopsArray(CCArray::createWithCapacity(100));
	setForceInfoDic(CCDictionary::create());
}

StageBaseLayer::~StageBaseLayer()
{
	CC_SAFE_RELEASE(m_pPlanetArray);	
	CC_SAFE_RELEASE(m_pStarArray);	
	CC_SAFE_RELEASE(m_pUpdateArray);
	CC_SAFE_RELEASE(m_pTroopsArray);	
	CC_SAFE_RELEASE(m_pForceInfoDic);	
}

bool StageBaseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		initForceSideInfo();  // �����÷��ʼ
		initBackground();
		initLevelPannel();
		initBackButton();		
		initLineLayer();
		initPannel();
		initFrontSight();
		initFocusMark();

		initWorld();
		initPlanets();
		

		// ����Update
		this->scheduleUpdate();

		// ��Ҫ֧����ק
		this->setTouchEnabled(true);


		PreloadEffect("Audio_fight.mp3");
		PreloadEffect("Audio_button.mp3");
		PreloadEffect("Audio_skill_down.mp3");
		PreloadEffect("Audio_cat_mew.mp3");

		bRet = true;
	} while (0);

	return bRet;
}

// ��ʼ�����������ĳ�ʼ����
// Ŀǰ��ʵֻ�г�ʼ������
void StageBaseLayer::initForceSideInfo()
{
	m_pForceInfoDic->setObject(ForceSideInfo::create(kForceSideCat, 0) , kForceSideCat);
	m_pForceInfoDic->setObject(ForceSideInfo::create(kForceSideDog, 0) , kForceSideDog);
	m_pForceInfoDic->setObject(ForceSideInfo::create(kForceSideThird, 0) , kForceSideThird);
}

// level��Ҫ��back button֮ǰadd��ȥ,��Ȼ�����в���back button���ڵ�
void StageBaseLayer::initLevelPannel()
{
	CCSize winSize = WIN_SIZE;
	setLevelBorder(CCSprite::create("StageBase_level_border.png"));
	CCSize borderSize = m_pLevelBorder->boundingBox().size;
	m_pLevelBorder->setPosition(ccp(142, winSize.height - borderSize.height / 2));
	this->addChild(m_pLevelBorder, kPannelLayerIndex);
		
	setLevelLabel(CCLabelTTF::create(" ", "8bitoperator JVE.ttf", 24));
	ccColor3B ccMyOrange={255, 104, 0};
	m_pLevelLabel->setColor(ccMyOrange);	
	m_pLevelLabel->setPosition(ccp(borderSize.width / 2 - 2 ,20));
	m_pLevelBorder->addChild(m_pLevelLabel);
}



void StageBaseLayer::setLevel(int big, int small1)
{
	CCString* pStrLevel = CCString::createWithFormat("Stage %d-%d", big, small1);
	m_pLevelLabel->setString(pStrLevel->getCString());
}

void StageBaseLayer::initPlanets()
{

}

Planet* StageBaseLayer::makePlanet(int force, CCPoint position, int fightUnitCount, int level)
{
	Planet* pPlanet = Planet::createWithForceSide(force);

	pPlanet->setPosition(position);
	pPlanet->setFightUnitCount(fightUnitCount);
	pPlanet->setLevel(level);

	m_pPlanetArray->addObject(pPlanet);
	m_pUpdateArray->addObject(pPlanet);
	pPlanet->createBox2dObject(m_pWorld);
	this->addChild(pPlanet, kPlanetLayerIndex);

	return pPlanet;
}

StarObject* StageBaseLayer::makeStar(CCPoint position)
{
	StarObject* pStar = StarObject::create();
	pStar->setPosition(position);
	pStar->createBox2dObject(m_pWorld);
	this->addChild(pStar, kPlanetLayerIndex);	
	getStarArray()->addObject(pStar);
	getUpdateArray()->addObject(pStar);

	return pStar;	
}

void StageBaseLayer::initBackground()
{
	// Bkg
	CCSize size = WIN_SIZE;
	CCSprite* pBkg = CCSprite::create(getBKGFileName());
	pBkg->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(pBkg);
}

void StageBaseLayer::initBackButton()
{
	CCSize size = WIN_SIZE;
	// Back
	CCMenu* pMenu = CCMenu::create(NULL);
	pMenu->setPosition(CCPointZero);
	
	this->addChild(pMenu, kPannelLayerIndex);

	CCMenuItemImage *pGobackItem = CCMenuItemImage::create(
		"Thumb_back.png",
		"Thumb_back_pressed.png",
		this,
		menu_selector(StageBaseLayer::gobackCallback));
	
	float iconSize = 40;
	float margin = 0;
	pGobackItem->setPosition(ccp(iconSize + margin, size.height - iconSize - margin));		
	pMenu->addChild(pGobackItem);
}

void StageBaseLayer::update(float dt)
{
	if(m_bIsUpdateStopped)
		return;
	updateTime(dt);

	m_pWorld->Step(dt, 6, 1);
	updateUpdateArray(dt);	
	updateTroopsArray(); // Troops����Ҫÿһ�ָ���m_bodyֵˢ����λ�õ�
	updateSkillButtonState();
	updateAI();
	updateAddStar();
}

// add star������Ҫ���ܻ��� ������Ҫ�ֹ�ָ������λ��
// ÿ�ζ����ѡλ�������ֵ������̫��,�����׵��������ٴ�ѡλ
void StageBaseLayer::updateAddStar()
{
	if(m_fTime - m_fLastAddStarTime < getAddStarInteval())
	{
		return;
	}
	
	m_fLastAddStarTime = m_fTime;
	if(!HIT(0.35))
		return;

	//int count = m_vecPossibleStarLocations.size();
	//if(count == 0)
	//	return;

	//int randomIndex = MiscTool::getRandom(count);
	//if(randomIndex == m_nLastAddStarIndex)
	//{
	//	randomIndex = (randomIndex + 1) % count;
	//}

	//CCPoint loc = m_vecPossibleStarLocations[randomIndex];
	//m_nLastAddStarIndex = randomIndex;
	//makeStar(loc);
	CCPoint goodPostion;
	bool bFinallyFindOne = false;
	// ���Ƴ��Դ�����ָ��������û�ҵ�����ֵ����ֹ�������
	int testTime = 40;
	
	while(!bFinallyFindOne && --testTime > 0)
	{
		// �������� 50 - 650 ֮��
		int x = 50 + MiscTool::getRandom(650 - 50);
		// �������� 40 - 435 ֮��
		int y = 40 + MiscTool::getRandom(435 - 40);
		CCPoint testPoint = ccp(x, y);
		// ��ֵ
		int judge = 150;
		bool bOK = true;
		// 1.����������̫��
		CCObject* pOb = NULL;			
		CCARRAY_FOREACH(m_pPlanetArray, pOb)
		{
			Planet* pPlanet = (Planet*) pOb;
			// ������Լ����Ż���
			if(!pPlanet->isDirty())
			{	
				CCPoint planetPosition = pPlanet->getPosition();
				if(ccpDistance(planetPosition, testPoint) < judge)
				{
					bOK = false;
					break;
				}
			}
		}

		// 2. �����뷵�ذ�ť̫��
		CCRect rectBack(0, 370, 130, 130);
		CCRect rectLevelLabel(71, 430, 160, 50);
		if(rectBack.containsPoint(testPoint) || rectLevelLabel.containsPoint(testPoint))
			bOK = false;

		if(bOK)
		{
			bFinallyFindOne = true;
			goodPostion = testPoint;
			break;
		}
	}

	if(bFinallyFindOne)
		makeStar(goodPostion);
	else
	{
		int a  = 0 ;
		a++;
	}
}

void StageBaseLayer::updateAI()
{
	// AIҪ��һ��ʱ��updateһ�Σ����ÿһ֡��update�������Ĳ���
	if(m_fTime - m_fLastRefreshAITime < getAIRefreshInteval()
		|| m_bIsAIStopped)
	{
		return;
	}
	m_fLastRefreshAITime = m_fTime;

	updateAIAttack();
	updateAIStar();
	updateAISkill();
}

void StageBaseLayer::updateAIAttack()
{
	CCObject* pOb = NULL;			
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;
		if(!pPlanet->isDirty()
			&& pPlanet->getForceSide() != kForceSideCat
			&& pPlanet->getForceSide() != kForceSideMiddle)
		{
			updateAIForPlanet(pPlanet);
		}
	}
}

void StageBaseLayer::updateAIStar()
{
	// ΪDog�ࡢ Third������Ѱ��һ����Star�����ȥ׷��
	int forceSideNeedAI[] = {kForceSideDog, kForceSideThird};
	int count = sizeof(forceSideNeedAI) / sizeof(int);
	
	for(int i = 0; i < count; i++)
	{
		int forceSide = forceSideNeedAI[i];
		CCObject* pOb = NULL;	
		CCARRAY_FOREACH(m_pStarArray, pOb)
		{
			StarObject* pStar = (StarObject*) pOb;
			if(!pStar->isDirty())
			{	
				if(HIT(0.3))
				{
					bool thisForceHaveSentStarTroop = findTroops(pStar, forceSide);
					if(thisForceHaveSentStarTroop)
						continue;
					else
					{
						Planet* pNearest = getNeareastPlanet(pStar->getPosition(), forceSide, false);
						if(pNearest)
							sendTroopsToStar(pNearest, pStar);
					}
				}
			}
		}
	}
}

void StageBaseLayer::updateAISkill()
{
	// ΪDog�ࡢ Third������Ѱ��һ����Star�����ȥ׷��
	int forceSideNeedAI[] = {kForceSideDog, kForceSideThird};
	int count = sizeof(forceSideNeedAI) / sizeof(int);
	for(int i = 0; i < count; i++)
	{
		int forceSide = forceSideNeedAI[i];

		// ΪDog������������ʹ���ж�
		if( (getStarCountForForceSide(kForceSideDog) >= SKILL_SPEED_COUNT) && HIT(0.3))
		{
			Planet* pSpeedUpPlanet = getRandomCanSpeedUpPlanet(kForceSideDog, false);
			if(pSpeedUpPlanet)
			{
				pSpeedUpPlanet->speedUp();
				addStarCountForForceSide(kForceSideDog, -SKILL_SPEED_COUNT);			
				PlayEffect("Audio_button.mp3");
			}
		}

		if( (getStarCountForForceSide(kForceSideDog) >= SKILL_UPGRADE_COUNT) && HIT(0.3))
		{
			Planet* pLevelUpPlanet = getRandomCanLevelUpPlanet(kForceSideDog, false);
			if(pLevelUpPlanet)
			{
				pLevelUpPlanet->levelUp();
				addStarCountForForceSide(kForceSideDog, -SKILL_UPGRADE_COUNT);			
				PlayEffect("Audio_button.mp3");
			}
		}
	}
}

// extraUpdateAIForPlanet�Ƕ�updateAIForPlanet�Ĳ���
// ר�������߼�����
// �������оͲ���ֱ��override updateAIForPlanet��
// ��дextraUpdateAIForPlanet����
void StageBaseLayer::updateAIExtraForPlanet(Planet* pPlanet)
{
	// To be implemented
}

void StageBaseLayer::updateAIForPlanet(Planet* pPlanet)
{
	if(!pPlanet || pPlanet->isDirty() || pPlanet->getForceSide() == kForceSideCat)
	{
		return;
	}

	updateAIExtraForPlanet(pPlanet);

	int thisCount = pPlanet->getFightUnitCount();
	CCObject* pOb = NULL;			
	bool bHaveSent = false;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* targetPlanet = (Planet*) pOb;
		if(!targetPlanet->isDirty())
		{
			
			int toCount = targetPlanet->getFightUnitCount();
			// ����
			if(targetPlanet->getForceSide() == pPlanet->getForceSide())
			{
				if(toCount < 10
					&& thisCount > 20)
				{
					if(HIT(0.7))
					{
						sendTroopsToPlanet(pPlanet, targetPlanet);
						bHaveSent = true;
						break;
					}
				}
			}
			// ����
			else
			{
				// �˴����߼��ص��ǻ���˫�������Ա������е�
				// �������������ձ�ϴ�
				if(thisCount / 2 >= toCount  && thisCount >= 10 )
				{
					if(HIT(0.3))
					{
						sendTroopsToPlanet(pPlanet, targetPlanet);
						bHaveSent = true;
						break;
					}					
				}	
				else if(thisCount - toCount >= 5)
				{
					if(HIT(0.25))
					{
						sendTroopsToPlanet(pPlanet, targetPlanet);
						bHaveSent = true;
						break;
					}
				}
			}
		}
	}

	
	// �˴����߼��ص��ǻ��ڵ�ǰ����ռ���������ı��������е�
	// �������������ձ��С
	if(!bHaveSent)
	{
		/*if(thisCount == pPlanet->getMaximumUnitCount())
		{
		planetActOn(pPlanet);
		}	
		else if(thisCount > pPlanet->getMaximumUnitCount() * 3 / 4  )
		{
		if(HIT(0.7))
		planetActOn(pPlanet);
		}
		else if(thisCount > pPlanet->getMaximumUnitCount() * 2 / 4  )
		{
		if(HIT(0.3))
		planetActOn(pPlanet);
		}
		*/
		if(thisCount > 20 )
		{
			if(HIT(0.9))
				planetActOn(pPlanet);
		}
		else if(thisCount > 10 )
		{
			if(HIT(0.6))
				planetActOn(pPlanet);
		}
	}
}

bool StageBaseLayer::findTroops(GameObject* to, int force)
{
	CCObject* pOb = NULL;
	CCARRAY_FOREACH(m_pTroopsArray, pOb)
	{
		Troops* pIter = (Troops*) pOb;
		if(!pIter->isDirty()
			&& pIter->getForceSide() == force			
			&& pIter->getTargetObject() == to)
		{
			return true;
		}
	}
	return false;
}

void StageBaseLayer::planetActOn(Planet* pPlanet)
{
	Planet* pWeakestEnemyPlanet = getWeakestPlanet(pPlanet->getForceSide(), true);
	Planet* pWeakestFriendPlanet = getWeakestPlanet(pPlanet->getForceSide(), false);
	Planet* pRandomEnemyPlanet = getRandomPlanet(pPlanet->getForceSide(), true);
	Planet* pNearestEnemyPlanet = getNeareastPlanet(pPlanet->getPosition(), pPlanet->getForceSide(), true);

	// ������������򷢶�����
	if(HIT(0.5) && pNearestEnemyPlanet)
	{
		sendTroopsToPlanet(pPlanet, pNearestEnemyPlanet);
	}
	// ���������򷢶�����
	else if(HIT(0.3) && pWeakestEnemyPlanet)
	{
		sendTroopsToPlanet(pPlanet, pWeakestEnemyPlanet);
	}
	//  �����ѡ�Է����򷢶�����
	else if(HIT(0.3) && pRandomEnemyPlanet)
	{
		sendTroopsToPlanet(pPlanet, pRandomEnemyPlanet);
	}
	// ��Ԯ����������δ������
	else if(HIT(0.3) && pWeakestFriendPlanet && pWeakestFriendPlanet != pPlanet
		&& pWeakestFriendPlanet->getFightUnitCount() < pWeakestFriendPlanet->getMaximumUnitCount())
	{
		sendTroopsToPlanet(pPlanet, pWeakestFriendPlanet);
	}
}

// ������һ������
// ��exceptModeΪtrue�����ʾ���Ϊ����nForceSide�����
// ����ΪnForceSide�е�
Planet* StageBaseLayer::getWeakestPlanet(int nForceSide, bool exceptMode)
{
	Planet* pWeakeast = NULL;
	CCObject* pOb = NULL;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		if(!pIter->isDirty())
		{
			bool judgeGoOn = ( pIter->getForceSide() == nForceSide );
			if(exceptMode)
				judgeGoOn = !judgeGoOn;
			if(judgeGoOn)
			{
				if(pWeakeast == NULL)
				{
					pWeakeast = pIter;
				}
				else if(pWeakeast->getFightUnitCount() > pIter->getFightUnitCount())
				{
					pWeakeast = pIter;
				}
			}
		}
	}
	return pWeakeast;
}

// Ѱ����basePosition�����һ��Planet
// ��exceptModeΪtrue�����ʾ���Ϊ����nForceSide���������
// ����ΪnForceSide�������
Planet* StageBaseLayer::getNeareastPlanet(CCPoint basePosition, int nForceSide, bool exceptMode )
{
	Planet* pNearest = NULL;
	CCObject* pOb = NULL;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		if(!pIter->isDirty())
		{
			bool judgeGoOn = ( pIter->getForceSide() == nForceSide );
			if(exceptMode)
				judgeGoOn = !judgeGoOn;

			if(judgeGoOn)
			{
				if(pNearest == NULL)
				{
					pNearest = pIter;
				}
				else 
				{
					float distanceIter = ccpDistance(pIter->getPosition(), basePosition);
					float distanceNeareast =  ccpDistance(pNearest->getPosition(), basePosition);
					if(distanceIter < distanceNeareast)
					{
						pNearest = pIter;
					}
				}
			}
		}
	}

	return pNearest;
}

// �����һ��Planet
// ��exceptModeΪtrue�����ʾ���Ϊ����nForceSide�����
// ����ΪnForceSide�е�
Planet* StageBaseLayer::getRandomPlanet( int nForceSide, bool exceptMode )
{
	Planet* pResult = NULL;
	CCObject* pOb = NULL;
	CCArray* pRandomArray = CCArray::createWithCapacity(40);
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		if(!pIter->isDirty())
		{
			bool judgeGoOn = ( pIter->getForceSide() == nForceSide );
			if(exceptMode)
				judgeGoOn = !judgeGoOn;
			if(judgeGoOn)		
				pRandomArray->addObject(pIter);
		}
	}

	int count = pRandomArray->count();
	if(count == 0)
		return NULL;

	int randomIndex = MiscTool::getRandom(count);
	return (Planet*)pRandomArray->objectAtIndex(randomIndex);
}

Planet* StageBaseLayer::getRandomCanLevelUpPlanet( int nForceSide, bool exceptMode )
{
	Planet* pResult = NULL;
	CCObject* pOb = NULL;
	CCArray* pRandomArray = CCArray::createWithCapacity(40);
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		if(!pIter->isDirty())
		{
			bool judgeGoOn = ( pIter->getForceSide() == nForceSide );
			if(exceptMode)
				judgeGoOn = !judgeGoOn;
			if(judgeGoOn && pIter->canLevelUp())
			{
				pRandomArray->addObject(pIter);
			}
		}
	}

	int count = pRandomArray->count();
	if(count == 0)
		return NULL;

	int randomIndex = MiscTool::getRandom(count);
	return (Planet*)pRandomArray->objectAtIndex(randomIndex);
}

Planet* StageBaseLayer::getRandomCanSpeedUpPlanet( int nForceSide, bool exceptMode )
{
	Planet* pResult = NULL;
	CCObject* pOb = NULL;
	CCArray* pRandomArray = CCArray::createWithCapacity(40);
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		if(!pIter->isDirty())
		{
			bool judgeGoOn = ( pIter->getForceSide() == nForceSide );
			if(exceptMode)
				judgeGoOn = !judgeGoOn;
			if(judgeGoOn && pIter->canLevelUp())
			{
				pRandomArray->addObject(pIter);
			}
		}
	}

	int count = pRandomArray->count();
	if(count == 0)
		return NULL;

	int randomIndex = MiscTool::getRandom(count);
	return (Planet*)pRandomArray->objectAtIndex(randomIndex);
}


void StageBaseLayer::updateTime(float dt)
{
	m_fTime += dt;
}

void StageBaseLayer::updateSkillButtonState()
{
	int catStarCount = getStarCountForForceSide(kForceSideCat) ;
	// ������ť
	if(m_pFocusedPlanet == NULL
		|| catStarCount < SKILL_UPGRADE_COUNT
		|| !m_pFocusedPlanet->canLevelUp())
	{
		m_pSkillUpgradeBtn->setEnabled(false);
	}
	else 
	{
		m_pSkillUpgradeBtn->setEnabled(true);
	}
	
	// ���ٰ�ť
	if(m_pFocusedPlanet == NULL
		|| catStarCount < SKILL_SPEED_COUNT
		|| !m_pFocusedPlanet->canSpeedUp())
	{
		m_pSkillSpeedBtn->setEnabled(false);
	}
	else
	{
		m_pSkillSpeedBtn->setEnabled(true);
	}

	// ���ٰ�ť
	// ���ټ�����ʹ���зǼ��������������ʽ���
	CCObject* pOb = NULL;
	bool bCanSlowDown = false;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		if(!pPlanet->isDirty() 
			&& !pPlanet->getForceSide() == kForceSideCat
			&& pPlanet->canSlowDown())
		{			
			bCanSlowDown = true;
			break;			
		}
	}

	if(  catStarCount < SKILL_DOWN_COUNT
		|| !bCanSlowDown)
	{
		m_pSkillDownBtn->setEnabled(false);
	}
	else
	{
		m_pSkillDownBtn->setEnabled(true);
	}
}


void StageBaseLayer::updateTroopsArray()
{
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(m_pTroopsArray, pObject)
	{
		Troops* pTroops = (Troops*)pObject;
		if(pTroops->m_pBody)
		{
			b2Vec2 b2Pos = pTroops->m_pBody->GetPosition();
			pTroops->setPosition(ccp(b2Pos.x * PTM_RATIO, b2Pos.y * PTM_RATIO));
		}
	}
}

void StageBaseLayer::updateUpdateArray(float dt)
{
	int i = m_pUpdateArray->count();
	if(!m_pUpdateArray || m_pUpdateArray->count() == 0)
		return;
	CCObject* pObject = NULL;
	CCARRAY_FOREACH(m_pUpdateArray, pObject)
	{
		GameObject* go = (GameObject*)pObject;		
		go->myUpdate(dt);
	}
}

void StageBaseLayer::initWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, -0.0f);
	m_pWorld = new b2World(gravity);
	m_pWorld->SetAutoClearForces(true);

	m_pWorld->SetContactListener(this);
}

void StageBaseLayer::initLineLayer()
{	
	setLineLayer(LineLayer::create());
	this->addChild(m_pLineLayer, kPlanetLayerIndex - 1);
}

void StageBaseLayer::initFrontSight()
{
	setFrontSight(CCSprite::create());
	this->addChild(m_pFrontSight, kFrontSightLayerIndex);
	m_pFrontSight->setVisible(false);

	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("FrontSight_1.png");
	animation->addSpriteFrameWithFileName("FrontSight_2.png");
	animation->setDelayPerUnit(0.3f);
	CCAnimate* animate = CCAnimate::create(animation);	
	m_pFrontSight->runAction(CCRepeatForever::create(animate));
}

void StageBaseLayer::initFocusMark()
{
	setFocusMark(CCSprite::create("FocusedMark.png"));
	this->addChild(m_pFocusMark, kFocuseMarkIndex);
	m_pFocusMark->setVisible(false);
}

bool StageBaseLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCObject* pOb = NULL;		
	CCPoint touchPoint = pTouch->getLocation();
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;
		// ������Լ����Ż���
		if(pPlanet->getForceSide() == kForceSideCat)
		{			
			CCPoint planetPosition = pPlanet->getPosition();
			if(pPlanet->boundingBox().containsPoint(touchPoint))
			{
				setFromObject(pPlanet);
				if(m_pLineLayer)
				{				
					m_pLineLayer->setStart(planetPosition);
					m_pLineLayer->setEnd(planetPosition);
					m_pLineLayer->setNeedDraw(true);
				}
			}
		}
	}
	return true;
}

void StageBaseLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	setToObject(NULL);

	CCObject* pOb = NULL;		
	CCPoint touchPoint = pTouch->getLocation();
	bool findOne = false;

	if(!m_pFromObject)
		return;

	// ��������������:
	// 1: touch�����ʼ����
	// 2: �Ѿ���һ����ʼ��
	// ��һ����׼׼��	
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		CCPoint planetPosition = pPlanet->getPosition();
		if( pPlanet->boundingBox().containsPoint(touchPoint)
			&&  !pPlanet->isDirty())
		{	
			if(pPlanet != m_pFromObject && m_pFrontSight)
			{	
				m_pFrontSight->setPosition(ccp(planetPosition.x + 3, planetPosition.y  + 3));
				m_pFrontSight->setVisible(true);				
				
			}
			m_pToObject = pPlanet;
		}
	}

	// �������������ж��Ƿ�Ҫ��׼��
	CCARRAY_FOREACH(m_pStarArray, pOb)
	{
		StarObject* pStar = (StarObject*) pOb;
		CCPoint starPosition = pStar->getPosition();
		float adjust = 10; // ΢����ʹ����õ���
		CCRect originalRect = pStar->boundingBox();
		CCRect adjustedRect = CCRectMake(
			originalRect.origin.x - adjust,
			originalRect.origin.y - adjust,
			originalRect.size.width + adjust * 2,
			originalRect.size.height + adjust * 2);

		if(!pStar->isDirty() && 
			adjustedRect.containsPoint(touchPoint))
		{
			if(m_pFrontSight)
			{
				m_pFrontSight->setPosition(ccp(starPosition.x , starPosition.y ));
				m_pFrontSight->setVisible(true);
			}			
			m_pToObject = pStar;
		}
	}

	// ����������漸�ֲ��Һ���δ�ҵ�to����������׼��
	if(m_pToObject == NULL && m_pFrontSight)
		m_pFrontSight->setVisible(false);

	// ��ѡ����һ��From����Ҫ����׼��
	// ���������
	// 1:��touch��to����Χ�ڣ���end����to���������
	// 2:��touch��to����Χ�ڣ���end����touch��
	if(m_pLineLayer)
	{	
		if(m_pToObject)		
		{
			CCPoint toPosition = m_pToObject->getPosition();
			m_pLineLayer->setEnd(ccp(toPosition.x + 3, toPosition.y  + 3));	
		}
		else
			m_pLineLayer->setEnd(pTouch->getLocation());		
	}
}

Planet* StageBaseLayer::getPlanetByLocation(CCPoint location)
{
	CCObject* pOb = NULL;			
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		CCPoint planetPosition = pPlanet->getPosition();
		if( pPlanet->boundingBox().containsPoint(location)
			&& !pPlanet->isDirty())
		{	
			return pPlanet;
		}
	}
}

void StageBaseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_pFromObject && m_pToObject)
	{
		if(m_pFromObject != m_pToObject)
		{
			handleFromAndTo(m_pFromObject, m_pToObject);
		}
	}

	bool hasInvokeClickOnCatPlanet = false;
	if(m_pFromObject != NULL 
		&& m_pFromObject == getPlanetByLocation(pTouch->getLocation()))
	{
		int startType = GET_TYPE(m_pFromObject);
		if(startType == kGameObjectFight)
		{
			FightObject* pFightObject = (FightObject*) m_pFromObject;
			if(pFightObject->getFightType() == kFightPlanet 
				&& pFightObject->getForceSide() == kForceSideCat)
			{
				m_pFocusedPlanet = (Planet*) pFightObject;
				hasInvokeClickOnCatPlanet = true;
			}
		}
	}

	if(!hasInvokeClickOnCatPlanet)
	{
		m_pFocusedPlanet = NULL;
	}

	showFocusedMarkOnFocusedPlanet();

	// ��β�������󲿷�״̬��0
	if (m_pLineLayer)
	{
		m_pLineLayer->setStart(CCPointZero);
		m_pLineLayer->setEnd(CCPointZero);
		m_pLineLayer->setNeedDraw(false);
	}
	
	if(m_pFrontSight)
		m_pFrontSight->setVisible(false);
	setFromObject(NULL);
	setToObject(NULL);
}

void StageBaseLayer::handleFromAndTo(CCSprite* pFrom, CCSprite* pTo)
{
	int startType = GET_TYPE(pFrom);
	int endType = GET_TYPE(pTo);
	if(startType == kGameObjectFight)
	{
		FightObject* pFightObject = (FightObject*) pFrom;
		int fightType = pFightObject->getFightType();
		int force = pFightObject->getForceSide();
		if(fightType == kFightPlanet && force == kForceSideCat)
		{
			Planet* pCatPlanet = (Planet*) pFightObject;
			if(endType == kGameObjectFight)
			{
				FightObject* pToFightObject = (FightObject*) pTo;
				if(pToFightObject->getFightType() == kFightPlanet)
				{
					Planet* pToPlanet = (Planet*) pToFightObject;
					sendTroopsToPlanet(pCatPlanet, pToPlanet);
				}
			}
			else if(endType == kGameObjectStar)
			{
				StarObject* pStar = (StarObject*) pTo;
				sendTroopsToStar(pCatPlanet, pStar);
			}
		}
	}
}

void StageBaseLayer::showFocusedMarkOnFocusedPlanet()
{
	if(m_pFocusedPlanet == NULL)
	{
		m_pFocusMark->setVisible(false);
		m_pFocusMark->stopAllActions();
	}
	else
	{
		// �ߵ������֧���ˣ�˵��ȷʵ��һ������������ոձ�ѡ����
		m_pFocusMark->setVisible(true);
		m_pFocusMark->setPosition(ccp(
			m_pFocusedPlanet->getPositionX(),
			m_pFocusedPlanet->getPositionY() + 62));

		CCMoveBy* pMoveUp = CCMoveBy::create(0.5, ccp(0, 15));
		CCMoveBy* pMoveDown = CCMoveBy::create(0.5, ccp(0, -15));
		CCSequence* pSeq = CCSequence::createWithTwoActions(pMoveUp, pMoveDown);
		m_pFocusMark->stopAllActions();
		m_pFocusMark->runAction(CCRepeatForever::create(pSeq));

		CCScaleTo* pScaleBig = CCScaleTo::create(0.09, 1.3);
		CCScaleTo* pScaleRestore = CCScaleTo::create(0.09, 1);
		CCSequence* pShake = CCSequence::createWithTwoActions(pScaleBig, pScaleRestore);
		m_pFocusedPlanet->stopAllActions();
		m_pFocusedPlanet->runAction(pShake);

		// ���������ߵĺ���
		planetFocused(m_pFocusedPlanet);
	}	
}

void StageBaseLayer::sendTroopsToPlanet(Planet* fromPlanet, Planet* toPlanet, int count)
{
	if(!fromPlanet || !toPlanet) 
		return;

	if(toPlanet->isDirty())
		return;

	int unitCount = fromPlanet->getFightUnitCount();

	// ÿ���ͳ�һ�룬�����ǰΪ1������
	if(unitCount < 2)
		return;

	// 
	int sendCount = count == -1 ? unitCount / 2 : count;
	int remainCount = unitCount - sendCount;

	// ����from
	fromPlanet->setFightUnitCount(remainCount);

	// �Ф��ޤ���
	Troops* pTroops = makeTroops(fromPlanet->getForceSide(), sendCount, fromPlanet, toPlanet);
	pTroops->gotoTarget();
}

void StageBaseLayer::sendTroopsToStar(Planet* fromPlanet, StarObject* toStar)
{
	if(!fromPlanet || !toStar) 
		return;
	
	if(toStar->isDirty())
		return;

	int unitCount = fromPlanet->getFightUnitCount();

	// �����ǰΪ1�����ͳ�׷�ǲ���
	// ��Ϊ�����ͳ��ᵼ�µ�ǰ���򲿶�����Ϊ0�����ܻ�Ӱ��ռ���¼����ж�
	if(unitCount < 2)
		return;

	// ׷�ǲ���ֻ����1����
	int sendCount = 1;

	// ����from
	fromPlanet->decreaseFightUnitCount(sendCount);

	// ������׷�ǲ���, �Ф��ޤ���
	Troops* pTroops = makeTroops(fromPlanet->getForceSide(), sendCount, fromPlanet, toStar);	
	pTroops->setTroopsType(kTroopsForStar);	
	pTroops->gotoTarget();
}

// ע�⣺Ŀǰ���߼��ٶ�Troops��Ȼ��ĸ�۳���
Troops* StageBaseLayer::makeTroops(int forceSide, int fightUnitCount, Planet* pHomePort, GameObject* pTarget)
{
	Troops* pTroops = Troops::createWithForceSide(forceSide);
	pTroops->setPosition(pHomePort->getPosition());
	pTroops->setFightUnitCount(fightUnitCount);
	pTroops->setHomePort(pHomePort);
	pTroops->setTargetObject(pTarget);
	pTroops->createBox2dObject(m_pWorld);
	this->addChild(pTroops, kTroopsLayerIndex);
	m_pTroopsArray->addObject(pTroops);
	m_pUpdateArray->addObject(pTroops);	

	if(pHomePort->isSpeedUped())
	{
		pTroops->setHighSpeed(true);
	}

	return pTroops;
}

void StageBaseLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);	
}


void StageBaseLayer::gobackCallback(CCObject* pSender)
{
	CCScene* stage = StageSelectScene::create();
	CCDirector::sharedDirector()->replaceScene(stage);	
}


const char* StageBaseLayer::getBKGFileName()
{
	return "StageBase_bkg.png";
}

int StageBaseLayer::getStarCountForForceSide(int forceSide)
{
	int res = 0;
	CCObject* pOb = m_pForceInfoDic->objectForKey(forceSide);
	if(!pOb)
		return res;

	ForceSideInfo* pInfo = (ForceSideInfo*) pOb;
	res =  pInfo->getStarCount();
	return res;
}

void StageBaseLayer::setStarCountForForceSide(int forceSide, int count)
{	
	CCObject* pOb = m_pForceInfoDic->objectForKey(forceSide);
	if(!pOb)
		return ;

	ForceSideInfo* pInfo = (ForceSideInfo*) pOb;
	pInfo->setStarCount(count);	

	if(forceSide == kForceSideCat)
		refreshCatStartCountLabel();
}

void StageBaseLayer::addStarCountForForceSide(int forceSide, int count)
{	
	CCObject* pOb = m_pForceInfoDic->objectForKey(forceSide);
	if(!pOb)
		return ;

	ForceSideInfo* pInfo = (ForceSideInfo*) pOb;
	int nBefore = pInfo->getStarCount();
	pInfo->setStarCount(nBefore + count);	

	if(forceSide == kForceSideCat)
		refreshCatStartCountLabel();
}

void StageBaseLayer::initPannel()
{
	// pannel background
	CCSize winSize = WIN_SIZE;
	CCSprite* pPanel = CCSprite::create("StageBase_panel.png");
	pPanel->setPosition(ccp(winSize.width - pPanel->boundingBox().size.width / 2, winSize.height / 2));
	this->addChild(pPanel, kPannelLayerIndex);

	// pannel buttons
	float commonX = 56;
	CCMenu* pMenu = CCMenu::create(NULL);
	pMenu->setPosition(CCPointZero);	
	pPanel->addChild(pMenu, 1);

	setSkillUpgradeBtn(new CCMenuItemImage());
	CCSprite* pUpNormal = CCSprite::create("StageBase_btn_up_normal.png");
	CCSprite* pUpSeleted = CCSprite::create("StageBase_btn_up_pressed.png");
	CCSprite* pUpDisabled = CCSprite::create("StageBase_btn_up_normal.png");
	pUpDisabled->setOpacity(50);
	m_pSkillUpgradeBtn->initWithNormalSprite(
		pUpNormal,
		pUpSeleted,
		pUpDisabled,
		this,
		menu_selector(StageBaseLayer::skillUpCallback));	
	
	m_pSkillUpgradeBtn->setPosition(ccp(commonX, 438));	
	pMenu->addChild(m_pSkillUpgradeBtn);

	setSkillSpeedBtn(new CCMenuItemImage());
	CCSprite* pSpeedNormal = CCSprite::create("StageBase_btn_speed_normal.png");
	CCSprite* pSpeedSeleted = CCSprite::create("StageBase_btn_speed_pressed.png");
	CCSprite* pSpeedDisabled = CCSprite::create("StageBase_btn_speed_normal.png");
	pSpeedDisabled->setOpacity(50);
	m_pSkillSpeedBtn->initWithNormalSprite(
		pSpeedNormal,
		pSpeedSeleted,
		pSpeedDisabled,
		this,
		menu_selector(StageBaseLayer::skillSpeedCallback));	

	m_pSkillSpeedBtn->setPosition(ccp(commonX, 354));		
	pMenu->addChild(m_pSkillSpeedBtn);

	setSkillDownBtn(new CCMenuItemImage());
	CCSprite* pDownNormal = CCSprite::create("StageBase_btn_down_normal.png");
	CCSprite* pDownSeleted = CCSprite::create("StageBase_btn_down_pressed.png");
	CCSprite* pDownDisabled = CCSprite::create("StageBase_btn_down_normal.png");
	pDownDisabled->setOpacity(50);
	m_pSkillDownBtn->initWithNormalSprite(
		pDownNormal,
		pDownSeleted,
		pDownDisabled,
		this,
		menu_selector(StageBaseLayer::skillDownCallback));	

	m_pSkillDownBtn->setPosition(ccp(commonX, 270));		
	pMenu->addChild(m_pSkillDownBtn);

	// star
	CCSprite* pPanelStar = CCSprite::create("StageBase_panel_star.png");
	pPanelStar->setPosition(ccp(56, 200));
	pPanel->addChild(pPanelStar);

	int catStarCount = getStarCountForForceSide(kForceSideCat);
	CCString* pStrCount = CCString::createWithFormat("%d", catStarCount);
	setStarCountLabel(CCLabelTTF::create(pStrCount->getCString(), "8bitoperator JVE.ttf", 40));
	ccColor3B ccMyYellow={250, 203, 13};
	m_pStarCountLabel->setColor(ccMyYellow);
	m_pStarCountLabel->setPosition(ccp(56 , 160));
	pPanel->addChild(m_pStarCountLabel);

	// Speaker
	setSpeakerBtn(new CCMenuItemImage());

	bool musicEnable = LoadBooleanFromXML(KEY_SWITCH_MUSIC, true);
	bool soundEnable = LoadBooleanFromXML(KEY_SWITCH_SOUNDS, true);
	char* fileName = "Thumb_speaker.png";
	m_bIsSpeakerEnabled = true;
	if(!musicEnable && !soundEnable)	
		m_bIsSpeakerEnabled = false;
	else
		m_bIsSpeakerEnabled = true;

	CCSprite* pSpeakerNormal = NULL;
	CCSprite* pSpeakerSeleted = NULL;
	CCSprite* pSpeakerDisabled = NULL;
	if(m_bIsSpeakerEnabled)
	{
		pSpeakerNormal = CCSprite::create("StageBase_btn_speaker_on_normal.png");
		pSpeakerSeleted = CCSprite::create("StageBase_btn_speaker_on_pressed.png");
		pSpeakerDisabled = CCSprite::create("StageBase_btn_speaker_on_normal.png");	
	}
	else
	{
		pSpeakerNormal = CCSprite::create("StageBase_btn_speaker_off_normal.png");
		pSpeakerSeleted = CCSprite::create("StageBase_btn_speaker_off_pressed.png");
		pSpeakerDisabled = CCSprite::create("StageBase_btn_speaker_off_normal.png");	
	}

	m_pSpeakerBtn->initWithNormalSprite(
		pSpeakerNormal,
		pSpeakerSeleted,
		pSpeakerDisabled,
		this,
		menu_selector(StageBaseLayer::speakerCallback));	

	m_pSpeakerBtn->setPosition(ccp(commonX, 101));		
	pMenu->addChild(m_pSpeakerBtn);

	// Help
	CCMenuItemImage *pHelp = new CCMenuItemImage();
	CCSprite* pHelpNormal = CCSprite::create("StageBase_btn_help_normal.png");
	CCSprite* pHelpSeleted = CCSprite::create("StageBase_btn_help_pressed.png");
	CCSprite* pHelpDisabled = CCSprite::create("StageBase_btn_help_normal.png");	
	pHelp->initWithNormalSprite(
		pHelpNormal,
		pHelpSeleted,
		pHelpDisabled,
		this,
		menu_selector(StageBaseLayer::helpCallback));	

	pHelp->setPosition(ccp(commonX, 34));		
	pMenu->addChild(pHelp);
}

void StageBaseLayer::skillUpCallback( CCObject* pSender )
{
	if(m_pFocusedPlanet)
	{
		addStarCountForForceSide(kForceSideCat, -SKILL_UPGRADE_COUNT);		
		
		m_pFocusedPlanet->levelUp();

		PlayEffect("Audio_button.mp3");
	}
}

void StageBaseLayer::skillSpeedCallback( CCObject* pSender )
{
	if(m_pFocusedPlanet)
	{
		addStarCountForForceSide(kForceSideCat, -SKILL_SPEED_COUNT);
		m_pFocusedPlanet->speedUp();

		PlayEffect("Audio_button.mp3");
	}
}

void StageBaseLayer::skillDownCallback( CCObject* pSender )
{
	addStarCountForForceSide(kForceSideCat, -SKILL_DOWN_COUNT);			

	CCObject* pOb = NULL;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		if(!pPlanet->isDirty() 
			&& pPlanet->getForceSide() != kForceSideCat
			&& pPlanet->getForceSide() != kForceSideMiddle)
		{
			pPlanet->slowDown();
		}
	}
	
	PlayEffect("Audio_button.mp3");
	PlayEffect("Audio_skill_down.mp3");
}

void StageBaseLayer::speakerCallback( CCObject* pSender )
{
	if(m_bIsSpeakerEnabled)
	{
		m_pSpeakerBtn->setNormalImage(CCSprite::create("StageBase_btn_speaker_off_normal.png"));
		m_pSpeakerBtn->setSelectedImage(CCSprite::create("StageBase_btn_speaker_off_pressed.png"));
		m_pSpeakerBtn->setDisabledImage(CCSprite::create("StageBase_btn_speaker_off_normal.png"));	
		m_bIsSpeakerEnabled = false;
		if(m_pParentScene)
			m_pParentScene->opSound(false);
	}
	else 
	{
		m_pSpeakerBtn->setNormalImage(CCSprite::create("StageBase_btn_speaker_on_normal.png"));
		m_pSpeakerBtn->setSelectedImage(CCSprite::create("StageBase_btn_speaker_on_pressed.png"));
		m_pSpeakerBtn->setDisabledImage(CCSprite::create("StageBase_btn_speaker_on_normal.png"));
		m_bIsSpeakerEnabled = true;
		if(m_pParentScene)
			m_pParentScene->opSound(true);
	}

	PlayEffect("Audio_button.mp3");
}

void StageBaseLayer::helpCallback( CCObject* pSender )
{
	if(m_pParentScene)
		m_pParentScene->showHelpLayer();
	m_bIsUpdateStopped = true;

	PlayEffect("Audio_button.mp3");
}

void StageBaseLayer::helpLayerClosed()
{
	m_bIsUpdateStopped = false;
}

void StageBaseLayer::BeginContact( b2Contact* contact )
{
	void* pRawA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* pRawB = contact->GetFixtureB()->GetBody()->GetUserData();
	if(!pRawA || !pRawB)
		return;

	GameObject* goA = (GameObject*) pRawA;
	GameObject* goB = (GameObject*) pRawB;

	if(goA->willBeDestoried() || goB->willBeDestoried())
	{
		return;
	}

	int goTypeA = GET_TYPE(goA);
	int goTypeB = GET_TYPE(goB);
	// �ܹ����ܵļ������
	// 1. troops and troops
	// 2. troops and planet    �����Ƿ�����
	// 3. troops and star   �����Ƿ�����
	// ע��: troop�ַ�Ϊ׷�ǺͲ�׷���������

	if(goTypeA == kGameObjectFight && goTypeB == kGameObjectFight)
	{
		// �˷�֧����ܵ����
		// 1. troops and troops
		// 2. troops and planet  �����Ƿ�����
		FightObject* fightA = (FightObject*) goA;
		FightObject* fightB = (FightObject*) goB;
		
		int fightTypeA = fightA->getFightType();
		int fightTypeB = fightB->getFightType();

		// troops and troops
		if(fightTypeA == kFightTroops && fightTypeB == kFightTroops)
		{
			handleContactTroopsAndTroops((Troops*) fightA, (Troops*) fightB);
		}
		// troops and planet
		else if(fightTypeA == kFightTroops && fightTypeB == kFightPlanet)
		{
			handleContactTroopsAndPlanet((Troops*) fightA, (Planet*) fightB);
		}
		// planet and troops
		else if(fightTypeA == kFightPlanet && fightTypeB == kFightTroops)
		{
			handleContactTroopsAndPlanet((Troops*) fightB, (Planet*) fightA);
		}
	}
	else if(  (goTypeA == kGameObjectFight || goTypeB == kGameObjectFight)
		&& (goTypeA == kGameObjectStar || goTypeB == kGameObjectStar))
	{
		// �˷�֧����ܵ����
		// 1. troops and star  �����Ƿ�����
		FightObject* pFight = NULL;
		StarObject* pStar = NULL;
		if(goTypeA == kGameObjectFight)
		{
			pFight = (FightObject*) goA;
			pStar = (StarObject*) goB;
		}
		else 
		{
			pFight = (FightObject*) goB;
			pStar = (StarObject*) goA;
		}

		int fightType = pFight->getFightType();
		if(fightType == kFightTroops)
		{
			handleContactTroopsAndStar((Troops*) pFight, pStar);
		}
	}
}

void StageBaseLayer::handleContactTroopsAndTroops(Troops* pTroopsA, Troops* pTroopsB)
{
	if(!pTroopsA || !pTroopsB)
		return;

	if(pTroopsA->getForceSide() == pTroopsB->getForceSide())
		return;

	// ��׷�ǲ�����Ϊ0��ײ���
	GameObject *pTarA = pTroopsA->getTargetObject();
	GameObject *pTarB = pTroopsB->getTargetObject();
	if(pTarA && pTarB)
	{
		if(pTarA->getType() == kGameObjectStar || pTarB->getType() == kGameObjectStar)
		{
			return;
		}
	}


	PlayEffect("Audio_fight.mp3");

	int countA = pTroopsA->getFightUnitCount();
	int countB = pTroopsB->getFightUnitCount();

	// ������ʧ��λ
	int lostUnitCount = countA < countB ? countA : countB;
	if(pTroopsA->getForceSide() == kForceSideCat 
		|| pTroopsB->getForceSide() == kForceSideCat)
	{
		m_nUnitLost += lostUnitCount;
	}

	if(countA == countB)
	{
		pTroopsA->destroyInNextUpdate();
		pTroopsB->destroyInNextUpdate();
	}
	else
	{
		Troops* bigTroop = NULL;
		Troops* smallTroop = NULL;

		if(countA > countB)
		{
			bigTroop = pTroopsA;
			smallTroop = pTroopsB;
		}
		else
		{
			bigTroop = pTroopsB;
			smallTroop = pTroopsA;
		}
		bigTroop->setFightUnitCount(bigTroop->getFightUnitCount() - smallTroop->getFightUnitCount());
		smallTroop->destroyInNextUpdate();
	}
}

void StageBaseLayer::handleContactTroopsAndPlanet(Troops* pTroops, Planet* pPlanet)
{
	if(!pTroops || !pPlanet)
		return;

	if(pTroops->getTargetObject() == pPlanet)
	{
		// ����
		if(pTroops->getForceSide() == pPlanet->getForceSide())
		{
			pPlanet->increaseFightUnitCount(pTroops->getFightUnitCount());
		}
		// ����
		else 
		{
			int enemyCount= pPlanet->getFightUnitCount();
			int myCount = pTroops->getFightUnitCount();

			// ��������ʧ��λ
			int myLostUnit = myCount < enemyCount ? myCount : enemyCount;
			m_nUnitLost += myLostUnit;

			// ռ��
			if(myCount >= enemyCount)
			{
				int left = myCount - enemyCount;
				pPlanet->initWithForceSide(pTroops->getForceSide());
				pPlanet->setFightUnitCount(left);		
				playOccupySoundEffect(pTroops->getForceSide());
				planetOccupied(pPlanet);
			}
			// ����
			else
			{
				pPlanet->setFightUnitCount(enemyCount - myCount);
				pPlanet->cry();
				PlayEffect("Audio_fight.mp3");
			}
		}
		pTroops->destroyInNextUpdate();
	}

	if(pTroops->getHomePort() == pPlanet 
		&& pTroops->isInReturn()
		&& pTroops->getTroopsType() == kTroopsForStar)
	{
		// ����
		if(pTroops->getForceSide() == pPlanet->getForceSide()
			&& pTroops->hasGotStar() == true)
		{
			pPlanet->increaseFightUnitCount(pTroops->getFightUnitCount());
			if(pPlanet->getForceSide() == kForceSideCat)
			{
				addStarCountForForceSide(kForceSideCat, 1);	
				refreshCatStartCountLabel();
				starFinallyLandedOnMyPlanet(pPlanet);
			}
			else
			{
				addStarCountForForceSide(pPlanet->getForceSide(), 1);
			}
		}
		// ����
		else 
		{
			int enemyCount= pPlanet->getFightUnitCount();
			int myCount = pTroops->getFightUnitCount();
			if(myCount >= enemyCount)
			{
				int left = myCount = enemyCount;
				pPlanet->initWithForceSide(pTroops->getForceSide());
				pPlanet->setFightUnitCount(left);
			}
			else
			{
				pPlanet->setFightUnitCount(enemyCount - myCount);
			}			
		}
		pTroops->destroyInNextUpdate();

	}
}

void StageBaseLayer::handleContactTroopsAndStar(Troops* pTroops, StarObject* pStar)
{
	if(!pTroops || !pStar)
		return;

	// ע��׷�ǲ��Ӵ��� 1.ȥ  2.��  ����������

	// 1.ȥ
	if(!pTroops->isInReturn() && pTroops->getTargetObject() == pStar)
	{
		// ���������
		// 1.���ǻ����Ƕ�		
		if(!pStar->hasBeenGotBySomeOne())
		{
			pTroops->setHasGotStar(true);			
			pStar->setHasBeenGotBySomeOne(true);
		}
		// 2.�����Ѿ�����Ĳ���������,ֻ��m_pBody��������
		else
		{

		}
		pTroops->goHome();
	}
}

// ռ����Ч
void StageBaseLayer::playOccupySoundEffect(int force)
{
	if(force == kForceSideCat)
	{
		PlayEffect("Audio_cat_mew.mp3");
	}
	else if(force == kForceSideDog)
	{
		PlayEffect("Audio_dog_wang.mp3");
	}
}

// ��Ӯ�ж�ֻ����������ռ���¼���
void StageBaseLayer::planetOccupied(Planet* pPlanet)
{
	bool bNeedGotoWin = true;
	bool bNeedGotoDead = true;
	CCObject* pOb = NULL;			
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pIter = (Planet*) pOb;
		int forceSide = pIter->getForceSide();
		if(forceSide == kForceSideCat)
			bNeedGotoDead = false;
		else if(forceSide == kForceSideDog || forceSide == kForceSideThird)
			bNeedGotoWin = false;
	}

	if(bNeedGotoWin)
		gotoWin();

	if(bNeedGotoDead)
		gotoDead();
}

void StageBaseLayer::starFinallyLandedOnMyPlanet( Planet* pPlanet )
{
	// TODO
}

void StageBaseLayer::planetFocused( Planet* pPlanet )
{
	// TODO
}


void StageBaseLayer::gotoWin()
{	
	if(m_bInDeadOrWinState)
		return;
	m_bInDeadOrWinState = true;
	if(m_pParentScene)
	{		
		m_bIsUpdateStopped = true;
		this->scheduleOnce(schedule_selector(StageBaseLayer::gotoWinInDelay), 0.5f);
		PlayEffect("Audio_win.mp3");	
	}	
}

void StageBaseLayer::gotoWinInDelay(float f)
{
	m_pParentScene->showNavigator(true, (int)m_fTime, m_nUnitLost);	
}


void StageBaseLayer::gotoDead()
{
	if(m_bInDeadOrWinState)
		return;	
	m_bInDeadOrWinState = true;	
	if(m_pParentScene)
	{		
		m_bIsUpdateStopped = true;
		this->scheduleOnce(schedule_selector(StageBaseLayer::gotoDeadInDelay), 0.5f);
		PlayEffect("Audio_lose.mp3");	
	}
}

void StageBaseLayer::gotoDeadInDelay(float f)
{	
	m_pParentScene->showNavigator(false, (int)m_fTime, m_nUnitLost);		
}



void StageBaseLayer::refreshCatStartCountLabel()
{	
	if(m_pStarCountLabel)
	{
		CCString* pStrCount = CCString::createWithFormat("%d", getStarCountForForceSide(kForceSideCat));
		m_pStarCountLabel->setString(pStrCount->getCString());
	}
}