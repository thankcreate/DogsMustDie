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

// 注意：现在在没有指定国际化资源时，也不会自动切换到默认资源上
// 这主要是因我我太懒了，安卓上判断一个资源存不存在挺烦人的
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
	
      
	CCString* res = CCString::create(str);
    return res->getCString();
}

const char* LocalizeManager::getAndroidFullPathFromRelativePath(const char* path)
{
	// very complexed
	return "";
}


// 此函数暂时不用
bool LocalizeManager::exists(const char* fileName)
{
	if(!fileName)
		return false;

	// 这里非常坑爹
	// 安卓平台实现的fullPathFromRelativePath没有把ResourceDirectory加到前头
	// 而是原封不动的返回入参

/*
	const char* fullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fileName);
	FILE *fp = NULL;
	fp = fopen(fullPath, "rb");
	if(fp == NULL)
	{
		return false;
	}
	else
	{
		return true;
		fclose(fp);
	}*/
	return true;
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