#ifndef Stage2_04Layer_h__
#define Stage2_04Layer_h__

#include "Stage2_04Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage2_04Layer : public StageBaseLayer
{
public:
	Stage2_04Layer();

	CREATE_FUNC(Stage2_04Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage2_04Layer_h__

