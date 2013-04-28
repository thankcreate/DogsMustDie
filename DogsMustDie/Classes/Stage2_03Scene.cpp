#include "Stage2_03Scene.h"
#include "Stage2_03Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_03Scene::getMainStageLayer()
{
	return Stage2_03Layer::create();
}


void Stage2_03Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage2_03Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}