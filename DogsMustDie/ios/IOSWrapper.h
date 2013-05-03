//
//  IOSWrapper.h
//  StrangeAdventure
//
//  Created by Tron Skywalker on 13-3-29.
//
//

#ifndef __StrangeAdventure__IOSWrapper__
#define __StrangeAdventure__IOSWrapper__

class IOSWrapper
{
public:
    static IOSWrapper* sharedInstance();
    void rateUs();
    void showRateUSDialog();
    void recordLevel(int big, int small);
    
    static bool isLiteVersion();
    static bool isProVersion();
    
private:
    static IOSWrapper* m_pInstance;
    
};

#endif /* defined(__StrangeAdventure__IOSWrapper__) */
