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
            
            // �������˼����1-6����ˣ�������2-1ʱ����ʱ���ȵ�һ���Լ�д��alert��ʾ�û�Ҫͨ��buy������
            // �����ʱ���û�ȡ������alert�������promptCanceled.
            virtual void promptCanceled(){};
		};
	}
}

#endif
