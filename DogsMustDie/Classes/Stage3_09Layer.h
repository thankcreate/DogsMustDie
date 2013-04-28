#ifndef Stage3_09Layer_h__
#define Stage3_09Layer_h__

#include "Stage3_09Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_09Layer : public StageBaseLayer
{
public:
	Stage3_09Layer();

	CREATE_FUNC(Stage3_09Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage3_09Layer_h__

