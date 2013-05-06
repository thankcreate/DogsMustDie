//
//  DogsMustDieAppController.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AdMoGoDelegateProtocol.h"
#import "AdMoGoView.h"
#import "AdMoGoWebBrowserControllerUserDelegate.h"

@interface RootViewController : UIViewController <AdMoGoDelegate, AdMoGoWebBrowserControllerUserDelegate>
{
    AdMoGoView *adView;
}


@property (nonatomic, retain) AdMoGoView *adView;
-(void)initAd;
-(void)showAd;
-(void)hideAd;
@end
