#ifndef Stage1_08Layer_h__
#define Stage1_08Layer_h__

#include "Stage1_08Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class Stage1_08Layer : public StageBaseLayer
{
public:
	Stage1_08Layer();

	CREATE_FUNC(Stage1_08Layer);

	bool init();
	void initPlanets();	
	

};

#endif // Stage1_08Layer_h__

