#include "Stage1_2Scene.h"
#include "Stage1_2Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_2Scene::getMainStageLayer()
{
	return Stage1_2Layer::create();
}


void Stage1_2Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,2);
}

const char* Stage1_2Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}