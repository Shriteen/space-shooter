#ifndef SHIP_INCLUDED
	#define SHIP_INCLUDED

#include "movable.h"

class ship:public movable
{
	protected:
		enum action{_shoot,_move};
		
		int health;
		pair<int,int> gun;												//position of gun relative to ship position
	public:
		virtual void move(action act);									//accepts action _shoot or _move and perform the action
		void shoot();

};

class player_ship:public ship
{
	private:
		static const int MAX_HEALTH=100;								//max health of player
		static const int INIT_AMMO=15;									//initial ammunition count
		static const int PICKED_AMMO_AMOUNT=5;							//amount by which to increase ammunition when enemy is shot
		
		int ammo;														//amount of ammunition available
	public:
		player_ship(WINDOW *win);
		void pick_ammo();												//increases ammunition by PICKED_AMMO_AMOUNT
		int get_health();												//returns value of health
		int get_x_speed();												//returns value of x_speed
		int get_ammo_quantity();										//returns value of ammo
		void move(int key);												//accepts key strokes and perform move by player
		bool interact();												//Interact with all other entities, 
																		//returns true if survived, false if destroyed
		void draw();													//set player ship color to green
};


class enemy_ship:public ship
{
	private:
		static const int BASE_MAX_HEALTH=50;							//The health with which the enemy ships spawn initially
		static const int HEALTH_INCREMENT_PER_LEVEL=10;					//for each increase in level,
																		//initial health of enemies increases by this amount
	public:
		enemy_ship(WINDOW *win,int level);								//accepts current level for determining health of new enemy ships
		void move();													//perform random move by enemies
		bool interact();												//Interact with all other entities, 
																		//returns true if survived, false if destroyed
		void draw();													//set player ship color to red
};

#endif
