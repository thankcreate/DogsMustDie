
#ifndef SettingScene_h__
#define SettingScene_h__

#include "cocos2d.h"
#include "SettingLayer.h"
class SettingScene : public cocos2d::CCScene
{
public:
	SettingScene(void);
	~SettingScene(void);

	virtual bool init();
	CREATE_FUNC(SettingScene);

	CC_SYNTHESIZE(SettingLayer*, m_pSettingLayer, SettingLayer);
};




#endif // SettingScene_h__