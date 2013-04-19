#ifndef Stage1Layer_h__
#define Stage1Layer_h__

#include "cocos2d.h"
#include "IAPCallback.h"

using namespace cocos2d;

class StageSelectLayer : public CCLayer, public iOSBridge::Callbacks::IAPCallback
{
public:
	StageSelectLayer();
	~StageSelectLayer();

	CREATE_FUNC(StageSelectLayer);
	bool init();
	void keyBackClicked();

	void onExit();
	void onEnterTransitionDidFinish();


	CC_SYNTHESIZE(CCLayer*, m_pScrollLayer, ScrollLayer);
	CC_SYNTHESIZE(CCMenuItemImage*, m_pLeftThumb, LeftThumb);
	CC_SYNTHESIZE(CCMenuItemImage*, m_pRightThumb, RightThumb);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pBuyBtnArray, BuyBtnArray);

	void buyCallback(CCObject* pSender);
	void restoreCallback(CCObject* pSender);
	void gotoStageCallback(CCObject* pSender);
	void slideCallback(CCObject* pSender);
	void menuBackCallback(CCObject* pSender);


	void reloadScrollLayer();

	// IAPCallback
	virtual void productsDownloaded(const std::vector<std::string>& products);
	virtual void purchased(bool isSuccessful);


	enum
	{
		SLIDER_LEFT,
		SLIDER_RIGHT
	};
};

#endif // Stage1Layer_h__