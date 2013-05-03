#ifndef Stage1_04Layer_h__
#define Stage1_04Layer_h__

#include "Stage1_04Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_04Layer : public StageBaseLayer
{
public:
	Stage1_04Layer();

	CREATE_FUNC(Stage1_04Layer);

	bool init();
	void initPlanets();	

	CC_SYNTHESIZE(Planet*, m_pDog, Dog);
	CC_SYNTHESIZE(Planet*, m_pMiddle1, Middle1);
	CC_SYNTHESIZE(Planet*, m_pMiddle2, Middle2);
	void initLoadedAction();


};

#endif // Stage1_04Layer_h__

