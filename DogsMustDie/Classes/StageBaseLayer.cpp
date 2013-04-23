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
#include "CatPlanet.h"
#include "DogPlanet.h"
#include "AudioManager.h"

#define SKILL_UPGRADE_COUNT 2
#define SKILL_SPEED_COUNT 1
#define SKILL_DOWN_COUNT 2


StageBaseLayer::StageBaseLayer()  :
	m_pParentScene(NULL),
	m_bIsSpeakerEnabled(false),
	m_pSpeakerBtn(NULL),
	m_nStarCount(2),
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
	m_pFocusedPlanet(NULL)	
{
	setPlanetArray(CCArray::createWithCapacity(30));
	setStarArray(CCArray::createWithCapacity(10));
	setUpdateArray(CCArray::createWithCapacity(100));
	setTroopsArray(CCArray::createWithCapacity(100));
}

StageBaseLayer::~StageBaseLayer()
{
	CC_SAFE_RELEASE(m_pPlanetArray);	
	CC_SAFE_RELEASE(m_pStarArray);	
	CC_SAFE_RELEASE(m_pUpdateArray);
	CC_SAFE_RELEASE(m_pTroopsArray);
}

bool StageBaseLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		initBackground();
		initBackButton();	
		initLineLayer();
		initPannel();
		initFrontSight();
		initFocusMark();

		initWorld();
		initPlanets();
		// 启动Update
		this->scheduleUpdate();

		// 需要支持拖拽
		this->setTouchEnabled(true);


		PreloadEffect("Audio_fight.mp3");
		PreloadEffect("Audio_button.mp3");
		PreloadEffect("Audio_skill_down.mp3");

		bRet = true;
	} while (0);

	return bRet;
}

void StageBaseLayer::initPlanets()
{

}

Planet* StageBaseLayer::makePlanet(int force, CCPoint position, int fightUnitCount, int level)
{
	Planet* pPlanet = NULL;

	if(force == kForceSideCat)
	{
		pPlanet = CatPlanet::create();
	}
	else if(force == kForceSideDog)
	{
		pPlanet = DogPlanet::create();
	}
		
	pPlanet->setPosition(position);
	pPlanet->setFightUnitCount(fightUnitCount);
	pPlanet->setLevel(level);

	m_pPlanetArray->addObject(pPlanet);
	m_pUpdateArray->addObject(pPlanet);
	pPlanet->createBox2dObject(m_pWorld);
	this->addChild(pPlanet, kPlanetLayerIndex);

	return pPlanet;
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

	m_pWorld->Step(dt, 6, 1);
	updateUpdateArray(dt);

	// Troops是需要每一轮刷新其位置的
	updateTroopsArray();
	updateSkillButtonState();
}

void StageBaseLayer::updateSkillButtonState()
{

	// 升级按钮
	if(m_pFocusedPlanet == NULL
		|| m_nStarCount < SKILL_UPGRADE_COUNT
		|| !m_pFocusedPlanet->canLevelUp())
	{
		m_pSkillUpgradeBtn->setEnabled(false);
	}
	else 
	{
		m_pSkillUpgradeBtn->setEnabled(true);
	}
	
	// 加速按钮
	if(m_pFocusedPlanet == NULL
		|| m_nStarCount < SKILL_SPEED_COUNT
		|| !m_pFocusedPlanet->canSpeedUp())
	{
		m_pSkillSpeedBtn->setEnabled(false);
	}
	else
	{
		m_pSkillSpeedBtn->setEnabled(true);
	}

	// 减速按钮
	// 减速技能是使所有非己方星球升产速率降低
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

	if(  m_nStarCount < SKILL_DOWN_COUNT
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
		// 如果是自己方才画线
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

	// 遍历所有星球，若:
	// 1: touch点非起始星球
	// 2: 已经有一个起始点
	// 则画一个瞄准准星	
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

	// 遍历所有星星判断是否要画准星
	CCARRAY_FOREACH(m_pStarArray, pOb)
	{
		StarObject* pStar = (StarObject*) pOb;
		CCPoint starPosition = pStar->getPosition();
		if(!pStar->isDirty() && 
			pStar->boundingBox().containsPoint(touchPoint))
		{
			if(m_pFrontSight)
			{
				m_pFrontSight->setPosition(ccp(starPosition.x , starPosition.y ));
				m_pFrontSight->setVisible(true);
			}			
			m_pToObject = pStar;
		}
	}

	// 如果经过上面几轮查找后，仍未找到to对象，则隐藏准星
	if(m_pToObject == NULL && m_pFrontSight)
		m_pFrontSight->setVisible(false);

	// 若选中了一个From对象，要画瞄准线
	// 分两种情况
	// 1:若touch在to对象范围内，则end端是to对象的中心
	// 2:若touch在to对象范围内，则end端是touch点
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

	// 收尾工作，大部分状态清0
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
					sendTroopsToPlanet(kForceSideCat, pCatPlanet, pToPlanet);
				}
			}
			else if(endType == kGameObjectStar)
			{
				StarObject* pStar = (StarObject*) pTo;
				sendTroopsToStar(kForceSideCat, pCatPlanet, pStar);
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
		// 走到这个分支里了，说明确实有一个喵星人星球刚刚被选中了
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
	}	
}

