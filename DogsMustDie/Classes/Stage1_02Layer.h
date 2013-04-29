#ifndef Stage1_02Layer_h__
#define Stage1_02Layer_h__

#include "Stage1_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_02Layer : public StageBaseLayer
{
public:
	Stage1_02Layer();
	
	CREATE_FUNC(Stage1_02Layer);
	
	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pCatRight, CatRight);

	bool init();
	void initPlanets();	
	void attack(float dt);


};

#endif // Stage1_02Layer_h__

