#ifndef Stage1_04Layer_h__
#define Stage1_04Layer_h__

#include "Stage1_04Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage1_04Layer : public StageBaseLayer
{
public:
	Stage1_04Layer();

	CREATE_FUNC(Stage1_04Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_04Layer_h__

