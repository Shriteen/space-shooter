#ifndef HP_INCLUDED
	#define HP_INCLUDED

#include "movable.h"

class health_pack:public movable
{
	public:
		health_pack(WINDOW *win);
		//bool interact();
};

#endif
