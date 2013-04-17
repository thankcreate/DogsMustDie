#include "Stage1_1Scene.h"
#include "Stage1_1Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_1Scene::getMainStageLayer()
{
	return Stage1_1Layer::create();
}


void gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,2);
}