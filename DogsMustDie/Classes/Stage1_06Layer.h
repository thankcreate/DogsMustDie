#ifndef Stage1_06Layer_h__
#define Stage1_06Layer_h__

#include "Stage1_06Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_06Layer : public StageBaseLayer
{
public:
	Stage1_06Layer();

	CREATE_FUNC(Stage1_06Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_06Layer_h__

