#ifndef PermissionManager_h__
#define PermissionManager_h__

#include "cocos2d.h"
using namespace cocos2d;
class PermissionManager
{
public:
	static PermissionManager* getSharedInstance();

	bool isStageAllowed(int bigIndex, int smallIndex);

protected:
	PermissionManager();

private:
	static PermissionManager* m_pInstance;
};

#endif // PermissionManager_h__
