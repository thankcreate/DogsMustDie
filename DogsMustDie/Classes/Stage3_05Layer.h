#ifndef Stage3_05Layer_h__
#define Stage3_05Layer_h__

#include "Stage3_05Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_05Layer : public StageBaseLayer
{
public:
	Stage3_05Layer();

	CREATE_FUNC(Stage3_05Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage3_05Layer_h__

