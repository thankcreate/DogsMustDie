#include "Stage2_08Scene.h"
#include "Stage2_08Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_08Scene::getMainStageLayer()
{
	return Stage2_08Layer::create();
}



const char* Stage2_08Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}