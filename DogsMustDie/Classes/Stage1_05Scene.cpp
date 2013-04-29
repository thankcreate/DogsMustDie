#include "Stage1_05Scene.h"
#include "Stage1_05Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_05Scene::getMainStageLayer()
{
	return Stage1_05Layer::create();
}



const char* Stage1_05Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_4.mp3";
}