#ifndef Stage3_08Layer_h__
#define Stage3_08Layer_h__

#include "Stage3_08Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_08Layer : public StageBaseLayer
{
public:
	Stage3_08Layer();

	CREATE_FUNC(Stage3_08Layer);

	bool init();
	void initPlanets();		
	virtual float getAddStarInteval() {return 1.5;}	
};

#endif // Stage3_08Layer_h__

