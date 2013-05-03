#ifndef Stage3_02Layer_h__
#define Stage3_02Layer_h__

#include "Stage3_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_02Layer : public StageBaseLayer
{
public:
	Stage3_02Layer();

	CREATE_FUNC(Stage3_02Layer);

	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pMiddle1, Middle1);	
	CC_SYNTHESIZE(Planet*, m_pMiddle2, Middle2);

	bool init();
	void initPlanets();	
	void initLoadedAction();


};

#endif // Stage3_02Layer_h__

