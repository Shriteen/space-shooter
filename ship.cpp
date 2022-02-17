#include "ship.h"
#include "environment.h"
using namespace environment;

void ship::shoot()
{
	int dir=(gun.second > 0)?1:-1;										//determine if gun position is on right or left and spawn bullet
	bullet *temp= new bullet(win,y_pos+gun.first,x_pos+gun.second,dir);
	bullets.insert(temp);
	this->clean();
	this->x_pos-=dir;													//equal and opposite reaction
}

void ship::move(action act)
{
	switch(act)
	{
		case _shoot:
			shoot();
			break;
		case _move:
			movable::move();
			break;
	}
}


player_ship::player_ship(WINDOW *win)
{
	this->win=win;
	this->y_pos=(LINES/2);
	this->x_pos=(COLS*0.1);
	this->y_speed=0;
	this->x_speed=0;
	
	pixels[pair<int,int>{0,0}]=':';
	pixels[pair<int,int>{0,1}]='=';
	pixels[pair<int,int>{0,2}]='}';
	pixels[pair<int,int>{0,3}]='>';
	pixels[pair<int,int>{0,-1}]='#';
	pixels[pair<int,int>{0,-2}]='#';
	pixels[pair<int,int>{0,-3}]=']';
	pixels[pair<int,int>{-1,0}]='\\';
	pixels[pair<int,int>{-1,-1}]='\\';
	pixels[pair<int,int>{1,0}]='/';
	pixels[pair<int,int>{1,-1}]='/';
	pixels[pair<int,int>{-1,-3}]='}';
	pixels[pair<int,int>{-1,-4}]='>';
	pixels[pair<int,int>{1,-3}]='}';
	pixels[pair<int,int>{1,-4}]='>';
	
	gun=pair<int,int>{0,4};
	
	this->health=MAX_HEALTH;
	this->ammo=INIT_AMMO;
}

void player_ship::pick_ammo()
{
	this->ammo+=PICKED_AMMO_AMOUNT;
}

int player_ship::get_health()
{
	return health;
}

int player_ship::get_x_speed()
{
	return x_speed;
}

int player_ship::get_ammo_quantity()
{
	return ammo;
}

void player_ship::move(int key)
{
	switch(key)
	{
		case 32:								//if space, shoot and return
			if(this->ammo > 0)
			{
				ship::move(_shoot);
				this->ammo--;
			}
			return;
		case KEY_UP:
			this->clean();
			this->y_pos-=1;
			break;
		case KEY_DOWN:
			this->clean();
			this->y_pos+=1;
			break;
		case KEY_LEFT:
			this->x_speed-=1;
			break;
		case KEY_RIGHT:
			this->x_speed+=1;
			break;
	}
	//If not shooting we move regardless of input as momentum is maintained
	ship::move(_move);
}

bool player_ship::interact()
{
	if(movable::interact() == 0)										//check for map bounds
		return 0;
	
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			this->health-=50;
	}
	
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			this->health-=50;
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			this->health-=20;
	}
	
	for(set<health_pack*>::iterator itr=hpacks.begin();
		itr!=hpacks.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
		{
			this->health+=50;
			if(this->health > MAX_HEALTH)
				this->health=MAX_HEALTH;
		}
	}
	
	if(this->health <= 0)
		return 0;
	else
		return 1;
}


enemy_ship::enemy_ship(WINDOW *win,int level)
{
	this->win=win;
	
	//set positions and speed
	this->y_pos=rand_int_y(rand_engine);
	this->x_pos=right_side;
	
	this->y_speed=rand_real_speed_normal(rand_engine);
	this->x_speed=rand_real_speed_uniform(rand_engine);
	this->x_speed = (x_speed>0)? -x_speed : x_speed;					//making sure enemies move towards viewport
	
	pixels[pair<int,int>{0,0}]=':';
	pixels[pair<int,int>{0,-1}]='=';
	pixels[pair<int,int>{0,-2}]='{';
	pixels[pair<int,int>{0,-3}]='<';
	pixels[pair<int,int>{0,1}]='#';
	pixels[pair<int,int>{0,2}]='#';
	pixels[pair<int,int>{0,3}]='[';
	pixels[pair<int,int>{-1,0}]='/';
	pixels[pair<int,int>{-1,1}]='/';
	pixels[pair<int,int>{1,0}]='\\';
	pixels[pair<int,int>{1,1}]='\\';
	pixels[pair<int,int>{-1,3}]='{';
	pixels[pair<int,int>{-1,4}]='<';
	pixels[pair<int,int>{1,3}]='{';
	pixels[pair<int,int>{1,4}]='<';
	
	gun=pair<int,int>{0,-4};
	
	this->health = BASE_MAX_HEALTH + (HEALTH_INCREMENT_PER_LEVEL*level);	//taking into account current level
}

void enemy_ship::move()
{
	static std::uniform_int_distribution 	rand_action(0,5);			//Pick a random action with 0.167 probability for each action
	int act=rand_action(rand_engine);
	int direction;
	switch(act)
	{
		case 0:										//shoot
			ship::move(_shoot);
			break;
		case 1:										//change direction
			direction=rand_action(rand_engine);
			switch(direction)
			{
				case 0:						//up
					this->y_speed--;
					break;
				case 1:						//down
					this->y_speed++;				
					break;
				case 2:						//left, 0.5 probability
				case 3:
				case 4:								
					this->x_speed--;
					break;
				case 5:						//right
					this->x_speed++;
					break;
			}
			//no break as we still want to move even after direction change
		case 2:										//do-nothing, i.e. maintain momentum; 0.66 probability
		case 3:
		case 4:
		case 5:
			ship::move(_move);
			break;
	}
}

bool enemy_ship::interact()
{
	if(movable::interact() == 0)										//check for map bounds
		return 0;
	
	if(this->sprite::touches(*player))
		this->health-=50;
	
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
			this->health-=50;
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end();
		itr++)
	{
		if(this->sprite::touches(**itr))
		{
			this->health-=20;
			if(this->health <= 0)
				player->pick_ammo();
		}
	}
	
	if(this->health <= 0)
		return 0;
	else
		return 1;
}
