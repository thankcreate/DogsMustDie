#ifndef StageMap_h__
#define StageMap_h__

#include "cocos2d.h"

using namespace  cocos2d;

class StageBaseScene;
class StageMap
{
public:
	static StageMap* sharedInstance();
	void gotoStage(int bigIndex, int smallIndex);
	void gotoStageGameOver();


private:
	StageBaseScene* gotoStageInner( int bigIndex, int smallIndex );
	static StageMap* m_pInstance;
};

#endif // StageMap_h__
