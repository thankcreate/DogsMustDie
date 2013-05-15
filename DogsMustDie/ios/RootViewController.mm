//
//  DogsMustDieAppController.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "RootViewController.h"
#include "Defines.h"
#include "MyUseDefaultDef.h"



@implementation RootViewController
#ifdef USE_AD
@synthesize adView;
#endif

- (void)dealloc
{
#ifdef USE_AD
    adView.delegate = nil;
    adView.adWebBrowswerDelegate = nil;
#endif
    [super dealloc];
}


 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}




// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    [super loadView];
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

-(void)initAd
{    
#ifdef USE_AD
    bool bPurchased = LoadBooleanFromXML(KEY_PRO_UPGRADE_PURCHASED, false);
    if(bPurchased)
        return;
    
    adView = [[AdMoGoView alloc] initWithAppKey:@"7e6e18012516460d94ee6068f0325869"
                                             adType:AdViewTypeNormalBanner
                                        expressMode:YES
                                 adMoGoViewDelegate:self];    
    
    adView.adWebBrowswerDelegate = self;
    
    // typedef enum {
    // AdViewTypeUnknown = 0,
    // AdViewTypeNormalBanner = 1,
    // AdViewTypeLargeBanner = 2,
    // AdViewTypeMediumBanner = 3,
    // AdViewTypeRectangle = 4,
    // AdViewTypeSky = 5,
    // AdViewTypeFullScreen = 6,
    // AdViewTypeVideo = 7,
    // AdViewTypeiPadNormalBanner = 8, //ipad use iphone banner
    // } AdViewType;

    CGSize size = self.view.frame.size;
    
    // 注意，这里由于做了一个横向，所以size.width是高，size.height是宽！切记切记。
    adView.frame = CGRectMake(size.width/2 - 160,size.height - 200, 0,0);
    adView.frame = CGRectMake(size.height/2 - 160, size.width - 50, 0,0);
    [self.view addSubview:adView];
    self.adView.hidden = true;
    [adView release];
#endif
}

-(void)showAd
{
#ifdef USE_AD
    bool bPurchased = LoadBooleanFromXML(KEY_PRO_UPGRADE_PURCHASED, false);
    if(bPurchased)
        return;
    
    adView.hidden = false;
#endif
}

-(void)hideAd
{
#ifdef USE_AD
    bool bPurchased = LoadBooleanFromXML(KEY_PRO_UPGRADE_PURCHASED, false);
    if(bPurchased)
        return;
    
    adView.hidden = true;
#endif
}



#ifdef USE_AD
/**
 * 广告开始请求回调
 */
- (void)adMoGoDidStartAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告开始请求回调");
}
/**
 * 广告接收成功回调
 */
- (void)adMoGoDidReceiveAd:(AdMoGoView *)adMoGoView{
    NSLog(@"广告接收成功回调");
}




- (UIViewController *)viewControllerForPresentingModalView
{
    return self;
}
#endif 

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskLandscape;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

@end
