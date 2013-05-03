#ifndef StageEndlessLayer_h__
#define StageEndlessLayer_h__

#include "StageEndlessLayer.h"
#include "StageBaseLayer.h"
#include "NoticeLayerDelegate.h"

using namespace cocos2d;

class Planet;


// 第一关有很多教程部分
class StageEndlessLayer : public StageBaseLayer, public NoticeLayerDelegate
{
public:
	StageEndlessLayer();
	~StageEndlessLayer();

	CREATE_FUNC(StageEndlessLayer);

	// NoticeLayerDelegate
	void noticeLayerFinished();

	CC_SYNTHESIZE_RETAIN(CCArray*, m_pCatPlanetArray, CatPlanetArray);
	CC_SYNTHESIZE_RETAIN(CCArray*, m_pDogPlanetArray, DogPlanetArray);

	bool init();	
	void setLevel(int big, int small1);
	
	void initWithRound(int round);
	void initPlanetsWithRound(int round);
	CCPoint getRandomPlanetPosition();	

	virtual float getAddStarInteval() {return 2;}
	virtual void gotoWinInDelay(float f);
	virtual void gotoDeadInDelay(float f);

	virtual void setRound(int round);
	void initCatPlanetsWithRound(int round);
	void initDogPlanetsWithRound(int round);
	void initStarsWithRound(int round);
	void initStartCountWithRound(int round);
	void initMiddlePlanetsWithRound(int round);	
	void initLoadedAction();
protected:
	int m_nRound;
};

#endif // StageEndlessLayer_h__