void StageBaseLayer::sendTroopsToPlanet(int force, Planet* fromPlanet, Planet* toPlanet)
{
	if(!fromPlanet || !toPlanet) 
		return;

	if(toPlanet->isDirty())
		return;

	int unitCount = fromPlanet->getFightUnitCount();

	// 每次送出一半，如果当前为1，则不送
	if(unitCount < 2)
		return;

	// 
	int sendCount = unitCount / 2;
	int remainCount = unitCount - sendCount;

	// 设置from
	fromPlanet->setFightUnitCount(remainCount);

	// 行きます！
	Troops* pTroops = makeTroops(force, sendCount, fromPlanet, toPlanet);
	pTroops->gotoTarget();
}

void StageBaseLayer::sendTroopsToStar(int force, Planet* fromPlanet, StarObject* toStar)
{
	if(!fromPlanet || !toStar) 
		return;
	
	if(toStar->isDirty())
		return;

	int unitCount = fromPlanet->getFightUnitCount();

	// 如果当前为1，不送出追星部队
	// 因为如若送出会导致当前星球部队数量为0，可能会影响占领事件的判断
	if(unitCount < 2)
		return;

	// 追星部队只出动1个喵
	int sendCount = 1;

	// 设置from
	fromPlanet->decreaseFightUnitCount(sendCount);

	// 喵星人追星部队, 行きます！
	Troops* pTroops = makeTroops(force, sendCount, fromPlanet, toStar);	
	pTroops->setTroopsType(kTroopsForStar);	
	pTroops->gotoTarget();
}

// 注意：目前的逻辑假定Troops必然从母港出发
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

	CCString* pStrCount = CCString::createWithFormat("%d", m_nStarCount);
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
		int remain = m_nStarCount - SKILL_UPGRADE_COUNT;
		setStarCount(remain);
		m_pFocusedPlanet->levelUp();

		PlayEffect("Audio_button.mp3");
	}
}

void StageBaseLayer::skillSpeedCallback( CCObject* pSender )
{
	if(m_pFocusedPlanet)
	{
		int remain = m_nStarCount - SKILL_SPEED_COUNT;
		setStarCount(remain);
		m_pFocusedPlanet->speedUp();

		PlayEffect("Audio_button.mp3");
	}
}

void StageBaseLayer::skillDownCallback( CCObject* pSender )
{
	int remain = m_nStarCount - SKILL_DOWN_COUNT;
	setStarCount(remain);

	CCObject* pOb = NULL;
	CCARRAY_FOREACH(m_pPlanetArray, pOb)
	{
		Planet* pPlanet = (Planet*) pOb;	
		if(!pPlanet->isDirty() && pPlanet->getForceSide() != kForceSideCat)
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
	// 总共可能的几种组合
	// 1. troops and troops
	// 2. troops and planet    或者是反过来
	// 3. troops and star   或者是反过来
	// 注意: troop又分为追星和不追星两种情况

	if(goTypeA == kGameObjectFight && goTypeB == kGameObjectFight)
	{
		// 此分支里可能的组合
		// 1. troops and troops
		// 2. troops and planet  或者是反过来
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
		// 此分支里可能的组合
		// 1. troops and star  或者是反过来
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
}

void StageBaseLayer::handleContactTroopsAndPlanet(Troops* pTroops, Planet* pPlanet)
{
	if(!pTroops || !pPlanet)
		return;

	if(pTroops->getTargetObject() == pPlanet)
	{
		// 友星
		if(pTroops->getForceSide() == pPlanet->getForceSide())
		{
			pPlanet->increaseFightUnitCount(pTroops->getFightUnitCount());
		}
		// 敌星
		else 
		{
			int enemyCount= pPlanet->getFightUnitCount();
			int myCount = pTroops->getFightUnitCount();
			// 占领
			if(myCount >= enemyCount)
			{
				int left = myCount - enemyCount;
				pPlanet->initWithForceSide(pTroops->getForceSide());
				pPlanet->setFightUnitCount(left);		
				playOccupySoundEffect(pTroops->getForceSide());
				planetOccupied(pPlanet);
			}
			// 打酱油
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
		// 友星
		if(pTroops->getForceSide() == pPlanet->getForceSide()
			&& pTroops->hasGotStar() == true)
		{
			pPlanet->increaseFightUnitCount(pTroops->getFightUnitCount());
			setStarCount(++m_nStarCount);
		}
		// 敌星
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

	// 注意追星部队存在 1.去  2.回  这两个过程

	// 1.去
	if(!pTroops->isInReturn() && pTroops->getTargetObject() == pStar)
	{
		// 分两种情况
		// 1.星星还在那儿		
		if(!pStar->hasBeenGotBySomeOne())
		{
			pTroops->setHasGotStar(true);			
			pStar->setHasBeenGotBySomeOne(true);
		}
		// 2.星星已经被别的部队抢走了,只是m_pBody还在那里
		else
		{

		}
		pTroops->goHome();
	}
}

void StageBaseLayer::setStarCount( int count )
{
	m_nStarCount = count;
	if(m_pStarCountLabel)
	{
		CCString* pStrCount = CCString::createWithFormat("%d", m_nStarCount);
		m_pStarCountLabel->setString(pStrCount->getCString());
	}
}


// 占领音效
void StageBaseLayer::playOccupySoundEffect(int force)
{
	if(force == kForceSideCat)
	{
		PlayEffect("Audio_cat_occupy.mp3");
	}
	else if(force == kForceSideDog)
	{
		PlayEffect("Audio_dog_occupy.mp3");
	}
}

void StageBaseLayer::planetOccupied(Planet* pPlanet)
{
	// TODO
}