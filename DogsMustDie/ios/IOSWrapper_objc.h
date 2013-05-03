//
//  IOSWrapper_objc.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-29.
//
//

#import <Foundation/Foundation.h>

@interface IOSWrapper_objc : NSObject<UIAlertViewDelegate>
+ (IOSWrapper_objc *)sharedInstance;

-(void)showRateusDialog;
-(void)gotoRateView;
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;
@end
