#include "AdViewManager.h"
#include "Defines.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif

AdViewManager::AdViewManager()
{

}

AdViewManager* AdViewManager::m_pInstance = NULL;

AdViewManager* AdViewManager::sharedInstance()
{
	if(!m_pInstance)
		m_pInstance = new AdViewManager();
	return m_pInstance;
}

void AdViewManager::show()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo; 
	jobject jobj; 
	jint _int = 1;

	bool b = JniHelper::getStaticMethodInfo(minfo,  
		"com/thankcreate/tool/AdViewHelper",  //��·�� 
		"nativeSendMsg",   //��̬������ 
		"(I)V");   //��������ǲ�����������Ƿ���ֵ�� 
	jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, VIEW_VISIBLE );  
#endif
}

void AdViewManager::hide()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo; 
	jobject jobj; 
	jint _int = 1;

	bool b = JniHelper::getStaticMethodInfo(minfo,  
		"com/thankcreate/tool/AdViewHelper",  //��·�� 
		"nativeSendMsg",   //��̬������ 
		"(I)V");   //��������ǲ�����������Ƿ���ֵ�� 
	jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, VIEW_INVISIBLE );  
#endif
};