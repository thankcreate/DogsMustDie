//
//  IAPCallback.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-26.
//
//

#ifndef StrangeAdventure_IAPCallback_h
#define StrangeAdventure_IAPCallback_h

#include "cocos2d.h"



using namespace cocos2d;

namespace iOSBridge
{
	namespace Callbacks
	{
		struct IAPItem
		{
			std::string identification;
			std::string name;
			std::string localizedTitle;
			std::string localizedDescription;
			float price;
		};
        
		class IAPCallback
		{
		public:
			virtual void productsDownloaded(const std::vector<std::string>& products) {};
            virtual void purchased(bool isSuccessful){};
            virtual void guidePurchased(bool isSuccessful) {};
            
            // 这里的意思是在1-6玩过了，想跳到2-1时，这时是先弹一个自己写的alert提示用户要通过buy来解锁
            // 如果此时被用户取消掉了alert框，则进入promptCanceled.
            virtual void promptCanceled(){};
		};
	}
}

#endif
