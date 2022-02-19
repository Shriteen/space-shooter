#include "space_shooter.h"
#include<fstream>

space_shooter::space_shooter():
				main_menu_win(newwin(0,0,0,0)),
				pause_menu_win(newwin(LINES/2,
									  COLS*0.8,
									  LINES/4,
									  COLS*0.1) ),
				canvas(newwin(0,0,0,0)),
				game_over_dialogue(newwin(LINES*0.3,
										  COLS*0.6,
										  LINES*0.35,
										  COLS*0.2) ),
				main_menu(main_menu_win,
						  "Main Menu",
						  vector<string>{"Start Game",
										 "High Score",
										 "Help",
										 "Exit"}),
				pause_menu(pause_menu_win,
						   "Game Paused",
						   vector<string>{"Resume",
										  "Restart",
										  "Quit"}),
				game(new gameplay(canvas)) {}

space_shooter::~space_shooter()
{
	delwin(game_over_dialogue);
	delwin(pause_menu_win);
	delwin(main_menu_win);
	delete game;
	delwin(canvas);
}

void space_shooter::start()
{
	int ch;
	do
	{
		ch=main_menu.menu_IO();
		switch(ch)
		{
			case 1:
				game_main();
				break;	
			case 2:
				show_high_score();
				break;
			case 3:
				help();;
				break;
		}
	}while(ch!=4);
	
}

void space_shooter::game_main()
{
	delete game;
	game=new gameplay(canvas);
	while(1)
	{
		//cleanup
		wclear(main_menu_win);
		wrefresh(main_menu_win);
		
		game->game_loop();
		
		if(game->is_paused())											//pause menu
		{
			if(!pause_handler())			
				break;									//quit is selected
		}
		else 															//game over
		{
			game_over_handler();
			break;
		}
	}
	
}

bool space_shooter::pause_handler()
{
	int ch=pause_menu.menu_IO();
	switch(ch)
	{
		case 1:									//resume
			return 1;
		case 2:									//restart
			delete game;	
			game=new gameplay(canvas);
			return 1;
		case 3:									//quit
			return 0;
		default:								//to supress a warning
			return 1;
	}
}

void space_shooter::game_over_handler()
{
	wclear(game_over_dialogue);
	box(game_over_dialogue,0,0);
	
	int h,w;
	getmaxyx(game_over_dialogue,h,w);
	
	wattron(game_over_dialogue,A_BOLD);
	mvwprintw(game_over_dialogue,
			  (h/2)-2,
			  (w-9)/2,
			  "Game Over" );
	mvwprintw(game_over_dialogue,
			  (h/2)-1,
			  (w-9)/2,
			  "Score:%3d",game->get_score() );
	if(is_high_score())
	{
		mvwprintw(game_over_dialogue,
				  (h/2),
				  (w-14)/2,
				  "New High Score" );
	}
	wattroff(game_over_dialogue,A_BOLD);
	
	mvwprintw(game_over_dialogue,
			  h-2,
			  1,
			  "Press any key to continue..." );
	wrefresh(game_over_dialogue);
	wgetch(game_over_dialogue);
}

bool space_shooter::is_high_score()
{
	int hs=0;
	fstream file("highscore",ios::in|ios::binary);
	if(file)
	{
		file.read((char*)&hs,sizeof(hs));
		file.close();
	}
	if(game->get_score() > hs)
	{
		hs=game->get_score();
		file.open("highscore",ios::out|ios::binary);
		file.write((char*)&hs,sizeof(hs));
		file.close();
		return 1;
	}
	return 0;
}

void space_shooter::show_high_score()
{
	WINDOW *hs_dialogue=newwin(LINES*0.3,COLS*0.6,LINES*0.35,COLS*0.2);
	wclear(hs_dialogue);
	box(hs_dialogue,0,0);
	
	int h,w,hs;
	getmaxyx(hs_dialogue,h,w);
	
	fstream file("highscore",ios::in|ios::binary);
	if(file)
	{
		file.read((char*)&hs,sizeof(hs));
		mvwprintw(hs_dialogue,
				  (h/2),
				  (w-14)/2,
				  "Highscore:%3d",hs );
		file.close();
	}
	else
	{
		mvwprintw(hs_dialogue,
				  (h/2),
				  (w-20)/2,
				  "No records found..." );
	}
	
	mvwprintw(hs_dialogue,
			  h-2,
			  1,
			  "Press any key to continue..." );
	wrefresh(hs_dialogue);
	wgetch(hs_dialogue);	
}

void space_shooter::help()
{
	WINDOW *helpwin=newwin(0,0,0,0);
	wclear(helpwin);
	
	mvwprintw(helpwin,1,(COLS-4)/2,"Help");
	
	mvwprintw(helpwin,3,0,"Space Shooter is an arcade style game \
where goal is to survive for as much time as possible.\n\n");
	wprintw(helpwin,"Use up and down arrow keys to move up and down. \
Left and right arrow keys are used to change speed in left or right direction. \
Use space to shoot.\n\n");
	wprintw(helpwin,"The score increases every tick. \
Hitting asteroid or enemy ships decreases health by 50. \
Hitting bullet decreases health by 20. \
Health pickups increase health by 50. \
When a bullet hits enemy ship you get 1 ammo.\
When a bullet destroys enemy ship you get 25 bonus score. \
The health of enemies increases with your score.\n\n");
	wprintw(helpwin,"Press escape to pause game.\n");
	
	mvwprintw(helpwin,LINES-1,0,"Press any key to continue...");
	wrefresh(helpwin);
	wgetch(helpwin);
}

int main()
{
	//setup ncurses
	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_YELLOW,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_BLACK);
	curs_set(0);
	
	space_shooter object;
	object.start();
	
	curs_set(1);
	endwin();
}
