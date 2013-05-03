//
//  File.cpp
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-4-8.
//
//

#include "GameCenterWrapper.h"
#include "GameCenterWrapper_objc.h"

GameCenterWrapper* GameCenterWrapper::m_pInstance = NULL;

GameCenterWrapper* GameCenterWrapper::sharedInstance()
{
    if(!m_pInstance)
		m_pInstance = new GameCenterWrapper();
	return m_pInstance;
}

void GameCenterWrapper::authenticateLocalUser()
{
    [[GameCenterWrapper_objc sharedGameCenterHelper] authenticateLocalUser];
}

void GameCenterWrapper::showLeaderboard()
{
    [[GameCenterWrapper_objc sharedGameCenterHelper] showLeaderboard];
}

void GameCenterWrapper::showAchievements()
{
    [[GameCenterWrapper_objc sharedGameCenterHelper] showAchievements];
}

void GameCenterWrapper::reportAchievement(const std::string aid)
{
    NSString *nsID = [NSString stringWithCString:aid.c_str()
                                        encoding:[NSString defaultCStringEncoding]];
    
    [[GameCenterWrapper_objc sharedGameCenterHelper] reportAchievement:nsID];
}

void GameCenterWrapper::reportScore(int score)
{
    [[GameCenterWrapper_objc sharedGameCenterHelper] reportScore:score];
}