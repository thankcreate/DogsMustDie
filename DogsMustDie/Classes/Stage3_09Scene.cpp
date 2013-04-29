#include "Stage3_09Scene.h"
#include "Stage3_09Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_09Scene::getMainStageLayer()
{
	return Stage3_09Layer::create();
}



const char* Stage3_09Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_8.mp3";
}