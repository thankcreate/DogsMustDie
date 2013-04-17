#ifndef StageBaseLayer_h__
#define StageBaseLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageBaseScene;

class StageBaseLayer : public CCLayer
{
public:
	StageBaseLayer();
	~StageBaseLayer();
	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pParentScene, ParentScene);	
	CC_SYNTHESIZE(CCMenuItemImage*, m_pSpeakerBtn, SpeakerBtn);

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


};

#endif // StageBaseLayer_h__
