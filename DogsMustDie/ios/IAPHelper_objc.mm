//
//  IAPHelper_objc.m
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-26.
//
//
#import "IAPHelper_objc.h"

#include "Defines.h"
#include "LocalizeManager.h"

static IAPHelper_objc * sharedHelper = nil;

@implementation IAPHelper_objc

@synthesize productIdentifiers = _productIdentifiers;
@synthesize products = _products;
@synthesize purchasedProducts = _purchasedProducts;
@synthesize request = _request;
@synthesize lastProductID = _lastProductID;

#define kBuyAlertTag 2
#define kRestoreAlertTag 3

+ (IAPHelper_objc *)sharedHelper
{
    @synchronized(self) {
        if (sharedHelper == nil) {
            sharedHelper = [[IAPHelper_objc alloc] init];
        }
    }
    return sharedHelper;
}


- (id)initWithProductIdentifiers:(NSSet *)productIdentifiers{
	latestIAPCallback = nil;
    
	if ((self = [super init])) {
		_productIdentifiers = [productIdentifiers retain];
        
		// Check for previously purchased products
		NSMutableSet * purchasedProducts = [NSMutableSet set];
		for (NSString * productIdentifier in _productIdentifiers)
		{
			BOOL productPurchased = [[NSUserDefaults standardUserDefaults] boolForKey:productIdentifier];
			if (productPurchased)
			{
				[purchasedProducts addObject:productIdentifier];
				NSLog(@"Previously purchased: %@", productIdentifier);
			}
			NSLog(@"Not purchased: %@", productIdentifier);
		}
        
		self.purchasedProducts = purchasedProducts;
	}
	return self;
}

- (bool)canMakePayments
{
	return [SKPaymentQueue canMakePayments];
}

- (void)requestProductsWithCallback:(iOSBridge::Callbacks::IAPCallback*)callback
{
	latestIAPCallback = callback;
	[self requestProducts];

}

- (void)requestProducts {
	self.request = [[[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers] autorelease];
	_request.delegate = self;
	[_request start];    
}


#pragma mark - SKProductsRequestDelegate delegate
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
	self.products = response.products;
	self.request = nil;
    
	[[NSNotificationCenter defaultCenter] postNotificationName:kProductsLoadedNotification object:_products];
    
	std::vector<id> items;
    NSArray *products = response.products;
    SKProduct* proUpgradeProduct = [products count] == 1 ? [[products firstObject] retain] : nil;
    if (proUpgradeProduct)
    {
        NSLog(@"Product title: %@" , proUpgradeProduct.localizedTitle);
        NSLog(@"Product description: %@" , proUpgradeProduct.localizedDescription);
        NSLog(@"Product price: %@" , proUpgradeProduct.price);
        NSLog(@"Product id: %@" , proUpgradeProduct.productIdentifier);
    }
    
//     NSArray* invalid = response.invalidProductIdentifiers;
    
	// populate UI
	//for(int i=0;iproductsDownloaded(items);
}
        
- (void)productsLoaded:(NSNotification *)notification {
    [NSObject cancelPreviousPerformRequestsWithTarget:self];
}

- (void)buyProduct:(NSString*) product callBack:(iOSBridge::Callbacks::IAPCallback*)cb
{
    [self setLastProductID:product];
    latestIAPCallback = cb;
    [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
    SKPayment *payment = [SKPayment paymentWithProductIdentifier:_lastProductID];
    [[SKPaymentQueue defaultQueue] addPayment:payment];
    
}

- (void)restorePurchase:(NSString*)msg callBack:(iOSBridge::Callbacks::IAPCallback*)callback
{
    latestIAPCallback = callback;    
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @"^_^"
                                                          message: msg
                                                         delegate: self
                                                cancelButtonTitle: @"Cancel"
                                                otherButtonTitles: @"OK", nil];
    [messageBox setTag:kRestoreAlertTag];
    [messageBox autorelease];
    [messageBox show];
}


