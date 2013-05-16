#include "PermissionManager.h"
#include "MyUseDefaultDef.h"
#include "Defines.h"

PermissionManager* PermissionManager::m_pInstance = NULL;

PermissionManager::PermissionManager()
{
}

PermissionManager* PermissionManager::getSharedInstance()
{	
	if(!m_pInstance)
		m_pInstance = new PermissionManager();
	return m_pInstance;
}

// ???????????1???
bool PermissionManager::isStageAllowed(int bigIndex, int smallIndex)
{
	bool res = false;

	CCUserDefault::purgeSharedUserDefault();
	int toBig = LoadIntegerFromXML(KEY_PLAYED_TO_BIG, 1);
	int toSmall =  LoadIntegerFromXML(KEY_PLAYED_TO_SMALL, 1);

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    // ?????????
    bool bIsPurchased = LoadBooleanFromXML(KEY_PRO_UPGRADE_PURCHASED ,false);
    if(bigIndex >= LOCK_BEGIN_INDEX && !bIsPurchased)
    {
        return false;
    }
#endif
    //return true;
    
	if(bigIndex < toBig)
		res = true;
	else if(bigIndex == toBig)
	{
        if(smallIndex <= toSmall)
			res = true;
	}

	return res;
}
