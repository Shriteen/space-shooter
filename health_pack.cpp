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

bool health_pack::interact()
{
	if(movable::interact() == 0)										//check for map bounds
		return 0;
	
	if(this->sprite::touches(*player))
		return 0;
	
	return 1;
}

void health_pack::draw()
{
	attron(COLOR_PAIR(1));
	attron(A_BOLD);
	sprite::draw();
	attroff(A_BOLD);
	attroff(COLOR_PAIR(1));
}
