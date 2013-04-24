#ifndef MiddlePlanet_h__
#define MiddlePlanet_h__

#include "Planet.h"

class MiddlePlanet : public Planet
{
public:
	MiddlePlanet();
	CREATE_FUNC(MiddlePlanet);
	bool init();
};

#endif // MiddlePlanet_h__

