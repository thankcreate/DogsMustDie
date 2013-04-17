#include "AudioManager.h"
#include "SimpleAudioEngine.h"
#include "MyUseDefaultDef.h"
#include "Defines.h"


using namespace CocosDenshion;
using namespace cocos2d;

AudioManager* AudioManager::m_pInstance = NULL;

AudioManager::AudioManager() :
	m_strCurrentBGM(NULL),
	m_strBGMBeforeStop(NULL)
{

}

AudioManager* AudioManager::getSharedInstance()
{	
	if(!m_pInstance)
		m_pInstance = new AudioManager();
	return m_pInstance;
}

void AudioManager::preloadEffect(const char* fileName)
{	
	if(fileName != NULL)
		SimpleAudioEngine::sharedEngine()->preloadEffect(fileName);	
}

void AudioManager::playEffect(const char* fileName, bool bLoop)
{
	bool soundEnable = LoadBooleanFromXML(KEY_SWITCH_SOUNDS, true);	
	if(!soundEnable)
		return;

	if(fileName != NULL)
		SimpleAudioEngine::sharedEngine()->playEffect(fileName,bLoop);
}

void AudioManager::stopAllEffect()
{
	SimpleAudioEngine::sharedEngine()->stopAllEffects();
}

void AudioManager::playBackgroundMusic(const char* fileName1)
{
	// strcpy的原因是setBGMBeforeStop可能导致内部自我赋值
	char fileName[100];
	strcpy(fileName, fileName1);

	bool musicEnable = LoadBooleanFromXML(KEY_SWITCH_MUSIC, true);	
	if(fileName != NULL)
	{	
		setBGMBeforeStop(CCString::createWithFormat("%s", fileName));
	}
	if(!musicEnable)
		return;



	if(fileName != NULL)
	{
		CCString* input  = CCString::createWithFormat("%s",fileName);
		if(m_strCurrentBGM == NULL || m_strCurrentBGM->compare("") == 0)
		{
			setCurrentBGM(input);
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fileName, true);	
		}
		else
		{
			if(m_strCurrentBGM->compare(fileName) != 0)
			{
				setCurrentBGM(input);
				SimpleAudioEngine::sharedEngine()->playBackgroundMusic(fileName,true);
			}
		}
	}
}

void AudioManager::stopBackgroundMusic()
{
	setCurrentBGM(CCString::create(""));
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void AudioManager::enableSoundAndMusic( bool isEnable )
{
	if(isEnable == false)
	{
		SaveBooleanToXML(KEY_SWITCH_MUSIC,false);
		SaveBooleanToXML(KEY_SWITCH_SOUNDS,false);
		SaveUserDefault();
		if(m_strCurrentBGM && m_strCurrentBGM->length() != 0)
			setBGMBeforeStop((CCString*) m_strCurrentBGM->copy());
		stopAllEffect();
		stopBackgroundMusic();
	}
	else
	{
        SaveBooleanToXML(KEY_SWITCH_MUSIC,true);
        SaveBooleanToXML(KEY_SWITCH_SOUNDS,true);
        SaveUserDefault();
		if(m_strBGMBeforeStop != NULL)
		{
			playBackgroundMusic(m_strBGMBeforeStop->getCString());
		}
	}
}
