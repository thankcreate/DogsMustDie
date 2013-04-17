#ifndef AudioManager_h__
#define AudioManager_h__

#include "cocos2d.h"
using namespace cocos2d;

class AudioManager
{
public:
	static AudioManager* getSharedInstance();	
	void preloadEffect(const char* fileName);
	void playEffect(const char* fileName, bool bLoop = false);
	void stopAllEffect();
	void stopBackgroundMusic();
	void playBackgroundMusic(const char* fileName);


	CC_SYNTHESIZE_RETAIN(CCString*, m_strBGMBeforeStop, BGMBeforeStop);
	void enableSoundAndMusic(bool isEnable);

	CC_SYNTHESIZE_RETAIN(CCString*, m_strCurrentBGM, CurrentBGM);
protected:
	AudioManager();	
private:
	static AudioManager* m_pInstance;
};

#endif // AudioManager_h__
