#include "movable.h"
#include "environment.h"
using namespace environment;

void movable::move()
{
	//clear the sprite, change position by speed and draw at new position
	this->clean();
	this->x_pos+=x_speed;
	this->y_pos+=y_speed;
	this->draw();
}

bool movable::interact()
{
	//if going out of bounds
	if( this->y_pos < top_side-15    ||
		this->y_pos > bottom_side+15 ||
		this->x_pos < -5             || 
		this->x_pos > right_side+30)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
