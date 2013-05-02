#ifndef Stage2_03Scene_h__
#define Stage2_03Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_03Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_03Scene);
	virtual StageBaseLayer* getMainStageLayer();

	
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 38; }
};

#endif // Stage2_03Scene_h__