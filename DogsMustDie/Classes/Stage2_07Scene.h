#ifndef Stage2_07Scene_h__
#define Stage2_07Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_07Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_07Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 77; }
};

#endif // Stage2_07Scene_h__