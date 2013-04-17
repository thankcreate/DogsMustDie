#ifndef AboutLayer_h__
#define AboutLayer_h__
#include "cocos2d.h"

class AboutLayer : public cocos2d::CCLayer
{
public:
	AboutLayer(void);
	virtual ~AboutLayer(void);

	CREATE_FUNC(AboutLayer);

	bool init();	
	void keyBackClicked(); 
	void onExit();
	void gobackCallback(CCObject* pSender);
};


#endif // AboutLayer_h__