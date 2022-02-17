#include "bullet.h"
#include "environment.h"
using namespace environment;

bullet::bullet(WINDOW *win,float y_pos,float x_pos,int dir)
{
	this->win=win;
	this->y_pos=y_pos;
	this->x_pos=x_pos;
	
	pixels[pair<int,int>{0,0}]='=';
	
	this->y_speed=0;
	if(dir<0)															//set correct direction
		this->x_speed=-BULLET_SPEED;
	else
		this->x_speed=BULLET_SPEED;
}

bool bullet::interact()
{
	if(movable::interact() == 0)										//check for map bounds
		return 0;
	
	if(this->sprite::touches(*player))
		return 0;
		
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			return 0;
	}
	
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			return 0;
	}
	
	return 1;
}
