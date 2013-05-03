//
//  File.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-4-8.
//
//

#ifndef __StrangeAdventure__File__
#define __StrangeAdventure__File__

#include <iostream>
class GameCenterWrapper
{
public:
    static GameCenterWrapper* sharedInstance();
    void authenticateLocalUser();
    void showLeaderboard();
    void showAchievements();
    
    void reportAchievement(const std::string aid);
    void reportScore(int score);
    
private:
    static GameCenterWrapper* m_pInstance;
    
    
};
#endif /* defined(__StrangeAdventure__File__) */
