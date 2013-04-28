#include "Stage1_03Scene.h"
#include "Stage1_03Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_03Scene::getMainStageLayer()
{
	return Stage1_03Layer::create();
}


void Stage1_03Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_03Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}