#ifndef Stage1_03Layer_h__
#define Stage1_03Layer_h__

#include "Stage1_03Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage1_03Layer : public StageBaseLayer
{
public:
	Stage1_03Layer();

	CREATE_FUNC(Stage1_03Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_03Layer_h__

