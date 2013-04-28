#include "Stage1_07Scene.h"
#include "Stage1_07Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_07Scene::getMainStageLayer()
{
	return Stage1_07Layer::create();
}


void Stage1_07Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_07Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}