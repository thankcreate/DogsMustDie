#ifndef Stage2_08Layer_h__
#define Stage2_08Layer_h__

#include "Stage2_08Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage2_08Layer : public StageBaseLayer
{
public:
	Stage2_08Layer();

	CREATE_FUNC(Stage2_08Layer);

	bool init();
	void initPlanets();		

};

#endif // Stage2_08Layer_h__

