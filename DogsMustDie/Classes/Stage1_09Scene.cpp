#include "Stage1_09Scene.h"
#include "Stage1_09Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_09Scene::getMainStageLayer()
{
	return Stage1_09Layer::create();
}


void Stage1_09Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_09Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}