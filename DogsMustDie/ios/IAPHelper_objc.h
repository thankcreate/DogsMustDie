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

#define kInAppPurchaseProUpgradeProductId  @"com.thankcreate.DogsMustDie.UpgradeToPro"

#define kInAppPurchaseCoin10_Pro @"com.thankcreate.DogsMustDie.10Coins"
#define kInAppPurchaseCoin10_Lite @"com.thankcreate.DogsMustDie.10CoinsLite"

#define kInAppPurchaseCoin20_Pro @"com.thankcreate.DogsMustDie.20Coins"
#define kInAppPurchaseCoin20_Lite @"com.thankcreate.DogsMustDie.20CoinsLite"

#define kInAppPurchaseCoin50_Pro @"com.thankcreate.DogsMustDie.50Coins"
#define kInAppPurchaseCoin50_Lite @"com.thankcreate.DogsMustDie.50CoinsLite"

#if VERSION == VERSION_LITE
#define kInAppPurchaseCoin10_Auto kInAppPurchaseCoin10_Lite
#else
#define kInAppPurchaseCoin10_Auto kInAppPurchaseCoin10_Pro
#endif

#if VERSION == VERSION_LITE
#define kInAppPurchaseCoin20_Auto kInAppPurchaseCoin20_Lite
#else
#define kInAppPurchaseCoin20_Auto kInAppPurchaseCoin20_Pro
#endif


#if VERSION == VERSION_LITE
#define kInAppPurchaseCoin50_Auto kInAppPurchaseCoin50_Lite
#else
#define kInAppPurchaseCoin50_Auto kInAppPurchaseCoin50_Pro
#endif




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
- (void)restorePurchase:(NSString*)msg callBack:(iOSBridge::Callbacks::IAPCallback*)callback;

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue;
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error;
@end