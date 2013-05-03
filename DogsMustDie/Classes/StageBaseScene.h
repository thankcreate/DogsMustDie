#ifndef StageBaseScene_h__
#define StageBaseScene_h__

#include "cocos2d.h"
#include "OptionDelegate.h"

using namespace cocos2d;

class StageBaseLayer;
class HelpLayer;
class NavigatorLayer;
class PauseLayer;
class TopBannerLayer;
class StageBaseScene : public CCScene, public OptionDelegate
{
public:
	StageBaseScene();
	~StageBaseScene();

	CC_SYNTHESIZE(StageBaseLayer*, m_pStageLayer, StageBaseLayer);
	CC_SYNTHESIZE(HelpLayer*, m_pHelpLayer, HelpLayer);
	CC_SYNTHESIZE(NavigatorLayer*, m_pRestartLayer, RestartLayer);
	CC_SYNTHESIZE(NavigatorLayer*, m_pWinLayer, WinLayer);	
	CC_SYNTHESIZE(PauseLayer*, m_pPauseLayer, PauseLayer);
	CC_SYNTHESIZE(TopBannerLayer*, m_pTopBannerLayer, TopBannerLayer);
	virtual StageBaseLayer* getMainStageLayer() = 0;

	bool init();	
	void setLevel(int big, int small1);
	void playBGM();
	virtual const char* getBGMFileName();

	virtual void opGoBack();
	virtual void opReStart();
	virtual void opSound(bool isOn);
	virtual void gotoNext();
	void showHelpLayer();
		
	virtual void showNavigatorLose(int time, int unitLost);
	virtual void showNavigatorWin(int time, int unitLost);
	virtual void showNavigator(bool isWin, int time, int unitLost);
	int m_nBigLevel;
	int m_nSmallLevel;

	virtual int getTimeJudgeLine() = 0;
	virtual int getUnitLostJudgeLine() = 0;
	virtual int getScoreStartCount(int time , int unitLost);

	virtual int getJudgeScoreTime() { return 40; }
	void showPauseLayer();
	void showTopBannerLayer(char* content, float restoreTime);
	void restoreTopBannerLayer(float dt);
	void showTopBannerLayerWithCustomizedContent(float restoreTime);
	virtual void customizeTopBannerLayer();
};

#endif // StageBaseScene_h__
