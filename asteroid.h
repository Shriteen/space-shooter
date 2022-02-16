#ifndef ASTEROID_INCLUDED
	#define ASTEROID_INCLUDED
	
#include "movable.h"
#include<random>

class asteroid:public movable
{
	private:
		static const int SAMPLE_POINTS=5;								//Number of points to sample to randomly generate asteroid pixels
		inline static int asteroid_number=0;							//Maintains count of asteroids spawned to use as ID nimber of asteroid
		
		int id;															//ID number of asteroid to uniquely identify the asteroid 
		
		int rand_real_size( std::default_random_engine& rand_engine );	//Returns a size value of asteroid to select values for sample points
		void random_shape();											//Generates a random shape as asteroid pixels
		void line(map< pair<int,int> , char >::iterator p1,				//Form a line between two sample points from the pixel map
				  map< pair<int,int> , char >::iterator p2);			
		void set_rand_pos_speed();										//Set initial random position and speed/direction
	public:
		asteroid(WINDOW *win);
		
		//bool interact();
};

#endif
