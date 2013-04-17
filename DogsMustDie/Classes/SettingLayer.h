#ifndef SettingLayer_h__
#define SettingLayer_h__
#include "cocos2d.h"

class SettingLayer : public cocos2d::CCLayer
{
public:
	SettingLayer(void);
	virtual ~SettingLayer(void);

	CREATE_FUNC(SettingLayer);
	CCLayer* p;
	bool init();	
	void keyBackClicked(); 

	void onExit();

	void gobackCallback(CCObject* pSender);
	void onSoundCallback(CCObject* pSender);
	void onMusicCallback(CCObject* pSender);
	int fromBoolToIndex(bool enable);
	bool fromIndexToBool(int index);
};


#endif // SettingLayer_h__