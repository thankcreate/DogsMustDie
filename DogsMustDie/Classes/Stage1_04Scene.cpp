#include "Stage1_04Scene.h"
#include "Stage1_04Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage1_04Scene::getMainStageLayer()
{
	return Stage1_04Layer::create();
}



const char* Stage1_04Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_3.mp3";
}