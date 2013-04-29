#include "Stage3_03Scene.h"
#include "Stage3_03Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_03Scene::getMainStageLayer()
{
	return Stage3_03Layer::create();
}



const char* Stage3_03Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_3.mp3";
}