#include "Stage1_09Scene.h"
#include "Stage1_09Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_09Scene::getMainStageLayer()
{
	return Stage1_09Layer::create();
}



const char* Stage1_09Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_8.mp3";
}