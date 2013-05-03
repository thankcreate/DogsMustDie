#ifndef Stage3_03Layer_h__
#define Stage3_03Layer_h__

#include "Stage3_03Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_03Layer : public StageBaseLayer
{
public:
	Stage3_03Layer();

	CREATE_FUNC(Stage3_03Layer);

	CC_SYNTHESIZE(Planet*, m_pDog1, Dog1);
	CC_SYNTHESIZE(Planet*, m_pDog2, Dog2);
	CC_SYNTHESIZE(Planet*, m_pCat1, Cat1);

	bool init();
	void initPlanets();		
	void attack1(float dt);
	void restoreAIUpdate(float dt);
	void initLoadedAction();
};

#endif // Stage3_03Layer_h__

