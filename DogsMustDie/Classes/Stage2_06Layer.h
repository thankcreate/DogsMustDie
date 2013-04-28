#ifndef Stage2_06Layer_h__
#define Stage2_06Layer_h__

#include "Stage2_06Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_06Layer : public StageBaseLayer
{
public:
	Stage2_06Layer();

	CREATE_FUNC(Stage2_06Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage2_06Layer_h__

