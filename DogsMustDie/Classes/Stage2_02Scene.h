#ifndef Stage2_02Scene_h__
#define Stage2_02Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_02Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_02Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 41; }
};

#endif // Stage2_02Scene_h__