//
//  IOSWrapper_objc.m
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-29.
//
//

#import "IOSWrapper_objc.h"
#import "Defines.h"
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
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: @"^_^"
                                                          message: @"Do you want to rate this game ? It motivates us a lot! Thank you!"
                                                         delegate: self
                                                cancelButtonTitle: @"Rate Now"
                                                otherButtonTitles: @"Don't Ask Me Again", nil];
    [messageBox autorelease];
    [messageBox show];
}

-(void)gotoRateView
{
    NSString* appID = @"";
#if VERSION == VERSION_LITE
    appID = @"626699502";
#else
    appID = @"629895579";
    
#endif
    NSString* navStr = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa/wa/viewContentsUserReviews?type=Purple+Software&id=%@", appID];
    [[UIApplication sharedApplication] openURL: [NSURL URLWithString:navStr]];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if(buttonIndex == 0)
    {
        [self gotoRateView];
    }
    else
    {
      //  alertView
    }
}

@end
