#ifndef Stage2_05Layer_h__
#define Stage2_05Layer_h__

#include "Stage2_05Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_05Layer : public StageBaseLayer
{
public:
	Stage2_05Layer();

	CREATE_FUNC(Stage2_05Layer);

	CC_SYNTHESIZE(Planet*, m_pMiddleToDog1, MiddleToDog1);
	CC_SYNTHESIZE(Planet*, m_pMiddleToDog2, MiddleToDog2);


	CC_SYNTHESIZE(Planet*, m_pMiddleToCat1, MiddleToCat1);
	CC_SYNTHESIZE(Planet*, m_pMiddleToCat2, MiddleToCat2);

	CC_SYNTHESIZE(Planet*, m_pThird, Third);
	CC_SYNTHESIZE(Planet*, m_pDog, Dog);

	bool init();
	void initPlanets();		
	void extraUpdateAIForPlanet( Planet* pPlanet );
	void initLoadedAction();
};

#endif // Stage2_05Layer_h__

