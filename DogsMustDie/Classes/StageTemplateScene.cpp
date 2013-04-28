#include "StageTemplateScene.h"
#include "StageTemplateLayer.h"
#include "StageMap.h"


StageBaseLayer* StageTemplateScene::getMainStageLayer()
{
	return StageTemplateLayer::create();
}



const char* StageTemplateScene::getBGMFileName()
{	
	return "Audio_bgm_stage_1.mp3";
}