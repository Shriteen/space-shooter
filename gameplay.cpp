#include "gameplay.h"
#include "environment.h"
using namespace environment;

#include<iostream>

gameplay::gameplay()
{
	//-------------
	this->win=stdscr;
	
	this->score=0;
	//spawn player ship
	player=new player_ship(this->win);
	//spawn asteroids and add to set
	for(int i=0; i<TARGET_ASTEROID_COUNT; i++)
	{
		asteroid *temp= new asteroid(this->win);
		asteroids.insert(temp);
	}
	//spawn enemy ships and add to set
	for(int i=0; i<TARGET_ENEMY_COUNT; i++)
	{
		enemy_ship *temp= new enemy_ship(this->win,this->get_level());
		enemies.insert(temp);
	}
	
	
	
	
	
	
	/*state_var=playing;
	while(input()==playing)
	{
		
		move_env();
		
		
		canvas_draw();
		
		wrefresh(this->win);
	}	
	*/
	
	//---------------------------------temporary
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

/*int main()
{
	initscr();
	keypad(stdscr,TRUE);
	gameplay g;
	endwin();
}
*/
