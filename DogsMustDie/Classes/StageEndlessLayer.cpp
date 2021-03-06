#include "StageEndlessLayer.h"
#include "Defines.h"
#include "Planet.h"
#include "MiscTool.h"
#include "StartupScene.h"
#include "AudioManager.h"
#include "StageEndlessScene.h"
#include "MyUseDefaultDef.h"

StageEndlessLayer::StageEndlessLayer() :
	m_nRound(0),
	m_pCatPlanetArray(NULL),
	m_pDogPlanetArray(NULL)
{
	setDogPlanetArray(CCArray::createWithCapacity(10));
	setCatPlanetArray(CCArray::createWithCapacity(10));	
}

	StageEndlessLayer::~StageEndlessLayer()
	{
		CC_SAFE_RELEASE(m_pDogPlanetArray);
		CC_SAFE_RELEASE(m_pCatPlanetArray);
	}

bool StageEndlessLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StageBaseLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}

void StageEndlessLayer::initLoadedAction()
{		
	// check if need show NoticeLayer
	bool bFirstHere = LoadBooleanFromXML(KEY_FIRST_ENDLESS , true);
	if(bFirstHere)
	{
		SaveBooleanToXML(KEY_FIRST_ENDLESS, false);
		SaveUserDefault();
		StageEndlessScene* scene = (StageEndlessScene*)getParentScene();
		scene->showNoticeLayer();
	}


	// check if need show daily award
	time_t rawtime;
	struct tm * tmInfo;
	time (&rawtime);

	tmInfo = localtime(&rawtime);
	int year = tmInfo->tm_year + 1900;
	int month = tmInfo->tm_mon + 1;
	int day = tmInfo->tm_mday;

	int lastYear = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_YEAR , -1);
	int lastMonth = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_MONTH , -1);
	int lastDay = LoadIntegerFromXML(KEY_LAST_ENDLESS_DATE_DAY , -1);

	if(	lastYear != year
		|| lastMonth != month
		|| lastDay != day )
	{
		// 走到这里说明是今日第一次登陆到无尽模式
		int coin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
		++coin;
		SaveIntegerToXML(KEY_COIN_COUNT, coin);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_YEAR, year);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_MONTH, month);
		SaveIntegerToXML(KEY_LAST_ENDLESS_DATE_DAY, day);
		SaveUserDefault();
		StageEndlessScene* scene = (StageEndlessScene*)getParentScene();
		scene->showTopBannerLayerWithCustomizedContent(3);		
	}	
}


void StageEndlessLayer::initWithRound(int round)
{
	setRound(round);
	initPlanetsWithRound(round);
}


// round从0算起
void StageEndlessLayer::initPlanetsWithRound(int round)
{
	initCatPlanetsWithRound(round);
	initDogPlanetsWithRound(round);
	initMiddlePlanetsWithRound(round);
	initStarsWithRound(round);
	initStartCountWithRound(round);	
}

void StageEndlessLayer::initMiddlePlanetsWithRound(int round)
{
	if(round >= 4)
	{				
		CCPoint posi = getRandomPlanetPosition();
		if(posi.x > 0 && posi.y > 0)
			makePlanet(kForceSideMiddle, posi , 6, 0)->stopIncrease();		
	}
}



void StageEndlessLayer::initStartCountWithRound(int round)
{
	if(round >= 5)
	{		
		setStarCountForForceSide(kForceSideCat, 2);
	}
	else if(round >= 3)
	{		
		setStarCountForForceSide(kForceSideCat, 1);
	}
}

// round从0算起
void StageEndlessLayer::initCatPlanetsWithRound(int round)
{
	int countForSide = 0;
	if(round < 2)
		countForSide = 2;
	else
		countForSide = 3;

	for(int i = 0; i <countForSide; i++)
	{	
		int fightUnit = 10;
		CCPoint posi = getRandomPlanetPosition();
		if(posi.x > 0 && posi.y > 0)
		{			
			Planet* cat = makePlanet(kForceSideCat, posi, fightUnit, 0);
			m_pCatPlanetArray->addObject(cat);
		}
	}
		
    // 以9为一个循环数
	int levelSum = (round % 9)* 1.5;
	levelSum -=2;
	if(levelSum < 0)
		levelSum = 0;
	if(levelSum > 5)
		levelSum = 5;
		
	while(levelSum > 0)
	{
		CCObject* pOb = NULL;			
		CCARRAY_FOREACH(m_pCatPlanetArray, pOb)
		{
			Planet* pPlanet = (Planet*) pOb;		
			if(!pPlanet->isDirty())
			{	
				if(levelSum >0)
				{
					pPlanet->levelUp();
					--levelSum;
				}
			}
		}
	}

	if(round >= 5)
	{
		Planet* pCat = (Planet*) m_pCatPlanetArray->objectAtIndex(0);
		pCat->speedUp();
	}

}

