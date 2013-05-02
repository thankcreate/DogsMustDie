#ifndef StageEndlessScene_h__
#define StageEndlessScene_h__



#include "StageBaseScene.h"

using namespace cocos2d;


class StageEndlessScene : public StageBaseScene
{
public:	
	StageEndlessScene();
	CREATE_FUNC(StageEndlessScene);
	virtual StageBaseLayer* getMainStageLayer();
	bool init();

	const char* getBGMFileName();

	virtual void showNavigator(bool isWin, int time, int unitLost);

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
	void gotoNext();
	void opGoBack();

	void showNavigatorLose(int time, int unitLost);
	void showNavigatorWin(int time, int unitLost);
	void opReStart();
protected:
	int m_nEndlessRound;
};

#endif // StageEndlessScene_h__