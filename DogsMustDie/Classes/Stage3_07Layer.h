#ifndef Stage3_07Layer_h__
#define Stage3_07Layer_h__

#include "Stage3_07Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage3_07Layer : public StageBaseLayer
{
public:
	Stage3_07Layer();

	CREATE_FUNC(Stage3_07Layer);

	bool init();
	void initPlanets();		

	virtual float getAddStarInteval() {return 1.5;}	

};

#endif // Stage3_07Layer_h__

