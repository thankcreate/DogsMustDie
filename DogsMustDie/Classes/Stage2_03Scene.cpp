#include "Stage2_03Scene.h"
#include "Stage2_03Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_03Scene::getMainStageLayer()
{
	return Stage2_03Layer::create();
}



const char* Stage2_03Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_3.mp3";
}