#ifndef Stage1_1Layer_h__
#define Stage1_1Layer_h__

#include "Stage1_1Layer.h"
#include "StageBaseLayer.h"

using namespace cocos2d;

class Stage1_1Layer : public StageBaseLayer
{
public:
	Stage1_1Layer();
	~Stage1_1Layer();
	CREATE_FUNC(Stage1_1Layer);

	bool init();
};

#endif // Stage1_1Layer_h__

