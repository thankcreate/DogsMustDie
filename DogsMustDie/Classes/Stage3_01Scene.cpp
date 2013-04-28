#include "Stage3_01Scene.h"
#include "Stage3_01Layer.h"
#include "StageMap.h"


StageBaseLayer* Stage3_01Scene::getMainStageLayer()
{
	return Stage3_01Layer::create();
}



const char* Stage3_01Scene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}