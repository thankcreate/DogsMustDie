//
//  StartupLayer.h
//  DogsMustDie
//
//  Created by Tron Skywalker on 13-4-16.
//
//

#ifndef __DogsMustDie__StartupLayer__
#define __DogsMustDie__StartupLayer__

#include "cocos2d.h"

using namespace cocos2d;
class StartupLayer : public CCLayer
{
public:
	StartupLayer(void);
	~StartupLayer(void);
	CREATE_FUNC(StartupLayer);
    
	bool init();
    
	void startCallback(CCObject* pSender);
	void optionCallback(CCObject* pSender);
	void aboutCallback(CCObject* pSender);
    
    // 目前仅对iOS版有效，评分
    void rateusCallback(CCObject* pSender);
    
	// 目前仅对安卓有效，后退时退出
	void keyBackClicked();
};


#endif /* defined(__DogsMustDie__StartupLayer__) */
