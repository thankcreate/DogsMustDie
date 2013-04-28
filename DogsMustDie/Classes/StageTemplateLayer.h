#ifndef StageTemplateLayer_h__
#define StageTemplateLayer_h__

#include "StageTemplateLayer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Planet;

// ��һ���кܶ�̳̲���
class StageTemplateLayer : public StageBaseLayer
{
public:
	StageTemplateLayer();

	CREATE_FUNC(StageTemplateLayer);

	bool init();
	void initPlanets();		

};

#endif // StageTemplateLayer_h__

