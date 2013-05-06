//
//  IAPWrapper.cpp
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-26.
//
//
#import "IAPHelper_objc.h"
#import "IAPWrapper.h"

IAPWrapper* IAPWrapper::m_pInstance = NULL;

IAPWrapper* IAPWrapper::sharedInstance()
{
    if(!m_pInstance)
		m_pInstance = new IAPWrapper();
	return m_pInstance;
}

bool IAPWrapper::canMakePayments()
{
    return [[IAPHelper_objc sharedHelper] canMakePayments];
}

void IAPWrapper::requestProducts(iOSBridge::Callbacks::IAPCallback* callback)
{
    [[IAPHelper_objc sharedHelper] requestProductsWithCallback: callback];
}

void IAPWrapper::buyProductIdentifier(const std::string& productID,  iOSBridge::Callbacks::IAPCallback* callback)
{
    NSString *nsID = [NSString stringWithCString:productID.c_str()
                                        encoding:NSUTF8StringEncoding];
    
    [[IAPHelper_objc sharedHelper] buyProduct:nsID callBack:callback];
}

void IAPWrapper::buyProductIdentifierWithPromptDialog(const std::string& productID, const std::string& msg, iOSBridge::Callbacks::IAPCallback* callback)
{
    NSString *nsID = [NSString stringWithCString:productID.c_str()
                                        encoding:NSUTF8StringEncoding];
    NSString *nsMsg = [NSString stringWithCString:msg.c_str()
                                        encoding:NSUTF8StringEncoding];

    [[IAPHelper_objc sharedHelper] buyProductWithPromptDialog:nsID message:nsMsg callBack:callback];

}

void IAPWrapper::clearDelegate()
{
    [[IAPHelper_objc sharedHelper] clearDelegate];
}

void IAPWrapper::restorePurchase( const std::string& msg, iOSBridge::Callbacks::IAPCallback* callback)
{
    NSString *nsMsg = [NSString stringWithCString:msg.c_str()
                                         encoding:NSUTF8StringEncoding];
    [[IAPHelper_objc sharedHelper] restorePurchase:nsMsg callBack:callback];
}