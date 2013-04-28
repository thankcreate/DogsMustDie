#include "Stage2_04Scene.h"
#include "Stage2_04Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_04Scene::getMainStageLayer()
{
	return Stage2_04Layer::create();
}


void Stage2_04Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage2_04Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}