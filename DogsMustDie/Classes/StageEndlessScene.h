#ifndef StageEndlessScene_h__
#define StageEndlessScene_h__



#include "StageBaseScene.h"

using namespace cocos2d;

class NoticeLayer;
class StageEndlessScene : public StageBaseScene
{
public:	
	StageEndlessScene();
	CREATE_FUNC(StageEndlessScene);
	bool init();

	CC_SYNTHESIZE(NoticeLayer*, m_pNoticeLayer, NoticeLayer);

	virtual StageBaseLayer* getMainStageLayer();
	

	const char* getBGMFileName();

	virtual void showNavigator(bool isWin, int time, int unitLost);
	virtual void customizeTopBannerLayer();

	int getTimeJudgeLine() { return 30 ;}
	int getUnitLostJudgeLine() { return 30; }
	int getScoreStartCount(int time , int unitLost) {return 3;}
	bool gotoNext();
	void opGoBack();

	void showNavigatorLose(int time, int unitLost);
	void showNavigatorWin(int time, int unitLost);
	void opReStart();
	void showNoticeLayer();	
	void continueRestartWithThisRound();	
protected:
	int m_nEndlessRound;
};

#endif // StageEndlessScene_h__