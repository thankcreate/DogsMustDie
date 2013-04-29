#include "Stage3_02Scene.h"
#include "Stage3_02Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_02Scene::getMainStageLayer()
{
	return Stage3_02Layer::create();
}


const char* Stage3_02Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_2.mp3";
}