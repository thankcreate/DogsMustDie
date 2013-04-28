#ifndef Stage2_03Layer_h__
#define Stage2_03Layer_h__

#include "Stage2_03Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_03Layer : public StageBaseLayer
{
public:
	Stage2_03Layer();

	CREATE_FUNC(Stage2_03Layer);

	CC_SYNTHESIZE(Planet*, m_pMiddleToDog1, MiddleToDog1);
	CC_SYNTHESIZE(Planet*, m_pMiddleToDog2, MiddleToDog2);

	bool init();
	void initPlanets();	
	

	void extraUpdateAIForPlanet(Planet* pPlanet);

};

#endif // Stage2_03Layer_h__

