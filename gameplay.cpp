#include "gameplay.h"
#include "environment.h"
using namespace environment;

gameplay::gameplay(WINDOW *win)
{
	//set canvas window
	this->win=win;
	canvas=this->win;
	
	//set HUD window
	this->HUD=newwin(3,COLS,0,0);
	
	this->score=0;
	
	//spawn player ship
	player=new player_ship();
	
	//spawn asteroids and add to set
	for(int i=0; i<TARGET_ASTEROID_COUNT; i++)
	{
		asteroid *temp= new asteroid();
		asteroids.insert(temp);
	}
	
	//spawn enemy ships and add to set
	for(int i=0; i<TARGET_ENEMY_COUNT; i++)
	{
		enemy_ship *temp= new enemy_ship(this->get_level());
		enemies.insert(temp);
	}
}

gameplay::~gameplay()
{
	delete player;		
	
	/* co iterators are used as removing from set using an iterator 
	 * invalidates all iterators to the deleted element 
	 * so that we cannot increment it to point to next element 	*/
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end(); )
	{
		set<asteroid*>::iterator co_itr=itr;
		itr++;
		delete *co_itr;
		asteroids.erase(co_itr);
	}
	
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end();  )
	{
		set<enemy_ship*>::iterator co_itr=itr;
		itr++;
		delete *co_itr;
		enemies.erase(co_itr);
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end();  )
	{
		set<bullet*>::iterator co_itr=itr;
		itr++;
		delete *co_itr;
		bullets.erase(co_itr);
	}
	
	for(set<health_pack*>::iterator itr=hpacks.begin();
		itr!=hpacks.end();  )
	{
		set<health_pack*>::iterator co_itr=itr;
		itr++;
		delete *co_itr;
		hpacks.erase(co_itr);
	}
	
	delwin(this->HUD);
}

void gameplay::canvas_draw()
{
	player->draw();
	
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++)
	{
		(*itr)->draw();
	}
	
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end();
		itr++)
	{
		(*itr)->draw();
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end();
		itr++)
	{
		(*itr)->draw();
	}
	
	for(set<health_pack*>::iterator itr=hpacks.begin();
		itr!=hpacks.end();
		itr++)
	{
		(*itr)->draw();
	}
	
	wrefresh(this->win);
}

void gameplay::HUD_draw()
{
	wclear(this->HUD);
	box(this->HUD,0,0);
	//draw health,ammo,speed and score
	wattron(this->HUD,A_BOLD);
	mvwprintw(this->HUD,1,1,"Health:%d",player->get_health());
	mvwprintw(this->HUD,1,int(COLS*0.5),"Ammo:%d",player->get_ammo_quantity());
	mvwprintw(this->HUD,1,int(COLS*0.25),"Speed:%d",player->get_x_speed());
	mvwprintw(this->HUD,1,int(COLS*0.75),"Score:%d",this->score);
	wattroff(this->HUD,A_BOLD);
	wrefresh(this->HUD);
}

int gameplay::get_level()
{
	return (score%LEVEL_INTERVAL);
}

void gameplay::move_env()
{
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end();
		itr++)
	{
		(*itr)->move();
	}
	
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end();
		itr++)
	{
		(*itr)->move();
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end();
		itr++)
	{
		(*itr)->move();
	}
	
	for(set<health_pack*>::iterator itr=hpacks.begin();
		itr!=hpacks.end();
		itr++)
	{
		(*itr)->move();
	}
}

bool gameplay::is_paused()
{
	if(state_var==paused)
		return 1;
	else
		return 0;
}

gameplay::state gameplay::input()
{
	wtimeout(this->win,WAIT_TIME_MILLISEC);								//set input mode as timeout
	int ip=wgetch(this->win);											//input if available
	switch(ip)
	{
		case 27:														//escape key pressed
			this->state_var=paused;
			break;
		default:														//pass keystroke to player ship's move function
			player->move(ip);
			this->state_var=playing;
			break;
	}
	wtimeout(this->win,-1);												//restore input mode
	return state_var;
}

bool gameplay::interact_env()
{
	if(!player->interact())									//if game over
	{
		delete player;
		player=NULL;										//set to NULL so that delete in gameplay destructor does not try to 
															//free the dangling pointer 
		return 0;
	}
	
	//If entities are destroyed delete and remove them
	for(set<enemy_ship*>::iterator itr=enemies.begin();
		itr!=enemies.end(); )
	{
		set<enemy_ship*>::iterator co_itr=itr;
		itr++;
		if(!(*co_itr)->interact())
		{
			delete *co_itr;
			enemies.erase(co_itr);
		}
	}
	
	asteroid_collisions.clear();										//flush collisions set
	for(set<asteroid*>::iterator itr=asteroids.begin();
		itr!=asteroids.end(); )
	{
		set<asteroid*>::iterator co_itr=itr;
		itr++;
		if(!(*co_itr)->interact())
		{
			delete *co_itr;
			asteroids.erase(co_itr);
		}
	}
	
	for(set<bullet*>::iterator itr=bullets.begin();
		itr!=bullets.end(); )
	{
		set<bullet*>::iterator co_itr=itr;
		itr++;
		if(!(*co_itr)->interact())
		{
			delete *co_itr;
			bullets.erase(co_itr);
		}
	}
	
	for(set<health_pack*>::iterator itr=hpacks.begin();
		itr!=hpacks.end(); )
	{
		set<health_pack*>::iterator co_itr=itr;
		itr++;
		if(!(*co_itr)->interact())
		{
			delete *co_itr;
			hpacks.erase(co_itr);
		}
	}
	
	return 1;
}

void gameplay::balance_env()
{
	if(asteroids.size() < TARGET_ASTEROID_COUNT)
	{
		for(int i=asteroids.size();
			i<TARGET_ASTEROID_COUNT;
			i++ )
		{
			asteroid *temp= new asteroid();
			asteroids.insert(temp);
		}
	}
	
	if(enemies.size() < TARGET_ENEMY_COUNT)
	{
		for(int i=enemies.size();
			i<TARGET_ENEMY_COUNT;
			i++ )
		{
			enemy_ship *temp= new enemy_ship(this->get_level());
			enemies.insert(temp);
		}
	}
	
	static std::uniform_int_distribution five_percent(0,19);			//0.05 probability for each outcome
	int chance=five_percent(rand_engine);
	if(chance == 10)													//0.05 percent probability of truth
	{
		health_pack *temp= new health_pack();
		hpacks.insert(temp);
	}
}

void gameplay::game_loop()
{
	state_var=playing;													//Set state to playing
	while(input()==playing)												//Take input of player, if paused, stop looping and return
	{
		this->score++;														//Increment score every tick
		move_env();														//Make all entities move
		if(interact_env()==0)											//Make all entities interact,
			return;														//If player did not survive, i.e. game over, then return
		balance_env();													//Spawn entities if required
		canvas_draw();													//Draw all game elements
		HUD_draw();														//Draw HUD
	}	
}

int gameplay::get_score()
{
	return score;
}

/*
int main()
{
	initscr();
	noecho();
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_BLACK);
	keypad(stdscr,TRUE);
	gameplay g(stdscr);
	g.game_loop();
	endwin();
}
*/

