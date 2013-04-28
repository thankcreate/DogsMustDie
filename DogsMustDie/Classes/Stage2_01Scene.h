#ifndef Stage2_01Scene_h__
#define Stage2_01Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_01Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_01Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage2_01Scene_h__