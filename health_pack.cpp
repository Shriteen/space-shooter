#include "health_pack.h"
#include "environment.h"
using namespace environment;

health_pack::health_pack(WINDOW *win)
{
	this->win=win;
	this->y_pos=rand_int_y(rand_engine);
	this->x_pos=right_side;
	
	pixels[pair<int,int>{0,0}]='+';
	pixels[pair<int,int>{0,-1}]='[';
	pixels[pair<int,int>{0,1}]=']';
	
	this->y_speed=0;
	this->x_speed=-1.2;
}
