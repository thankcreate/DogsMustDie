#ifndef Stage1_01Layer_h__
#define Stage1_01Layer_h__

#include "Stage1_01Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_01Layer : public StageBaseLayer
{
public:
	Stage1_01Layer();
	~Stage1_01Layer();
	CREATE_FUNC(Stage1_01Layer);

	CC_SYNTHESIZE(CCSprite*, m_pGuideBorder, GuideBorder);
	CC_SYNTHESIZE(CCLabelTTF*, m_pGuideLabel, GuideLabel);
	CC_SYNTHESIZE(CCSprite*, m_pFinger, Finger);
	CC_SYNTHESIZE(CCSprite*, m_pSkillPrompt, SkillPrompt);
	CC_SYNTHESIZE(CCSprite*, m_pStar, Star);


	CC_SYNTHESIZE(Planet*, m_pDogPlanet1, DogPlanet1);
	CC_SYNTHESIZE(Planet*, m_pDogPlanet2, DogPlanet2);

	bool init();
	void initPlanets();
	void initGuideLayer();
	void guideDragToOccupy(float dt);

	virtual void sendTroopsToPlanet( Planet* fromPlanet, Planet* toPlanet,  int count = -1);
	virtual void sendTroopsToStar( Planet* fromPlanet, StarObject* toStar);
	void planetOccupied(Planet* pPlanet);
	void guideDragToStar(float dt);
	void starFinallyLandedOnMyPlanet( Planet* pPlanet );
	void guideFocusOnPlanet(float dt);
	void guideClickOnUpgrade();
	void planetFocused( Planet* pPlanet );

	void skillUpCallback(CCObject* pSender);
	void skillSpeedCallback(CCObject* pSender);
	void skillDownCallback(CCObject* pSender);
	void guideClickOnSpeedUp();
	void guideClickOnDown(float dt);
	void updateSkillButtonState();
	void guideFinalStrike(float dt);
	void callFunc1();
	void guideWin();
	void skipCallback(CCObject* pObject);
	void showWinInDelay(float dt);

	int getInitStarCount() { return 4; }
	virtual void updateAI();
private:
	bool m_bAskedToFocusAPlanet;
	bool m_bAskedToClickSkillUpgrade;
	bool m_bAskedToClickSkillSpeedUp;
	bool m_bAskedToClickSkillDown;
	bool m_bAskedToFinalStrike;

};

#endif // Stage1_01Layer_h__

