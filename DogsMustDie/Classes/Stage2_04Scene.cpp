#include "Stage2_04Scene.h"
#include "Stage2_04Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage2_04Scene::getMainStageLayer()
{
	return Stage2_04Layer::create();
}



const char* Stage2_04Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_4.mp3";
}