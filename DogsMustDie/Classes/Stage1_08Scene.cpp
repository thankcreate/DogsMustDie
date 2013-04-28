#include "Stage1_08Scene.h"
#include "Stage1_08Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_08Scene::getMainStageLayer()
{
	return Stage1_08Layer::create();
}


void Stage1_08Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_08Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}