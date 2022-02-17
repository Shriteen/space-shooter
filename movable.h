#ifndef MOVABLE_INCLUDED
	#define MOVABLE_INCLUDED
	
#include "sprite.h"

/*	Movable class is to be used as base class for sprites
 *  which are changing position with time  */
class movable:public sprite
{
	protected:
		float x_speed;						//x-axis speed
		float y_speed;						//y-axis speed
	public:
		virtual void move();				//change position by speed
		bool interact();			//checks if going outside map limits,
											//returns true if survived, false if destroyed
};
	
	
#endif
