#include "Stage3_08Scene.h"
#include "Stage3_08Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_08Scene::getMainStageLayer()
{
	return Stage3_08Layer::create();
}



const char* Stage3_08Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}