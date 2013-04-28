#ifndef Stage2_07Layer_h__
#define Stage2_07Layer_h__

#include "Stage2_07Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_07Layer : public StageBaseLayer
{
public:
	Stage2_07Layer();

	CREATE_FUNC(Stage2_07Layer);

	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pThird, Third);

	CC_SYNTHESIZE(Planet*, m_pMiddleToDog1, MiddleToDog1);
	CC_SYNTHESIZE(Planet*, m_pMiddleToThird1, MiddleToCat1);
	

	bool init();
	void initPlanets();		
	void updateAIExtraForPlanet(Planet* pPlanet);
};

#endif // Stage2_07Layer_h__

