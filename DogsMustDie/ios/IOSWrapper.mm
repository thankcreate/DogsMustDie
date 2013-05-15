//
//  IOSWrapper.cpp
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-29.
//
//

#include "IOSWrapper.h"
#import <Foundation/Foundation.h>
#import "IOSWrapper_objc.h"


IOSWrapper* IOSWrapper::m_pInstance = NULL;

IOSWrapper* IOSWrapper::sharedInstance()
{
    if(!m_pInstance)
		m_pInstance = new IOSWrapper();
	return m_pInstance;
}

void IOSWrapper::rateUs()
{
    [[IOSWrapper_objc sharedInstance] gotoRateView];
}

void IOSWrapper::showRateUSDialog()
{
    [[IOSWrapper_objc sharedInstance] showRateusDialog];
}


// 上报友盟统计
void IOSWrapper::recordLevel(int big, int small)
{
    NSString* label = [NSString stringWithFormat:@"level:%d-%d", big, small];
}

void IOSWrapper::showAd()
{
    [[IOSWrapper_objc sharedInstance] showAd];
}

void IOSWrapper::hideAd()
{
    [[IOSWrapper_objc sharedInstance] hideAd];
}

bool IOSWrapper::isLiteVersion()
{
    return VERSION == VERSION_LITE;
}

bool IOSWrapper::isProVersion()
{
    return VERSION == VERSION_PRO;
}

bool IOSWrapper::isEndlessModeTest()
{
    NSString* strKey = [[NSString alloc] initWithString:@"Endless_Mode_Test"];
    NSString* strTest = [[IOSWrapper_objc sharedInstance] getUmengParam:strKey];
    
    if(strTest == nil || [strTest compare:@"1"] != NSOrderedSame)
    {
        return false;
    }
    else
    {
        return true;
    }
}