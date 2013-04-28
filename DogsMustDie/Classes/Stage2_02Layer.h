#ifndef Stage2_02Layer_h__
#define Stage2_02Layer_h__

#include "Stage2_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_02Layer : public StageBaseLayer
{
public:
	Stage2_02Layer();

	CREATE_FUNC(Stage2_02Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage2_02Layer_h__

