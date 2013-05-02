#ifndef Stage2_09Scene_h__
#define Stage2_09Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_09Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_09Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 62; }
};

#endif // Stage2_09Scene_h__