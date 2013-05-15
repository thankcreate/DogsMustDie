#ifndef StageEndlessRestartLayer_h__
#define StageEndlessRestartLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "StageEndlessNavigatorLayer.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AppOfferDelegate.h"
#endif

using namespace cocos2d;

class StageEndlessRestartLayer : public StageEndlessNavigatorLayer
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    , public AppOfferDelegate
#endif
{
public:
	StageEndlessRestartLayer();
	~StageEndlessRestartLayer();

	CREATE_FUNC(StageEndlessRestartLayer);
	bool init();

    void onEnterTransitionDidFinish();


	CC_SYNTHESIZE(CCSprite* , m_pHappyDog, HappyDog);		
	CC_SYNTHESIZE_RETAIN(CCAction*, m_pFlickerAction, FlickerAction);
	CC_SYNTHESIZE(CCLabelTTF*, m_pCoinCountLabel, CoinCountLabel);

	CC_SYNTHESIZE(CCMenuItemImage *, m_pContinueItem, ContinueItem);

	CCString* getTitle();
	void backCallback(CCObject* pOb);
	void restartCallback(CCObject* pOb);
	void getCoinCallback(CCObject* pOb);
	

	void restore();			
	void show();

	void dogFunc1();
	void dogFunc2();
	void setRound( int round );
	void refreshCoinCountLabel();
	void continueCallback(CCObject* pOb);
	void refreshContinueButtonEnableState();

	// AppOfferDelegate
	virtual void pointAdded(int n);
	void pointAddedInternal(float dt);
protected:
	int m_nCoinCount;
	bool m_bContinueAlreadyUsedInOneSession;
};

#endif // StageEndlessRestartLayer_h__