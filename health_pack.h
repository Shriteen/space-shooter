#ifndef HP_INCLUDED
	#define HP_INCLUDED

#include "movable.h"

class health_pack:public movable
{
	public:
		health_pack();
		bool interact();												//Interact with all other entities, 
																		//returns true if survived, false if destroyed
		void draw();													//set powerup color to green
};

#endif
