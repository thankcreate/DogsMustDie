#ifndef StageMap_h__
#define StageMap_h__

#include "cocos2d.h"
#include "IAPCallback.h"

using namespace  cocos2d;

class StageBaseScene;
class StageMap : public iOSBridge::Callbacks::IAPCallback
{
public:
	static StageMap* sharedInstance();
	void gotoStage(int bigIndex, int smallIndex);
	void gotoStageGameOver();

    virtual void purchased(bool isSuccessful);
    virtual void promptCanceled();

private:
	StageBaseScene* gotoStageInner( int bigIndex, int smallIndex );
	static StageMap* m_pInstance;
};

#endif // StageMap_h__
