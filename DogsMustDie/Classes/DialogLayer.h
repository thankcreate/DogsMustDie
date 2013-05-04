#ifndef DialogLayer_h__
#define DialogLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class DialogLayer : public CCLayer
{
public:
	DialogLayer();
	~DialogLayer();

	CREATE_FUNC(DialogLayer);

	bool init();

	CC_SYNTHESIZE(CCLayerColor*, m_pColorLayer, ColorLayer);
	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);
	CC_SYNTHESIZE(CCMenu*, m_pMenu, Menu);
	CC_SYNTHESIZE(CCLabelTTF*, m_pContentLabel, ContentLabel);
	

	void show();
	void restore();
	void okCallback( CCObject* pSender );

	void onEnterTransitionDidFinish();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void setContent(const char* input);
	bool m_bInShow; // 主要是为了防止用户连续点击	
};

#endif // DialogLayer_h__
