#ifndef Stage1_05Layer_h__
#define Stage1_05Layer_h__

#include "Stage1_05Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage1_05Layer : public StageBaseLayer
{
public:
	Stage1_05Layer();

	CREATE_FUNC(Stage1_05Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_05Layer_h__

