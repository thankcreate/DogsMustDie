#ifndef Stage2_04Layer_h__
#define Stage2_04Layer_h__

#include "Stage2_04Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_04Layer : public StageBaseLayer
{
public:
	Stage2_04Layer();

	CREATE_FUNC(Stage2_04Layer);

	CC_SYNTHESIZE(Planet*, m_pCat, Cat);
	CC_SYNTHESIZE(Planet*, m_pDog1, Dog1);	
	CC_SYNTHESIZE(Planet*, m_pDog2, Dog2);

	CC_SYNTHESIZE(Planet*, m_pMiddle1, Middle1);	
	CC_SYNTHESIZE(Planet*, m_pMiddle2, Middle2);
	bool init();
	void initPlanets();	
	void initLoadedAction();


};

#endif // Stage2_04Layer_h__

