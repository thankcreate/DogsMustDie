#ifndef Stage2_01Layer_h__
#define Stage2_01Layer_h__

#include "Stage2_01Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage2_01Layer : public StageBaseLayer
{
public:
	Stage2_01Layer();

	CREATE_FUNC(Stage2_01Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage2_01Layer_h__

