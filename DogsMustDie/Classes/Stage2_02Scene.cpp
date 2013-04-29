#include "Stage2_02Scene.h"
#include "Stage2_02Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_02Scene::getMainStageLayer()
{
	return Stage2_02Layer::create();
}



const char* Stage2_02Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_2.mp3";
}