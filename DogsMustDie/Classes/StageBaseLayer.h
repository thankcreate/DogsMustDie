#ifndef StageBaseLayer_h__
#define StageBaseLayer_h__

#include "cocos2d.h"
#include "HelpLayerDelegate.h"
#include "Box2D/Box2D.h"

using namespace cocos2d;

class StageBaseScene;
class LineLayer;
class b2World;
class Planet;
class StarObject;
class Troops;
class GameObject;


#define SKILL_UPGRADE_COUNT 2
#define SKILL_SPEED_COUNT 1
#define SKILL_DOWN_COUNT 2


class StageBaseLayer : public CCLayer, public HelpLayerDelegate, public b2ContactListener
{
public:
	StageBaseLayer();
	~StageBaseLayer();
	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pParentScene, ParentScene);

	CC_SYNTHESIZE(CCMenuItemImage*, m_pSkillUpgradeBtn, SkillUpgradeBtn);
	CC_SYNTHESIZE(CCMenuItemImage*, m_pSkillSpeedBtn, SkillSpeedBtn);
	CC_SYNTHESIZE(CCMenuItemImage*, m_pSkillDownBtn, SkillDownBtn);
	CC_SYNTHESIZE(CCMenuItemImage*, m_pSpeakerBtn, SpeakerBtn);
	CC_SYNTHESIZE(LineLayer*, m_pLineLayer, LineLayer);
	CC_SYNTHESIZE(CCSprite*, m_pFrontSight, FrontSight); // target的瞄准框
	CC_SYNTHESIZE(CCSprite*, m_pFocusMark, FocusMark);  // 当前的被选中的星球
	CC_SYNTHESIZE(CCLabelTTF*, m_pStarCountLabel, StarCountLabel);
	CC_SYNTHESIZE(CCSprite*, m_pLevelBorder, LevelBorder);
	CC_SYNTHESIZE(CCLabelTTF*, m_pLevelLabel, LevelLabel);
	void setLevel(int big, int small1);
	CC_SYNTHESIZE(CCSprite*, m_pFromObject, FromObject);
	CC_SYNTHESIZE(CCSprite*, m_pToObject, ToObject);
	CC_SYNTHESIZE(Planet*, m_pFocusedPlanet, FocusedPlanet);

	CC_SYNTHESIZE_RETAIN(CCArray*, m_pPlanetArray, PlanetArray);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pStarArray, StarArray);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pTroopsArray, TroopsArray);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pUpdateArray, UpdateArray);

	CC_SYNTHESIZE_RETAIN(CCDictionary*, m_pForceInfoDic, ForceInfoDic);
	
	std::vector<CCPoint> m_vecPossibleStarLocations;

	b2World* m_pWorld;

	virtual const char* getBKGFileName();
	
	// btn call back
	void gobackCallback(CCObject* pSender);
	virtual void skillUpCallback(CCObject* pSender);
	virtual void skillSpeedCallback(CCObject* pSender);
	virtual void skillDownCallback(CCObject* pSender);
	virtual void speakerCallback(CCObject* pSender);
	virtual void helpCallback(CCObject* pSender);
	

	// HelpLayerDelegate
	void helpLayerClosed();

	// b2ContactListener
	void BeginContact(b2Contact* contact);

	// touch
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void handleFromAndTo(CCSprite *pStart, CCSprite *pEnd);

	// inherit
	void update(float dt);
	void onEnterTransitionDidFinish();

	// init
	void initFrontSight();
	void initLineLayer();	
	void initWorld();	
	void initPannel();
	void initBackground();
	virtual void initPlanets();	
	void initBackButton();


	// update cycle
	virtual void updateTime(float dt);
	virtual void updateUpdateArray(float dt);
	virtual void updateTroopsArray();
	virtual void updateSkillButtonState();
	virtual void updateAI();
	virtual void updateAIStar();
	virtual void updateAIAttack();
	virtual void updateAISkill();
	virtual void updateAIExtraForPlanet(Planet* pPlanet);
	virtual void updateAddStar();

	// make tool
	Troops* makeTroops(int forceSide, int fightUnitCount, Planet* pHomePort, GameObject* pTarget);
	Planet* makePlanet(int force, CCPoint position, int fightUnitCount, int level);
	StarObject* makeStar(CCPoint position);



	// contact handle
	void handleContactTroopsAndStar(Troops* pTroops, StarObject* pStar);
	void handleContactTroopsAndTroops(Troops* troopsA, Troops* troopsB);
	void handleContactTroopsAndPlanet(Troops* pTroops, Planet* pPlanet);
	

	enum
	{
		kPlanetLayerIndex = 5,		
		kFocuseMarkIndex = 6,
		kTroopsLayerIndex = 7,
		kFrontSightLayerIndex = 8,
		kPannelLayerIndex = 10
	};


	void initFocusMark();
	Planet* getPlanetByLocation(CCPoint location);
	void showFocusedMarkOnFocusedPlanet();
	void playOccupySoundEffect(int force);
	void playOccupySoundEffectInDelay(float dt);
	virtual void sendTroopsToPlanet(Planet* fromPlanet, Planet* toPlanet, int count = -1);
	virtual void sendTroopsToStar(Planet* fromPlanet, StarObject* toStar);

	// listener for sub class
	virtual void planetOccupied(Planet* pPlanet);
	virtual void starFinallyLandedOnMyPlanet(Planet* pPlanet);
	virtual void planetFocused(Planet* pPlanet);

	
	virtual float getAIRefreshInteval() {return 4;}
	virtual float getAddStarInteval() {return 3;}	

	void gotoWin();
	void gotoWinInDelay(float f);
	void gotoDead();
	void gotoDeadInDelay(float f);
	void initLevelPannel();
	virtual void updateAIForPlanet(Planet* pPlanet);
	Planet* getWeakestPlanet(int nForceSide, bool exceptMode);
	Planet* getNeareastPlanet(CCPoint basePosition, int nForceSide, bool exceptMode);
	Planet* getRandomPlanet( int nForceSide, bool exceptMode );
	void planetActOn(Planet* pPlanet);
	bool findTroops(GameObject* to, int force);
	Planet* getRandomCanLevelUpPlanet( int nForceSide, bool exceptMode );
	Planet* getRandomCanSpeedUpPlanet( int nForceSide, bool exceptMode );
	void initForceSideInfo();
	int getStarCountForForceSide(int forceSide);
	void setStarCountForForceSide(int forceSide, int count);
	void addStarCountForForceSide(int forceSide, int count);
	
	void refreshCatStartCountLabel();
	
protected:
	bool m_bIsSpeakerEnabled;
	bool m_bIsUpdateStopped;
	bool m_bIsAIStopped;
	bool m_bIsAddStarStopped;
	bool m_bIsHelpLayerInShow;
	bool m_bInDeadOrWinState;
	float m_fTime;
	int m_nUnitLost;
	float m_fLastRefreshAITime;
	float m_fLastAddStarTime;
	float m_nLastAddStarIndex;
};

#endif // StageBaseLayer_h__
