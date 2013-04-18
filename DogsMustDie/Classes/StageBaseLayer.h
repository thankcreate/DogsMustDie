#ifndef StageBaseLayer_h__
#define StageBaseLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageBaseScene;
class LineLayer;

class StageBaseLayer : public CCLayer
{
public:
	StageBaseLayer();
	~StageBaseLayer();
	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pParentScene, ParentScene);	
	CC_SYNTHESIZE(CCMenuItemImage*, m_pSpeakerBtn, SpeakerBtn);
	CC_SYNTHESIZE(LineLayer*, m_pLineLayer, LineLayer);
	CC_SYNTHESIZE(CCSprite*, m_pFrontSight, FrontSight);

	CC_SYNTHESIZE(CCSprite*, m_pFromObject, FromObject);
	CC_SYNTHESIZE(CCSprite*, m_pToObject, ToObject);

	CC_SYNTHESIZE_RETAIN(CCArray*, m_pPlanetArray, PlanetArray);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pStarArray, StarArray);

	bool m_bIsSpeakerEnabled;
	int m_nStarCount;
	bool m_bIsHelpLayerInShow;

	virtual const char* getBKGFileName();
	void gobackCallback(CCObject* pSender);
	void initPannel();

	virtual void skillUpCallback(CCObject* pSender);
	virtual void skillSpeedCallback(CCObject* pSender);
	virtual void skillDownCallback(CCObject* pSender);
	virtual void speakerCallback(CCObject* pSender);
	virtual void helpCallback(CCObject* pSender);
	
	void onEnterTransitionDidFinish();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void initFrontSight();
	void initLineLayer();


	enum
	{
		kPlanetLayerIndex = 5,
		kFrontSightLayerIndex = 6,
		kPannelLayerIndex = 10
	};
};

#endif // StageBaseLayer_h__
