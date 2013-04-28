#ifndef Stage1_07Layer_h__
#define Stage1_07Layer_h__

#include "Stage1_07Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_07Layer : public StageBaseLayer
{
public:
	Stage1_07Layer();

	CREATE_FUNC(Stage1_07Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_07Layer_h__

