#ifndef WinLayer_h__
#define WinLayer_h__

#include "cocos2d.h"
#include "StageBaseScene.h"
#include "NavigatorLayer.h"


using namespace cocos2d;

class WinLayer : public NavigatorLayer
{
public:
	WinLayer();
	~WinLayer();

	CREATE_FUNC(WinLayer);
	bool init();	
	
	CC_SYNTHESIZE(CCSprite* , m_pHappyCat, HappyCat);	

	// m_pFlickerAction 与 本类存在互相引用，故要提前做release
	CC_SYNTHESIZE_RETAIN(CCAction*, m_pFlickerAction, FlickerAction);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pStarArray, StarArray);
	CC_SYNTHESIZE(CCLabelTTF*, m_pTimeLabel, TimeLabel);
	CC_SYNTHESIZE(CCLabelTTF*, m_pLostUnitLabel, LostUnitLabel);

	void show();
	void restore();
	
	CCString* getTitle();
	void backCallback(CCObject* pOb);
	void nextCallback(CCObject* pOb);

	void catFunc1();
	void catFunc2();

	void setScoreStarCount(int count);
	void fillEmptyStar(float dt);
	void setTime(int nTime);
	void setLostUnit(int nLost);
private:
	int m_nScoreStarCount;
	int m_nAlreadyFilledStarCount;
};

#endif // WinLayer_h__