//
//  IAPWrapper.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-26.
//
//

#ifndef __StrangeAdventure__IAPWrapper__
#define __StrangeAdventure__IAPWrapper__



#import "IAPCallback.h"

class IAPWrapper
{
public:
    static IAPWrapper* sharedInstance();
    // Some users might have IAP disabled
    bool canMakePayments();
    
    void requestProducts(iOSBridge::Callbacks::IAPCallback* callback);
    
    void buyProductIdentifier(const std::string& productID, iOSBridge::Callbacks::IAPCallback* callback);
    void buyProductIdentifierWithPromptDialog(const std::string& productID, const std::string& msg, iOSBridge::Callbacks::IAPCallback* callback);
    
    void clearDelegate();
    
    void restorePurchase( const std::string& msg, iOSBridge::Callbacks::IAPCallback* callback);

private:
    static IAPWrapper* m_pInstance;
    
};


#endif /* defined(__StrangeAdventure__IAPWrapper__) */
