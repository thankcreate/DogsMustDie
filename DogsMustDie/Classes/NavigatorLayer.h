#ifndef NavigatorLayer_h__
#define NavigatorLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageBaseScene;

class NavigatorLayer : public CCLayer
{
public:
	NavigatorLayer();
	virtual ~NavigatorLayer();
		
	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pStageScene, StageScene);
	CC_SYNTHESIZE(CCLayerColor*, m_pColorLayer, ColorLayer);
	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);	
	CC_SYNTHESIZE(CCLabelTTF*, m_pTitleLabel, TitleLabel);	

	bool m_bInShow; // 主要是为了防止用户连续点击gotonext 或者是restart

	void restartCallback(CCObject* object);
	void gotoNext(CCObject* object);
	void gotoStageSelect(CCObject* object);
	virtual void show();
	virtual void restore();

	virtual CCString* getTitle() = 0;

	virtual void setTime(int nTime) {};
	virtual  void setLostUnit(int nLost) {};
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onEnterTransitionDidFinish();
    void onExit();
	enum
	{
		SHAKE_DISTANCE = 30
	};

	virtual void setScoreStarCount(int count) {};
	virtual void setRound(int round) {};
protected:
	int m_nTime;
	int m_nLostUnit;
};

#endif // NavigatorLayer_h__