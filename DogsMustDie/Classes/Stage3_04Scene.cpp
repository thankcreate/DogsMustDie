#include "Stage3_04Scene.h"
#include "Stage3_04Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_04Scene::getMainStageLayer()
{
	return Stage3_04Layer::create();
}



const char* Stage3_04Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}