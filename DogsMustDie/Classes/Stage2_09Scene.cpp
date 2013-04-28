#include "Stage2_09Scene.h"
#include "Stage2_09Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_09Scene::getMainStageLayer()
{
	return Stage2_09Layer::create();
}



const char* Stage2_09Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}