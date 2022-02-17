#ifndef ENV_INCLUDED
	#define ENV_INCLUDED

#include<set>
#include<random>
#include "ship.h"
#include "asteroid.h"
#include "bullet.h"
#include "health_pack.h"
#include "gameplay.h"

namespace environment
{
	//map borders
	extern const int left_side;
	extern const int right_side;
	extern const int top_side;
	extern const int bottom_side;
	//map dimensions
	extern const int virtual_viewport_height;
	extern const int virtual_viewport_width;
	//random engine and generators
	extern std::default_random_engine 		rand_engine;
	extern std::uniform_int_distribution 	rand_int_y;
	extern std::uniform_real_distribution 	rand_real_speed_uniform;
	extern std::normal_distribution			rand_real_speed_normal;
	
	//sets to store pointers to entities present at a point in game
	extern set<enemy_ship*> enemies;
	extern set<asteroid*> asteroids;
	extern set<bullet*> bullets;
	extern set<health_pack*> hpacks;
	//pointer to player ship
	extern player_ship* player;
	
	//maintain the id's of asteroid which collided during a tick 
	//so that it is not considered again
	extern set<int> asteroid_collisions; 
}

#endif
