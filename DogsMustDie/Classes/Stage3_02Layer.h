#ifndef Stage3_02Layer_h__
#define Stage3_02Layer_h__

#include "Stage3_02Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage3_02Layer : public StageBaseLayer
{
public:
	Stage3_02Layer();

	CREATE_FUNC(Stage3_02Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage3_02Layer_h__

