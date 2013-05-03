#ifndef Stage2_09Layer_h__
#define Stage2_09Layer_h__

#include "Stage2_09Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage2_09Layer : public StageBaseLayer
{
public:
	Stage2_09Layer();

	CREATE_FUNC(Stage2_09Layer);

	bool init();
	void initPlanets();		
	void initLoadedAction();
};

#endif // Stage2_09Layer_h__

