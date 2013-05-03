#ifndef Stage1_06Layer_h__
#define Stage1_06Layer_h__

#include "Stage1_06Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_06Layer : public StageBaseLayer
{
public:
	Stage1_06Layer();

	CREATE_FUNC(Stage1_06Layer);


	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pMiddle1, Middle1);
	CC_SYNTHESIZE(Planet*, m_pMiddle2, Middle2);
	CC_SYNTHESIZE(Planet*, m_pMiddle3, Middle3);

	bool init();
	void initPlanets();	
	void initLoadedAction();


};

#endif // Stage1_06Layer_h__

