#ifndef BULLET_INCLUDED
	#define BULLET_INCLUDED

#include "movable.h"

class bullet:public movable
{
	private:
		static const int BULLET_SPEED=3;								//magnitude of speed of bullet
	public:
		bullet(WINDOW *win,float y_pos,float x_pos,int dir);			//negative value of dir is left, right otherwise
		//bool interact();
};
	
#endif