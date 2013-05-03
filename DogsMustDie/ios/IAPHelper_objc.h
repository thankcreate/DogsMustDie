//
//  IAPHelper_objc.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-26.
//
//

#import <Foundation/Foundation.h>
#import "StoreKit/StoreKit.h"
#include "IAPCallback.h"
#include "MyUseDefaultDef.h"

#define kProductsLoadedNotification @"ProductsLoaded"
#define kProductPurchasedNotification       @"ProductPurchased"
#define kProductPurchaseFailedNotification  @"ProductPurchaseFailed"

#define kUserDefaultProData  @"PRO_VER_DATA"
#define kInAppPurchaseProUpgradeProductId  @"com.thankcreate.RageAdventure.UpgradeToPro"

#define kInAppPurchasePromptProductId_Pro @"com.thankcreate.RageAdventure.Prompt_Pro"
#define kInAppPurchasePromptProductId_Lite @"com.thankcreate.RageAdventure.Prompt_Lite"



@interface IAPHelper_objc : NSObject<SKProductsRequestDelegate, SKPaymentTransactionObserver, UIAlertViewDelegate> {
	NSSet * _productIdentifiers;
	NSArray * _products;
	NSMutableSet * _purchasedProducts;
	SKProductsRequest * _request;
    NSString* _lastProductID;
	iOSBridge::Callbacks::IAPCallback* latestIAPCallback;
}

@property (retain) NSSet *productIdentifiers;
@property (retain) NSArray * products;
@property (retain) NSMutableSet *purchasedProducts;
@property (retain) SKProductsRequest *request;
@property (retain) NSString* lastProductID;

+ (IAPHelper_objc *)sharedHelper;


- (void)requestProducts;
- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers;
- (bool)canMakePayments;
- (void)requestProductsWithCallback:(iOSBridge::Callbacks::IAPCallback*)callback;
- (void)buyProduct:(NSString*) product callBack:(iOSBridge::Callbacks::IAPCallback*)cb;
- (void)buyProductWithPromptDialog:(NSString*) product message:(NSString*)msg callBack:(iOSBridge::Callbacks::IAPCallback*)cb;
- (void)clearDelegate;
- (void)restorePurchase:(iOSBridge::Callbacks::IAPCallback*)callback;

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue;
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error;
@end