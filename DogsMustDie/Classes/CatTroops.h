#ifndef CatTroops_h__
#define CatTroops_h__

#include "Troops.h"

class CatTroops : public Troops
{
public:
	CatTroops();
	CREATE_FUNC(CatTroops);
		
	bool init();
};

#endif // CatTroops_h__

