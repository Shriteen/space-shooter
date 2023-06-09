#ifndef GAMEPLAY_INCLUDED
	#define GAMEPLAY_INCLUDED
#include<ncurses.h>
class gameplay
{
	private:
		static const int TARGET_ASTEROID_COUNT=15;					//Ideal asteroid count to be present at any time in game
		static const int TARGET_ENEMY_COUNT=5;						//Ideal enemy ship count to be present at any time in game
		static const int LEVEL_INTERVAL=100;						//Increase level for score crossing this interval so stronger enemies are spawned
		static const int WAIT_TIME_MILLISEC=500;					//Max time to wait for input in milliseconds 
		static const int SCORE_INCREMENT=25;						//Value by which score is to be incremented when enemy is down by bullet
		enum state{paused,playing};
		
		state state_var;											//variable to store state of game as paused or not
		int score;
		WINDOW *win;												//window in which game canvas is drawn
		WINDOW *HUD;												//window in which HUD is drawn
		
		void move_env();											//Make all entities except player ship to move
		void canvas_draw();											//Draw all entities including player ship
		void HUD_draw();											//Draw HUD
		int get_level();											//Determine level based on score
		state input();												//Take input from user and process it, returns state of game
		bool interact_env();										//Make all entities interact with environment, 
																	//return 1 if player survives, 0 if game over
		void balance_env();											//spawn asteroids, enemies and health packs
	public:
		gameplay(WINDOW *win);										//spawn player ship, asteroids and enemy ships, set score to 0
		~gameplay();												//frees memory of all entities in game
		bool is_paused();											//return true if state_var is paused false otherwise
		int get_score();											//Return score
		void increment_score();										//increment score by score_increment
		void game_loop();											/* The loop in which game runs;
																	 * Returns when either paused or game over;
																	 * After returning check for state to determine pause or over  */
};

#endif
