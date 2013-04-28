#ifndef Stage3_07Scene_h__
#define Stage3_07Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage3_07Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage3_07Scene);
	virtual StageBaseLayer* getMainStageLayer();

	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage3_07Scene_h__