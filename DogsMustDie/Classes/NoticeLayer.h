#ifndef NoticeLayer_h__
#define NoticeLayer_h__

#include "cocos2d.h"

using namespace cocos2d;

class StageBaseScene;
class NoticeLayerDelegate;
class NoticeLayer : public CCLayer
{
public:
	NoticeLayer();
	~NoticeLayer();

	CREATE_FUNC(NoticeLayer);

	bool init();

	CC_SYNTHESIZE(StageBaseScene*, m_pStageScene, StageScene);	
	CC_SYNTHESIZE(CCSprite*, m_pFrame, Frame);	
	CC_SYNTHESIZE(CCLayerColor*, m_pColorLayer, ColorLayer);
	CC_SYNTHESIZE(CCLabelTTF*, m_pTitleLabel, TitleLabel);
	CC_SYNTHESIZE(CCLabelTTF*, m_pContentLabel, ContentLabel);
	CC_SYNTHESIZE(NoticeLayerDelegate*, m_pDelegate, Delegate);



	void nextCallback(CCObject* object);

	virtual void show();
	virtual void restore();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void onEnterTransitionDidFinish();
	enum
	{
		SHAKE_DISTANCE = 30
	};

protected:
	bool m_bInShow; // 主要是为了防止用户连续点击gotonext 或者是restart
	int m_nProcessIndex; // 对话框进度
};

#endif // NoticeLayer_h__