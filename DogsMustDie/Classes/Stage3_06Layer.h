#ifndef Stage3_06Layer_h__
#define Stage3_06Layer_h__

#include "Stage3_06Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_06Layer : public StageBaseLayer
{
public:
	Stage3_06Layer();

	CREATE_FUNC(Stage3_06Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage3_06Layer_h__

