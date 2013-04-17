#include "cocos2d.h"

using namespace  cocos2d;

class StageMap
{
public:
	static StageMap* sharedInstance();
	void gotoStage(int bigIndex, int smallIndex);
	void gotoStageGameOver();
	
private:
	static StageMap* m_pInstance;
};