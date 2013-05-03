#ifndef Stage2_02Layer_h__
#define Stage2_02Layer_h__

#include "Stage2_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_02Layer : public StageBaseLayer
{
public:
	Stage2_02Layer();

	CREATE_FUNC(Stage2_02Layer);

	CC_SYNTHESIZE(Planet*, m_pCat, Cat);
	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pMiddleNearToDog, MiddleNearToDog);
	CC_SYNTHESIZE(Planet*, m_pMiddleNearToCat, MiddleNearToCat);
	CC_SYNTHESIZE(Planet*, m_pThird, Third);

	bool init();
	void initPlanets();		
	void initLoadedAction();
};

#endif // Stage2_02Layer_h__

