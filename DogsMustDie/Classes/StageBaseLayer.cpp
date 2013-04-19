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


StageBaseLayer::StageBaseLayer()  :
	m_pParentScene(NULL),
	m_bIsSpeakerEnabled(false),
	m_pSpeakerBtn(NULL),
	m_nStarCount(0),
	m_pLineLayer(NULL),
	m_pPlanetArray(NULL),
	m_pFrontSight(NULL),
	m_pFromObject(NULL),
	m_pToObject(NULL),
	m_pStarArray(NULL),
	m_pWorld(NULL),
	m_pUpdateArray(NULL),
	m_bIsUpdateStopped(false),
	m_pTroopsArray(NULL)
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
			

		initWorld();
		initLineLayer();
		initPannel();
		initFrontSight();
		initPlanets();
		// 启动Update
		this->scheduleUpdate();

		// 需要支持拖拽
		this->setTouchEnabled(true);

		bRet = true;
	} while (0);

	return bRet;
}

void StageBaseLayer::initPlanets()
{

}

void StageBaseLayer::makePlanet(int force, CCPoint position, int fightUnitCount, int level)
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

	if(!pPlanet)
		return;
	pPlanet->setPosition(position);
	pPlanet->setFightUnitCount(fightUnitCount);

	m_pPlanetArray->addObject(pPlanet);
	m_pUpdateArray->addObject(pPlanet);
	pPlanet->createBox2dObject(m_pWorld);
	this->addChild(pPlanet, kPlanetLayerIndex);
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
		if( pPlanet != m_pFromObject
			&& pPlanet->boundingBox().containsPoint(touchPoint))
		{		
			if(m_pFrontSight)
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
		if(pStar->boundingBox().containsPoint(touchPoint))
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

void StageBaseLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if(m_pFromObject && m_pToObject)
	{
		handleFromAndTo(m_pFromObject, m_pToObject);
	}

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
					sendCatTroopsToPlanet(pCatPlanet, pToPlanet);
				}
			}
			else if(endType == kGameObjectStar)
			{
				StarObject* pStar = (StarObject*) pTo;
				sendCatTroopsToStar(pCatPlanet, pStar);
			}
		}
	}
}

void StageBaseLayer::sendCatTroopsToPlanet(Planet* fromPlanet, Planet* toPlanet)
{
	int unitCount = fromPlanet->getFightUnitCount();
	
	// 每次送出一半，如果当前为1，则不送
	if(unitCount < 2)
		return;

	// 
	int sendCount = unitCount / 2;
	int remainCount = unitCount - sendCount;

	// 设置from
	fromPlanet->setFightUnitCount(remainCount);

	// 设置出发喵星人军团
	CatTroops* pCatTroops = CatTroops::create();	
	pCatTroops->setPosition(fromPlanet->getPosition());
	pCatTroops->setFightUnitCount(sendCount);
	pCatTroops->setHomePort(fromPlanet);
	pCatTroops->setTargetObject(toPlanet);
	pCatTroops->createBox2dObject(m_pWorld);
	this->addChild(pCatTroops, kTroopsLayerIndex);
	m_pTroopsArray->addObject(pCatTroops);
	m_pUpdateArray->addObject(pCatTroops);
	
	float distance = ccpDistance(toPlanet->getPosition(), fromPlanet->getPosition());
	CCPoint distanceVector = ccpSub(toPlanet->getPosition(), fromPlanet->getPosition());
	
	float absoluteSpeed = pCatTroops->getAbsoluteSpeed();
	float b2SpeedX = absoluteSpeed / distance * distanceVector.x / PTM_RATIO;
	float b2SpeedY = absoluteSpeed / distance * distanceVector.y / PTM_RATIO;
	pCatTroops->m_pBody->SetLinearVelocity(b2Vec2(b2SpeedX, b2SpeedY));
}

void StageBaseLayer::sendCatTroopsToStar(Planet* fromPlanet, StarObject* toStar)
{

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

	CCMenuItemImage *pUp = new CCMenuItemImage();
	CCSprite* pUpNormal = CCSprite::create("StageBase_btn_up_normal.png");
	CCSprite* pUpSeleted = CCSprite::create("StageBase_btn_up_pressed.png");
	CCSprite* pUpDisabled = CCSprite::create("StageBase_btn_up_normal.png");
	pUpDisabled->setOpacity(50);
	pUp->initWithNormalSprite(
		pUpNormal,
		pUpSeleted,
		pUpDisabled,
		this,
		menu_selector(StageBaseLayer::skillUpCallback));	
	
	pUp->setPosition(ccp(commonX, 438));	
	pMenu->addChild(pUp);

	CCMenuItemImage *pSpeed = new CCMenuItemImage();
	CCSprite* pSpeedNormal = CCSprite::create("StageBase_btn_speed_normal.png");
	CCSprite* pSpeedSeleted = CCSprite::create("StageBase_btn_speed_pressed.png");
	CCSprite* pSpeedDisabled = CCSprite::create("StageBase_btn_speed_normal.png");
	pSpeedDisabled->setOpacity(50);
	pSpeed->initWithNormalSprite(
		pSpeedNormal,
		pSpeedSeleted,
		pSpeedDisabled,
		this,
		menu_selector(StageBaseLayer::skillSpeedCallback));	

	pSpeed->setPosition(ccp(commonX, 354));		
	pMenu->addChild(pSpeed);

	CCMenuItemImage *pDown = new CCMenuItemImage();
	CCSprite* pDownNormal = CCSprite::create("StageBase_btn_down_normal.png");
	CCSprite* pDownSeleted = CCSprite::create("StageBase_btn_down_pressed.png");
	CCSprite* pDownDisabled = CCSprite::create("StageBase_btn_down_normal.png");
	pDownDisabled->setOpacity(50);
	pDown->initWithNormalSprite(
		pDownNormal,
		pDownSeleted,
		pDownDisabled,
		this,
		menu_selector(StageBaseLayer::skillDownCallback));	

	pDown->setPosition(ccp(commonX, 270));		
	pMenu->addChild(pDown);

	// star
	CCSprite* pPanelStar = CCSprite::create("StageBase_panel_star.png");
	pPanelStar->setPosition(ccp(56, 200));
	pPanel->addChild(pPanelStar);

	CCString* pStrCount = CCString::createWithFormat("%d", m_nStarCount);
	CCLabelTTF* pLabelStarCount = CCLabelTTF::create(pStrCount->getCString(), "8bitoperator JVE.ttf", 40);
	ccColor3B ccMyYellow={250, 203, 13};
	pLabelStarCount->setColor(ccMyYellow);
	pLabelStarCount->setPosition(ccp(56 , 160));
	pPanel->addChild(pLabelStarCount);

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

}

void StageBaseLayer::skillSpeedCallback( CCObject* pSender )
{

}

void StageBaseLayer::skillDownCallback( CCObject* pSender )
{

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
}

void StageBaseLayer::helpCallback( CCObject* pSender )
{
	if(m_pParentScene)
		m_pParentScene->showHelpLayer();
	m_bIsUpdateStopped = true;
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

	if(goA->isWillBeDestoried() || goB->isWillBeDestoried())
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
}