//  这个是响应checkIfBuyBefore中的restoreCompletedTransactions成功的回调
- (void) paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue
{
    bool flag = false;
    for (SKPaymentTransaction *transaction in queue.transactions)
    {
        NSString *productID = transaction.payment.productIdentifier;
        if([productID compare:kInAppPurchaseProUpgradeProductId] == NSOrderedSame)
        {
            SaveBooleanToXML(KEY_PRO_UPGRADE_PURCHASED, true);
            SaveUserDefault();
            flag = true;
            if(latestIAPCallback)
            {
                [self alertSuccessDialog];
                latestIAPCallback->purchased(true);
            }
        }
    }
    
    if(!flag)
    {
        UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @">_<"
                                                              message: @"You had not purchased before."
                                                             delegate: self
                                                    cancelButtonTitle: @"OK"
                                                    otherButtonTitles: nil];
        [messageBox autorelease];
        [messageBox show];
    }
}

//  这个是响应checkIfBuyBefore中的restoreCompletedTransactions失败的回调
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error
{
    for (SKPaymentTransaction *transaction in queue.transactions)
    {
        NSString *productID = transaction.payment.productIdentifier;
        if([productID compare:kInAppPurchaseProUpgradeProductId] == NSOrderedSame)
        {
            SaveBooleanToXML(KEY_PRO_UPGRADE_PURCHASED, true);
            SaveUserDefault();
            if(latestIAPCallback)
            {
                [self alertErrorDialog];
                latestIAPCallback->purchased(false);
            }
        }        
    }
}

- (void) alertSuccessDialog
{
    NSString *nsMsg = [NSString stringWithCString:I18N_STR("IAP_Purchase_Success_Description")
                                         encoding:NSUTF8StringEncoding];

    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @"^_^"
                                                          message: nsMsg
                                                         delegate: self
                                                cancelButtonTitle: @"OK"
                                                otherButtonTitles: nil];
    [messageBox autorelease];
    [messageBox show];
}

- (void) alertErrorDialog
{
    NSString *nsMsg = [NSString stringWithCString:I18N_STR("IAP_Purchase_Fail_Description")
                                         encoding:NSUTF8StringEncoding];
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @">_<"
                                                          message: nsMsg
                                                         delegate: self
                                                cancelButtonTitle: @"OK"
                                                otherButtonTitles: nil];
    [messageBox autorelease];
    [messageBox show];
}


- (void)buyProductWithPromptDialog:(NSString*) product message:(NSString*)msg callBack:(iOSBridge::Callbacks::IAPCallback*)cb
{
    [self setLastProductID:product];
    latestIAPCallback = cb;
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @"^_^"
                                                          message: msg
                                                         delegate: self
                                                cancelButtonTitle: @"Cancel"
                                                otherButtonTitles: @"OK", nil];
    [messageBox setTag:kBuyAlertTag];
    [messageBox autorelease];
    [messageBox show];
}

// UIAlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if([alertView tag] == kBuyAlertTag)
    {
        if(buttonIndex == 0)
        {
            if(latestIAPCallback)
                latestIAPCallback->promptCanceled();
        }
        else if(buttonIndex == 1)
        {
            [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
            SKPayment *payment = [SKPayment paymentWithProductIdentifier:_lastProductID];
            [[SKPaymentQueue defaultQueue] addPayment:payment];
        }
    }
    else if([alertView tag] == kRestoreAlertTag)
    {
        if(buttonIndex == 0)
        {
            if(latestIAPCallback)
                latestIAPCallback->promptCanceled();
        }
        else if(buttonIndex == 1)
        {
            [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
        }
    }
    
}

- (void)recordTransaction:(SKPaymentTransaction *)transaction
{
    if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseProUpgradeProductId])
    {
        // save the transaction receipt to disk
        [[NSUserDefaults standardUserDefaults] setValue:transaction.transactionReceipt forKey:kUserDefaultProData ];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}


