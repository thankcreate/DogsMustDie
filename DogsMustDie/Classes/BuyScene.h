
#ifndef BuyScene_h__
#define BuyScene_h__



#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "BuyLayer.h"
class BuyScene : public cocos2d::CCScene
{
public:
	BuyScene(void);
	~BuyScene(void);

	virtual bool init();
	CREATE_FUNC(BuyScene);

	CC_SYNTHESIZE(BuyLayer*, m_pBuyLayer, BuyLayer);
};




#endif // BuyScene_h__