#ifndef Stage3_01Layer_h__
#define Stage3_01Layer_h__

#include "Stage3_01Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage3_01Layer : public StageBaseLayer
{
public:
	Stage3_01Layer();

	CREATE_FUNC(Stage3_01Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage3_01Layer_h__

