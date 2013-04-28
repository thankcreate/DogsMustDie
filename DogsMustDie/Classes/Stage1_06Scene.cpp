#include "Stage1_06Scene.h"
#include "Stage1_06Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_06Scene::getMainStageLayer()
{
	return Stage1_06Layer::create();
}


void Stage1_06Scene::gotoNext()
{
	StageMap::sharedInstance()->gotoStage(1,3);
}

const char* Stage1_06Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}