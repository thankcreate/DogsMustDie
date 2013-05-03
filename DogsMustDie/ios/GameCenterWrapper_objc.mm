//
//  GameCenterWrapper_objc.m
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-4-8.
//
//

#import "GameCenterWrapper_objc.h"
#include "MyUseDefaultDef.h"
#include "Defines.h"

@implementation GameCenterWrapper_objc

@synthesize gameCenterAvailable;

static GameCenterWrapper_objc *sSharedGameCenterHelper = nil;
static UIViewController* currentModalViewController = nil;

using namespace cocos2d;

+ (GameCenterWrapper_objc *) sharedGameCenterHelper
{
    if (!sSharedGameCenterHelper) {
        sSharedGameCenterHelper = [[GameCenterWrapper_objc alloc] init];
    }
    return sSharedGameCenterHelper;
}

//用于验证
- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer =@"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}

- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}

//后台回调登陆验证
- (void)authenticationChanged {
    
    bool test = [GKLocalPlayer localPlayer].isAuthenticated;
    
    if ([GKLocalPlayer localPlayer].isAuthenticated &&!userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
    
}

- (void)authenticateLocalUser {
    
    if (!gameCenterAvailable) return;
    
    NSLog(@"Authenticating local user...");
    if ([GKLocalPlayer localPlayer].authenticated == NO) {
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
    } else {
        NSLog(@"Already authenticated!");
    }
}

//显示排行榜
- (void) showLeaderboard
{
    if (!gameCenterAvailable) return;
    
    GKLeaderboardViewController *leaderboardController = [[GKLeaderboardViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.leaderboardDelegate = self;
        
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardController animated:YES];
    }
}

//关闭排行榜回调
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    if(currentModalViewController !=nil){
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}

// 显示成就
- (void) showAchievements
{
    if (!gameCenterAvailable) return;
    
    GKAchievementViewController *leaderboardController = [[GKAchievementViewController alloc] init];
    if (leaderboardController != nil) {
        leaderboardController.achievementDelegate = self;
        
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        currentModalViewController = [[UIViewController alloc] init];
        [window addSubview:currentModalViewController.view];
        [currentModalViewController presentModalViewController:leaderboardController animated:YES];
    }
    

}

// 关闭成就回调
- (void)achievementViewControllerDidFinish:(GKLeaderboardViewController *)viewController{
    if(currentModalViewController !=nil){
        [currentModalViewController dismissModalViewControllerAnimated:NO];
        [currentModalViewController release];
        [currentModalViewController.view removeFromSuperview];
        currentModalViewController = nil;
    }
}

- (void) reportAchievement:(NSString*)aid
{
    if (!gameCenterAvailable)
        return;
    
    if(aid == nil)
        return;
    
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    bool reported = [defaults boolForKey:aid];
    if(reported == YES)
        return;
    
    GKAchievement* achievement = [[GKAchievement alloc] initWithIdentifier:aid];
    achievement.percentComplete = 100.0;
    achievement.showsCompletionBanner = YES;
    [achievement reportAchievementWithCompletionHandler:^(NSError *error){
        if(error == nil)
        {
            [defaults setBool:YES forKey:aid];
            [defaults synchronize];
        }
        else{
            // Do nothing by now
        }
    }];
    
    }

- (void) reportScore:(int64_t)nScore
{
    if (!gameCenterAvailable)
        return;
    
    int lowest = LoadIntegerFromXML(KEY_HIGHEST_ENDLESS_ROUND, 0);
    if(nScore <= lowest)
        return;
    SaveIntegerToXML(KEY_HIGHEST_ENDLESS_ROUND, nScore);
    SaveUserDefault();
    
    GKScore* score = [[GKScore alloc] initWithCategory:@"grp.com.thankcreate.IQLeaderboard"];
    score.value = nScore;
    [score reportScoreWithCompletionHandler:nil];
}

@end 
