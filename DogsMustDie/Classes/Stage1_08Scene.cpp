#include "Stage1_08Scene.h"
#include "Stage1_08Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_08Scene::getMainStageLayer()
{
	return Stage1_08Layer::create();
}



const char* Stage1_08Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_6.mp3";
}