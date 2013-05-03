#ifndef BuyLayer_h__
#define BuyLayer_h__
#include "cocos2d.h"

using namespace cocos2d;
class BuyLayer : public CCLayer
{
public:
	BuyLayer(void);
	virtual ~BuyLayer(void);

	CREATE_FUNC(BuyLayer);

	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);
	CC_SYNTHESIZE(CCLabelTTF*, m_pCoinCountLabel, CoinCountLabel);
	bool init();	
	void keyBackClicked(); 
	
	void gobackCallback(CCObject* pSender);
	void initButtons();

	void buyCallback(CCObject* pSender);
	void refreshCoinCountLabel();
	enum
	{
		TAG_10 = 1,
		TAG_20,
		TAG_50
	};
};


#endif // BuyLayer_h__