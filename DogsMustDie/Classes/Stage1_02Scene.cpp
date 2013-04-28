#include "Stage1_02Scene.h"
#include "Stage1_02Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_02Scene::getMainStageLayer()
{
	return Stage1_02Layer::create();
}


void Stage1_02Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_02Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}