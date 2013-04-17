
#ifndef AboutScene_h__
#define AboutScene_h__



#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"
#include "AboutLayer.h"
class AboutScene : public cocos2d::CCScene
{
public:
	AboutScene(void);
	~AboutScene(void);

	virtual bool init();
	CREATE_FUNC(AboutScene);

	CC_SYNTHESIZE(AboutLayer*, m_pAboutLayer, AboutLayer);
};




#endif // AboutScene_h__