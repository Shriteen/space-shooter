#include "asteroid.h"
#include "environment.h"
using namespace environment;

int asteroid::rand_real_size( std::default_random_engine& rand_engine )
{
	static const double ASTEROID_MAX_RADIUS_ROOT=1.3;											//std deviation of asteroid size
	static std::normal_distribution<double> __random(0.0,double(ASTEROID_MAX_RADIUS_ROOT));		//generate a random size and return it
	return int(__random(rand_engine));
}

void asteroid::random_shape()
{
	//Add sample points to map
	for(int i=0;i<SAMPLE_POINTS;i++)
	{
		pixels[pair<int,int>{ rand_real_size(rand_engine),
							  rand_real_size(rand_engine)  } ]='#';
	}
	//Initialising both start and end as map would be updated during loop
	map< pair<int,int> , char >::iterator start=pixels.begin();
	map< pair<int,int> , char >::iterator end=pixels.end();
	for(;
		start!=end;
		start++ )
	{
		for(map< pair<int,int> , char >::iterator temp=start;
			temp!=end;
			temp++)
		{
			line(start,temp);											//draw line from each point to all points
		}
	}
	
}

void asteroid::line( map< pair<int,int> , char >::iterator p1,
					 map< pair<int,int> , char >::iterator p2 )
{
	if(int(p2->first.second) == int(p1->first.second))					//If the points have same x-coordinate i.e. need to draw vertical line
	{
		//Select lower and upper point and map pixels between them
		int i=( p2->first.first < p1->first.first )? p2->first.first : p1->first.first;
		int j=( p2->first.first > p1->first.first )? p2->first.first : p1->first.first;
		for(;i<=j;i++)
		{
			pixels[pair<int,int>{ i, p2->first.second }]='#';
		}
	}
	else 																//for points having different x-coordinate
	{	
		//Determine slope of line between points
		float slope= float(p2->first.first - p1->first.first) / 
					 float(p2->first.second - p1->first.second);
		//Set an interval for plotting y for each interval of x
		//Direction will be dependant on whether the first point is on left or right of other
		float interval=( p2->first.second > p1->first.second )? 0.5 : -0.5;
		//move from first point to other point
		for(float x=p1->first.second; int(x)!=p2->first.second; x+=interval)
		{
			float y= (slope*x)+p1->first.first;							//using y=mx+c formula with y-coordinate of first point acting as c
			pixels[pair<int,int>{ y,x }]='#';
		}
	}	
}

void asteroid::set_rand_pos_speed()
{	
	//static variables are used as having new object every time may result in same value being returned each time
	static std::uniform_int_distribution rand_region(0,2);				//select between 3 regions
	int region=rand_region(rand_engine);
	
	//set random speeds
	this->y_speed=rand_real_speed_uniform(rand_engine);
	this->x_speed=rand_real_speed_uniform(rand_engine);
	
	static std::uniform_int_distribution rand_spawn_position;			//selects random value in range for random spawn point along an axis
	
	switch(region)
	{
		case 0:													//top
			rand_spawn_position= std::uniform_int_distribution(100,right_side);
			this->x_pos=rand_spawn_position(rand_engine);
			this->y_pos=top_side-10;									//spawn above viewport
			
			this->y_speed = (y_speed<0)? -y_speed : y_speed;			//making sure to send it towards viewport
			break;
		case 1:													//side
			this->y_pos=rand_int_y(rand_engine);
			this->x_pos=right_side+20;									//spawn right of viewport
			
			this->x_speed = (x_speed>0)? -x_speed : x_speed;			//making sure to send it towards viewport
			break;
		case 2:													//bottom
			rand_spawn_position= std::uniform_int_distribution(100,right_side);
			this->x_pos=rand_spawn_position(rand_engine);				//spawn below viewport
			this->y_pos=bottom_side+10;
			
			this->y_speed = (y_speed>0)? -y_speed : y_speed;			//making sure to send it towards viewport
			break;
	}
	
	
	//if they spawn touching change position
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++ )
	{
		if((this->id != (*itr)->id) &&
			this->touches(**itr) )
		{
			set_rand_pos_speed();
		}
	}
}

asteroid::asteroid(WINDOW *win)
{
	this->win=win;
	this->id=asteroid_number;
	asteroid_number++;
	random_shape();
	set_rand_pos_speed();
}

bool asteroid::interact()
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
	
	//if the asteroid is not present in the set, then end iterator is returned
	//execute only if not present
	if(asteroid_collisions.find(this->id) == asteroid_collisions.end())				
	{
		//check with all asteroids
		for(set<asteroid*>::iterator itr=asteroids.begin();
			itr!=asteroids.end();
			itr++ )
		{
			//ignore if iterator is pointing to the same asteroid
			if((this->id != (*itr)->id) &&
				this->touches(**itr) )
			{
				//swap the x_speed and y_speed
				float temp = (*itr)->x_speed;
				(*itr)->x_speed = this->x_speed;
				this->x_speed = temp;
				
				temp = (*itr)->y_speed;
				(*itr)->y_speed = this->y_speed;
				this->y_speed = temp;
				
				//insert other asteroid id in the set
				asteroid_collisions.insert((*itr)->id);
			}
		}
	}
	return 1;
}

void asteroid::draw()
{
	attron(A_REVERSE);
	sprite::draw();
	attroff(A_REVERSE);
}
