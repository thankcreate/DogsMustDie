//
//  GameCenterWrapper_objc.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-4-8.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>

@interface GameCenterWrapper_objc : NSObject<GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate, GKMatchmakerViewControllerDelegate, GKMatchDelegate>
{
    BOOL gameCenterAvailable;
    BOOL userAuthenticated;
}

@property (assign, readonly) BOOL gameCenterAvailable;
+ (GameCenterWrapper_objc *)sharedGameCenterHelper;

- (void) authenticateLocalUser;
- (void) showLeaderboard;
- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController;

- (void) showAchievements;
- (void) achievementViewControllerDidFinish:(GKLeaderboardViewController *)viewController;

- (void) reportAchievement:(NSString *)aid;
- (void) reportScore:(int64_t)nScore;

@end
