#include "Stage3_02Scene.h"
#include "Stage3_02Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_02Scene::getMainStageLayer()
{
	return Stage3_02Layer::create();
}


void Stage3_02Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage3_02Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}