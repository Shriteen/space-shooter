#ifndef MOVABLE_INCLUDED
	#define MOVABLE_INCLUDED
	
#include "sprite.h"

class movable:public sprite
{
	protected:
		float x_speed;
		float y_speed;
	public:
		virtual void move();
};
	
	
#endif
