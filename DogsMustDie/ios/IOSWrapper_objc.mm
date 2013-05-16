//
//  IOSWrapper_objc.m
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-29.
//
//

#import "IOSWrapper_objc.h"
#import "Defines.h"
#import "AppController.h"
#include "LocalizeManager.h"
#import "MobClick.h"

static IOSWrapper_objc * sharedInstance = nil;

@implementation IOSWrapper_objc

+ (IOSWrapper_objc *)sharedInstance
{
    @synchronized(self) {
        if (sharedInstance == nil) {
            sharedInstance = [[IOSWrapper_objc alloc] init];
        }
    }
    return sharedInstance;
}

-(void)showRateusDialog
{
    NSString *nsMsg = [NSString stringWithCString:I18N_STR("IOS_Rate_Us_Description")
                                         encoding:NSUTF8StringEncoding];
    NSString *nsRateNow = [NSString stringWithCString:I18N_STR("IOS_Rate_Us_Yes")
                                         encoding:NSUTF8StringEncoding];
    NSString *nsNo = [NSString stringWithCString:I18N_STR("IOS_Rate_Us_No")
                                         encoding:NSUTF8StringEncoding];

    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @"^_^"
                                                          message: nsMsg
                                                         delegate: self
                                                cancelButtonTitle: nsNo
                                                otherButtonTitles: nsRateNow, nil];
    [messageBox autorelease];
    [messageBox show];
}

-(void)gotoRateView
{
    NSString* appID = @"";
#if VERSION == VERSION_LITE
    appID = @"645248568";
#else
    appID = @"645246774";
    
#endif
    NSString* navStr = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@", appID];
    [[UIApplication sharedApplication] openURL: [NSURL URLWithString:navStr]];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(buttonIndex == 1)
    {
        [self gotoRateView];
    }
    else
    {
      //  alertView
    }
}

-(void)showAd
{
    AppController* appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController.viewController showAd];
}

-(void)hideAd
{
    AppController* appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController.viewController hideAd];
}

-(NSString*)getUmengParam:(NSString*)key
{
    NSString *nsRet = [MobClick getConfigParams:key];


    return nsRet;
}

@end
