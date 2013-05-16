#include "AppOfferManager.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

#include "AppOfferDelegate.h"

AppOfferManager::AppOfferManager():
	m_pDelegate(NULL)
{

}

AppOfferManager* AppOfferManager::m_pInstance = NULL;

AppOfferManager* AppOfferManager::sharedInstance()
{
	if(!m_pInstance)
		m_pInstance = new AppOfferManager();
	return m_pInstance;
}

void AppOfferManager::show()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo; 
	jobject jobj; 
	jint _int = 1;

	bool b = JniHelper::getStaticMethodInfo(minfo,  
		"com/thankcreate/tool/AppOfferHelper",  //类路径 
		"nativeSendMsg",   //静态方法名 
		"(I)V");   //括号里的是参数，后面的是返回值。 
	jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, VIEW_VISIBLE );  
#endif
}

void AppOfferManager::hide()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo; 
	jobject jobj; 
	jint _int = 1;

	bool b = JniHelper::getStaticMethodInfo(minfo,  
		"com/thankcreate/tool/AppOfferHelper",  //类路径 
		"nativeSendMsg",   //静态方法名 
		"(I)V");   //括号里的是参数，后面的是返回值。 
	jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, VIEW_INVISIBLE );  
#endif
};

void AppOfferManager::setDelegate( AppOfferDelegate* dele )
{
	m_pDelegate = dele;
}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
extern "C"
{
	void Java_com_thankcreate_tool_AppOfferHelper_nativeAppOfferCallback(JNIEnv*  env, jobject thiz, jint a)
	{
		/*CCString* ptest = CCString::createWithFormat("%d", a);
		CCMessageBox(ptest->getCString(), "123");*/
		AppOfferManager::sharedInstance()->appOfferPointAdded(a);
	}
}
#endif

void AppOfferManager::appOfferPointAdded(int addedPoint)
{
	if(addedPoint == 0)
		return;

	int currentCoin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
	currentCoin = currentCoin + addedPoint;
	SaveIntegerToXML(KEY_COIN_COUNT, currentCoin);
	SaveUserDefault();

	if(m_pDelegate)
		m_pDelegate->pointAdded(addedPoint);
}