#ifndef Stage3_06Scene_h__
#define Stage3_06Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_06Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_06Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 68; }
};

#endif // Stage3_06Scene_h__