- (void)provideContent:(NSString *)productId
{
    if ([productId isEqualToString:kInAppPurchaseProUpgradeProductId])
    {
        // enable the pro features
        [[NSUserDefaults standardUserDefaults] setBool:YES forKey:@KEY_PRO_UPGRADE_PURCHASED];
        [[NSUserDefaults standardUserDefaults] synchronize];
    }
}

- (void)finishTransaction:(SKPaymentTransaction *)transaction wasSuccessful:(BOOL)wasSuccessful
{
    // remove the transaction from the payment queue.
    [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
    
    // 升级到完整版
    NSDictionary *userInfo = [NSDictionary dictionaryWithObjectsAndKeys:transaction, @"transaction" , nil];
    if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseProUpgradeProductId])
    {
        if (wasSuccessful)
        {
            SaveBooleanToXML(KEY_PRO_UPGRADE_PURCHASED, true);
            SaveUserDefault();
            if(latestIAPCallback != nil)
            {
                [self alertSuccessDialog];
                latestIAPCallback->purchased(true);
            }
        }
        else
        {
            if(latestIAPCallback != nil)
            {
                [self alertErrorDialog];
                latestIAPCallback->purchased(false);
            }
        }
    }
    // 10 coin
    else if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseCoin10_Auto])
    {
        if (wasSuccessful)
        {
            int coin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
            coin += 10;
            SaveIntegerToXML(KEY_COIN_COUNT, coin);
            SaveUserDefault();
            if(latestIAPCallback != nil)
            {
                [self alertSuccessDialog];
                latestIAPCallback->purchased(true);
            }
        }
        else
        {
            if(latestIAPCallback != nil)
            {
                [self alertErrorDialog];
                latestIAPCallback->purchased(false);
            }
        }
    }
    // 20 coin
    else if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseCoin20_Auto])
    {
        if (wasSuccessful)
        {
            int coin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
            coin += 20;
            SaveIntegerToXML(KEY_COIN_COUNT, coin);
            SaveUserDefault();
            if(latestIAPCallback != nil)
            {
                [self alertSuccessDialog];
                latestIAPCallback->purchased(true);
            }
        }
        else
        {
            if(latestIAPCallback != nil)
            {
                [self alertErrorDialog];
                latestIAPCallback->purchased(false);
            }
        }
    }
    // 50 coin
    else if ([transaction.payment.productIdentifier isEqualToString:kInAppPurchaseCoin50_Auto])
    {
        if (wasSuccessful)
        {
            int coin = LoadIntegerFromXML(KEY_COIN_COUNT, 0);
            coin += 50;
            SaveIntegerToXML(KEY_COIN_COUNT, coin);
            SaveUserDefault();
            if(latestIAPCallback != nil)
            {
                [self alertSuccessDialog];
                latestIAPCallback->purchased(true);
            }
        }
        else
        {
            if(latestIAPCallback != nil)
            {
                [self alertErrorDialog];
                latestIAPCallback->purchased(false);
            }
        }
    }
}

- (void)completeTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction];
    [self provideContent:transaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has been restored and and successfully completed
//
- (void)restoreTransaction:(SKPaymentTransaction *)transaction
{
    [self recordTransaction:transaction.originalTransaction];
    [self provideContent:transaction.originalTransaction.payment.productIdentifier];
    [self finishTransaction:transaction wasSuccessful:YES];
}
//
// called when a transaction has failed
//
- (void)failedTransaction:(SKPaymentTransaction *)transaction
{
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        // error!
        [self finishTransaction:transaction wasSuccessful:NO];
    }
    else
    {
        // this is fine, the user just cancelled, so don’t notify
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
}


- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for (SKPaymentTransaction *transaction in transactions)
    {
        int i = transaction.transactionState;
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
                break;
            default:
                break;
        }
    }
}



- (void)clearDelegate
{
    latestIAPCallback = nil;
}


- (void)dealloc
{
    [_productIdentifiers release];
    _productIdentifiers = nil;
    [_products release];
    _products = nil;
    [_purchasedProducts release];
    _purchasedProducts = nil;
    [_request release];
    _request = nil;
    [super dealloc];
}

@end