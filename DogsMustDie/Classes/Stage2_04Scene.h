#ifndef Stage2_04Scene_h__
#define Stage2_04Scene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class Stage2_04Scene : public StageBaseScene
{
public:	
	CREATE_FUNC(Stage2_04Scene);
	virtual StageBaseLayer* getMainStageLayer();

	void gotoNext();
	const char* getBGMFileName();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
};

#endif // Stage2_04Scene_h__