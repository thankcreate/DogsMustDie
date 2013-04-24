#ifndef StageBaseScene_h__
#define StageBaseScene_h__

#include "cocos2d.h"
#include "OptionDelegate.h"

using namespace cocos2d;

class StageBaseLayer;
class HelpLayer;
class RestartLayer;
class WinLayer;

class StageBaseScene : public CCScene, public OptionDelegate
{
public:
	StageBaseScene();
	~StageBaseScene();

	CC_SYNTHESIZE(StageBaseLayer*, m_pStageLayer, StageBaseLayer);
	CC_SYNTHESIZE(HelpLayer*, m_pHelpLayer, HelpLayer);
	CC_SYNTHESIZE(RestartLayer*, m_pRestartLayer, RestartLayer);
	CC_SYNTHESIZE(WinLayer*, m_pWinLayer, WinLayer);	

	virtual StageBaseLayer* getMainStageLayer() = 0;

	bool init();	
	void setLevel(int big, int small1);
	void playBGM();
	virtual const char* getBGMFileName();

	void opGoBack();
	void opReStart();
	void opSound(bool isOn);
	virtual void gotoNext() = 0;
	void showHelpLayer();
		
	void showNavigatorLose(int time, int unitLost);
	void showNavigatorWin(int time, int unitLost);
	void showNavigator(bool isWin, int time, int unitLost);
	int m_nBigLevel;
	int m_nSmallLevel;

	virtual int getTimeJudgeLine() = 0;
	virtual int getUnitLostJudgeLine() = 0;
	virtual int getScoreStartCount(int time , int unitLost);
};

#endif // StageBaseScene_h__
