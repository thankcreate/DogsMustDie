#ifndef Stage1_1Scene_h__
#define Stage1_1Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage1_1Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage1_1Scene);
	virtual StageBaseLayer* getMainStageLayer();

	void gotoNext();
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage1_1Scene_h__