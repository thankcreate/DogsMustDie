#ifndef TopBanner_h__
#define TopBanner_h__

#include "cocos2d.h"

using namespace cocos2d;

class TopBannerLayer : public CCLayer
{
public:
	TopBannerLayer();

	CREATE_FUNC(TopBannerLayer);
	bool init();

	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);
	CC_SYNTHESIZE(CCLabelTTF*, m_pContentLabel, ContentLabel);

	void show();
	void restore();
	void setContent(char* input);

protected:
	bool m_bInShow;
};

#endif // TopBanner_h__
