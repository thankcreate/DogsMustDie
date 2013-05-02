#ifndef StageEndlessNavigatorLayer_h__
#define StageEndlessNavigatorLayer_h__

#include "cocos2d.h"
#include "NavigatorLayer.h"

using namespace cocos2d;

class StageBaseScene;

class StageEndlessNavigatorLayer : public NavigatorLayer
{
public:
	StageEndlessNavigatorLayer();
	virtual ~StageEndlessNavigatorLayer();

	bool init();

	CC_SYNTHESIZE(CCLabelTTF*, m_pRoundLabel, RoundLabel);
	CC_SYNTHESIZE(CCLabelTTF*, m_pBestRoundLabel, BestRoundLabel);


	virtual void setRound(int round){};
	enum
	{
		SHAKE_DISTANCE = 30
	};

protected:
	int m_nRound;
};

#endif // StageEndlessNavigatorLayer_h__