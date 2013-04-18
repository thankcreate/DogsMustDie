#ifndef DogPlanet_h__
#define DogPlanet_h__

#include "Planet.h"

class DogPlanet : public Planet
{
public:
	DogPlanet();
	CREATE_FUNC(DogPlanet);
	bool init();
};

#endif // DogPlanet_h__

