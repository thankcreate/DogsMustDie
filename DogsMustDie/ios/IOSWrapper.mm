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
#import "MobClick.h"

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
    [MobClick event:label];
}



bool IOSWrapper::isLiteVersion()
{
    return VERSION == VERSION_LITE;
}

bool IOSWrapper::isProVersion()
{
    return VERSION == VERSION_PRO;
}