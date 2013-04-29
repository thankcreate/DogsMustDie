#include "Stage1_06Scene.h"
#include "Stage1_06Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_06Scene::getMainStageLayer()
{
	return Stage1_06Layer::create();
}


const char* Stage1_06Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_5.mp3";
}