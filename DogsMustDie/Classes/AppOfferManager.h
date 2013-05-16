#ifndef AppOfferManager_h__
#define AppOfferManager_h__

#include "cocos2d.h"


using namespace cocos2d;

class AppOfferDelegate;
class AppOfferManager
{
public:
	static AppOfferManager* sharedInstance();

	void show();
	void hide();

	enum
	{
		VIEW_VISIBLE = 1,
		VIEW_INVISIBLE = 2
	};

	void setDelegate(AppOfferDelegate* dele);
	void appOfferPointAdded(int addedPoint);

private:
	AppOfferManager();	
	static AppOfferManager* m_pInstance;
	AppOfferDelegate* m_pDelegate;
};

#endif // AppOfferManager_h__
