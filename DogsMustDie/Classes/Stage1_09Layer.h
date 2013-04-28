#ifndef Stage1_09Layer_h__
#define Stage1_09Layer_h__

#include "Stage1_09Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// 第一关有很多教程部分
class Stage1_09Layer : public StageBaseLayer
{
public:
	Stage1_09Layer();

	CREATE_FUNC(Stage1_09Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_09Layer_h__

