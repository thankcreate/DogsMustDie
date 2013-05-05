//
//  LocalizeManager.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-5-4.
//
//

#ifndef __DogsMustDie__LocalizeManager__
#define __DogsMustDie__LocalizeManager__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class LocalizeManager
{
public:
	static LocalizeManager* sharedInstance();
    static const char* makeResourceFileName(const char* rawFileName);
	static const char* getAndroidFullPathFromRelativePath(const char* path);
	static bool exists(const char* fileName);
    void initLoad();
    const char* getStringByKey(const char* key);

    
    // 这是一个字典字典
    CC_SYNTHESIZE_RETAIN(CCDictionary* , m_pLocalizeDictionary, LocalizeDictionary);
    
private:
    LocalizeManager();
    ~LocalizeManager();
	

	static LocalizeManager* m_pInstance;
};

#endif /* defined(__DogsMustDie__LocalizeManager__) */
