#ifndef Stage2_08Scene_h__
#define Stage2_08Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_08Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_08Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 58; }
};

#endif // Stage2_08Scene_h__