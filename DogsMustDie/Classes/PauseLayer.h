#ifndef PauseLayer_h__
#define PauseLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageBaseScene;
class PauseLayerDelegate;
class PauseLayer : public CCLayer
{
public:
	PauseLayer();
	~PauseLayer();

	CREATE_FUNC(PauseLayer);

	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pStageScene, StageScene);	
	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);	
	CC_SYNTHESIZE(CCLayerColor*, m_pColorLayer, ColorLayer);
	CC_SYNTHESIZE(CCLabelTTF*, m_pTitleLabel, TitleLabel);	
	CC_SYNTHESIZE(PauseLayerDelegate*, m_pDelegate, Delegate);

	bool m_bInShow; // 主要是为了防止用户连续点击gotonext 或者是restart

	void resumeCallback(CCObject* object);
	void restartCallback(CCObject* object);
	void backCallback(CCObject* object);

	virtual void show();
	virtual void restore();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onEnterTransitionDidFinish();
	enum
	{
		SHAKE_DISTANCE = 30
	};
	
};

#endif // PauseLayer_h__