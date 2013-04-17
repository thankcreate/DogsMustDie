#ifndef StageSelectScene_h__
#define StageSelectScene_h__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"
#include "StageSelectLayer.h"
class StageSelectScene : public cocos2d::CCScene
{
public:
	StageSelectScene(void);
	~StageSelectScene(void);

	virtual bool init();
	CREATE_FUNC(StageSelectScene);

	CC_SYNTHESIZE(StageSelectLayer*, _stage1Layer, StageSelectLayer);
};



#endif // StageSelectScene_h__

