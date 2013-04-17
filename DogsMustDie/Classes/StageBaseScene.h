#ifndef StageBaseScene_h__
#define StageBaseScene_h__

#include "cocos2d.h"
#include "OptionDelegate.h"

using namespace cocos2d;

class StageBaseLayer;
class HelpLayer;

class StageBaseScene : public CCScene, public OptionDelegate
{
public:
	StageBaseScene();
	~StageBaseScene();

	CC_SYNTHESIZE(StageBaseLayer*, m_pStageLayer, StageBaseLayer);
	CC_SYNTHESIZE(HelpLayer*, m_pHelpLayer, HelpLayer);
	int m_nBigLevel;
	int m_nSmallLevel;

	virtual StageBaseLayer* getMainStageLayer() = 0;

	bool init();	
	void setLevel(int big, int small1);
	void playBGM();
	const char* getBGMFileName();

	void opGoBack();
	void opReStart();
	void opSound(bool isOn);
	void showHelpLayer();
};

#endif // StageBaseScene_h__
