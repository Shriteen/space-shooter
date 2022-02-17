#ifndef BULLET_INCLUDED
	#define BULLET_INCLUDED

#include "movable.h"

class bullet:public movable
{
	private:
		static const int BULLET_SPEED=3;								//magnitude of speed of bullet
	public:
		bullet(float y_pos,float x_pos,int dir);						//negative value of dir is left, right otherwise
		bool interact();												//Interact with all other entities, 
																		//returns true if survived, false if destroyed
		void draw();													//set bullet color to yellow
};
	
#endif
