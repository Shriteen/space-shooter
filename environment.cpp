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
	extern const int left_side=0;
	extern const int right_side=180;
	extern const int top_side=0;
	extern const int bottom_side=45;
	//map dimensions
	extern const int virtual_viewport_height = bottom_side-top_side;
	extern const int virtual_viewport_width = right_side-left_side ;
	//random engine and generators
	std::default_random_engine 			rand_engine;
	std::uniform_int_distribution 		rand_int_y(	environment::top_side,
													environment::bottom_side );
	std::uniform_real_distribution 		rand_real_speed_uniform(-2.0,2.0);
	std::normal_distribution			rand_real_speed_normal(0.0,2.0);
	
	//sets to store pointers to entities present at a point in game
	set<enemy_ship*> enemies;
	set<asteroid*> asteroids;
	set<bullet*> bullets;
	set<health_pack*> hpacks;
	//pointer to player ship
	player_ship* player;
}

