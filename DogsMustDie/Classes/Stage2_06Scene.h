#ifndef Stage2_06Scene_h__
#define Stage2_06Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_06Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_06Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getJudgeScoreTime() { return 47; }
};

#endif // Stage2_06Scene_h__