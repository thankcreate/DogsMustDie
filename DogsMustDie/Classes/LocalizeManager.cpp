//
//  LocalizeManager.cpp
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-5-4.
//
//

#include "LocalizeManager.h"
#include "Defines.h"

LocalizeManager* LocalizeManager::m_pInstance = NULL;

LocalizeManager::LocalizeManager() :
    m_pLocalizeDictionary(NULL)
{
}

LocalizeManager::~LocalizeManager()
{
    CC_SAFE_RELEASE(m_pLocalizeDictionary);
}

LocalizeManager* LocalizeManager::sharedInstance()
{
	if(!m_pInstance)
		m_pInstance = new LocalizeManager();
	return m_pInstance;
}

void LocalizeManager::initLoad()
{
    ccLanguageType nType = CUR_LANG;
    if(nType == kLanguageChinese)
    {
        setLocalizeDictionary(CCDictionary::createWithContentsOfFile("i18n_zh.plist"));
    }
    else
    {
        setLocalizeDictionary(CCDictionary::createWithContentsOfFile("i18n_en.plist"));        
    }
}

// 在没有指定国际化资源时，要自动切换到默认资源上
const char* LocalizeManager::makeResourceFileName(const char* rawFileName)
{
    if(!rawFileName)
        return "";
    
    ccLanguageType nType = CUR_LANG;
    std::string str;
    bool bIsDefault = false;
    if(nType == kLanguageChinese)
    {
        str = rawFileName;
        int pointIndex = str.find_last_of(".");
        if(pointIndex != std::string::npos)
        {
            str.insert(pointIndex, "_zh");
        }
            
    }
    // default
    else
    {
        bIsDefault = true;
        str = rawFileName;
    }
    

    // 若非default资源，先试探是资源是否存在
    if(!bIsDefault)
    {
        const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(str.c_str());
        FILE *fp;
        fp = fopen(fullPath, "r");
        if(fp == NULL)
        {
            // 不存在时不用fclose
            str = rawFileName;
        }
        else
        {
            fclose(fp);
        }
    }
    
    return str.c_str();
}

const char* LocalizeManager::getStringByKey(const char* key)
{
    if(!key || !m_pLocalizeDictionary)
        return "";
        
    const CCString* pRes =  m_pLocalizeDictionary->valueForKey(key);
    if(pRes)
        return pRes->getCString();
    else
        return "";   

}