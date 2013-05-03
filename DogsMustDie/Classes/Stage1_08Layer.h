#ifndef Stage1_08Layer_h__
#define Stage1_08Layer_h__

#include "Stage1_08Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_08Layer : public StageBaseLayer
{
public:
	Stage1_08Layer();

	CREATE_FUNC(Stage1_08Layer);

	CC_SYNTHESIZE(Planet*, m_pCat, Cat);
	CC_SYNTHESIZE(Planet*, m_pDog1, Dog1);
	CC_SYNTHESIZE(Planet*, m_pDog2, Dog2);
	CC_SYNTHESIZE(Planet*, m_pDog3, Dog3);
	CC_SYNTHESIZE(Planet*, m_pDog4, Dog4);

	bool init();
	void initPlanets();	
	void initLoadedAction();


};

#endif // Stage1_08Layer_h__

