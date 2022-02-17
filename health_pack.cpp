#include "health_pack.h"
#include "environment.h"
using namespace environment;

health_pack::health_pack()
{
	this->win=canvas;
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
	wattron(this->win,COLOR_PAIR(1));
	wattron(this->win,A_BOLD);
	sprite::draw();
	wattroff(this->win,A_BOLD);
	wattroff(this->win,COLOR_PAIR(1));
}
