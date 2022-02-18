#include<ncurses.h>
#include "gameplay.h"
#include "menu.h"

class space_shooter
{
	private:
		WINDOW *main_menu_win;											//main menu window
		WINDOW *pause_menu_win;											//pause menu window
		WINDOW *canvas;													//canvas for game
		WINDOW *game_over_dialogue;										//game over dialogue window
		menu main_menu;													//main menu
		menu pause_menu;												//pause menu
		gameplay *game;													//the gameplay object
		
		void game_main();												//function for an instance of game
		bool pause_handler();											//handles pause menu, returns false if quit is selected
		void game_over_handler();										//display game over dialogue
		bool is_high_score();											//checks if high score and update file
	public:
		space_shooter();
		~space_shooter();
		void start();													//function for the main menu
};
