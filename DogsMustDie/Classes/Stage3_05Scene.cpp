#include "Stage3_05Scene.h"
#include "Stage3_05Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_05Scene::getMainStageLayer()
{
	return Stage3_05Layer::create();
}



const char* Stage3_05Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}