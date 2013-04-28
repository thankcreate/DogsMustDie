#ifndef Stage3_04Layer_h__
#define Stage3_04Layer_h__

#include "Stage3_04Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_04Layer : public StageBaseLayer
{
public:
	Stage3_04Layer();

	CREATE_FUNC(Stage3_04Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage3_04Layer_h__

