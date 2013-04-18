#ifndef CatPlanet_h__
#define CatPlanet_h__

#include "Planet.h"

class CatPlanet : public Planet
{
public:
	CatPlanet();
	CREATE_FUNC(CatPlanet);
	bool init();
};

#endif // CatPlanet_h__

