#include "Stage1_04Scene.h"
#include "Stage1_04Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_04Scene::getMainStageLayer()
{
	return Stage1_04Layer::create();
}


void Stage1_04Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_04Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}