// round从0算起
void StageEndlessLayer::initDogPlanetsWithRound(int round)
{
	int countForSide = 0;
	if(round < 2)
		countForSide = 2;
	else
		countForSide = 3;

	for(int i = 0; i <countForSide; i++)
	{		
		CCPoint posi = getRandomPlanetPosition();
		if(posi.x > 0 && posi.y > 0)
		{			
			Planet* dog = makePlanet(kForceSideDog, posi, 10, 0);
			m_pDogPlanetArray->addObject(dog);
		}
	}

	
	int levelSum = (round % 9)* 1.5;
	if(levelSum > 8)
		levelSum = 8;

	while(levelSum > 0)
	{
		CCObject* pOb = NULL;			
		CCARRAY_FOREACH(m_pDogPlanetArray, pOb)
		{
			Planet* pPlanet = (Planet*) pOb;		
			if(!pPlanet->isDirty())
			{	
				if(levelSum >0)
				{
					pPlanet->levelUp();
					--levelSum;
				}
			}
		}
	}

	int fightUnitAddedSum = (round % 9)* 1;
	if(fightUnitAddedSum > 8)
		fightUnitAddedSum = 8;

	while(fightUnitAddedSum > 0)
	{
		CCObject* pOb = NULL;			
		CCARRAY_FOREACH(m_pDogPlanetArray, pOb)
		{
			Planet* pPlanet = (Planet*) pOb;		
			if(!pPlanet->isDirty())
			{	
				if(fightUnitAddedSum >0)
				{
					pPlanet->increaseFightUnitCount(1);
					--fightUnitAddedSum;;
				}
			}
		}
	}
}

// round从0算起
void StageEndlessLayer::initStarsWithRound(int round)
{
	int startInitCount = round / 2;
	if(startInitCount > 4)
		startInitCount = 4;
	for(int i = 0 ; i < startInitCount; i++)
	{
		updateAddStarInternal();
	}
}

CCPoint StageEndlessLayer::getRandomPlanetPosition()
{
	CCPoint defaultResult = ccp(-1,-1);
	int testMax =  400;
	while(-- testMax > 0)
	{
		int xRandom = MiscTool::getRandom(533) + 76;
		int yRandom = MiscTool::getRandom(345) + 56;

		// 左上角不能选
		if(xRandom < 117 && yRandom > 356)
			continue;

		CCPoint testPoint = ccp(xRandom, yRandom);
		
		bool bToClose = false;
		float judge = 160;
		CCObject* pOb = NULL;			
		CCARRAY_FOREACH(getPlanetArray(), pOb)
		{
			Planet* pPlanet = (Planet*) pOb;
			// 如果是自己方才画线
			if(!pPlanet->isDirty())
			{	
				CCPoint planetPosition = pPlanet->getPosition();
				if(ccpDistance(planetPosition, testPoint) < judge)
				{
					bToClose = true;
					break;
				}
			}
		}

		if(bToClose)
			continue;

		return ccp(xRandom, yRandom);
	}

	return defaultResult;
}


void StageEndlessLayer::setLevel(int big, int small1)
{
	// 把这个置空
}

void StageEndlessLayer::setRound( int round )
{
	m_nRound = round;
	CCString* pStrLevel = CCString::createWithFormat("Round %d", round);	
	m_pLevelLabel->setString(pStrLevel->getCString());
}


void StageEndlessLayer::gotoWinInDelay(float f)
{
	m_pParentScene->showNavigator(true, 0, 0);	
}

void StageEndlessLayer::gotoDeadInDelay(float f)
{	
	m_pParentScene->showNavigator(false, 0, 0);		
}

void StageEndlessLayer::noticeLayerFinished()
{
	m_bIsUpdateStopped = false;
}
