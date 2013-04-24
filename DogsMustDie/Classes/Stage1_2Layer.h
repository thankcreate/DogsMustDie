#ifndef Stage1_2Layer_h__
#define Stage1_2Layer_h__

#include "Stage1_2Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_2Layer : public StageBaseLayer
{
public:
	Stage1_2Layer();
	
	CREATE_FUNC(Stage1_2Layer);

	bool init();
	void initPlanets();	
};

#endif // Stage1_2Layer_h__

