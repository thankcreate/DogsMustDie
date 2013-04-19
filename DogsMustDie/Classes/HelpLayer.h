#ifndef HelpLayer_h__
#define HelpLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class HelpLayerDelegate;

class HelpLayer : public CCLayer
{
public:
	HelpLayer();
	~HelpLayer();

	CREATE_FUNC(HelpLayer);

	bool init();
		
	CC_SYNTHESIZE(CCLayerColor*, m_pColorLayer, ColorLayer);
	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);
	CC_SYNTHESIZE(CCMenu*, m_pMenu, Menu);
	CC_SYNTHESIZE(HelpLayerDelegate*, m_pDelegate, Delegate);

	void show();
	void restore();
	void backCallback( CCObject* pSender );
	
	void onEnterTransitionDidFinish();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	bool m_bInShow; // 主要是为了防止用户连续点击

	enum
	{
		SHAKE_DISTANCE = 30
	};
};

#endif // HelpLayer_h__
