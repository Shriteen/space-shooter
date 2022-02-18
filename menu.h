#ifndef MENU_INCLUDED
	#define MENU_INCLUDED
	
#include<ncurses.h>
#include<vector>
#include<string>
using namespace std;
class menu
{
	private:
		WINDOW *win;													//window in which menu is displayed
		string title;													//title of menu
		vector<string> options;											//vector containing option strings
	public:
		menu(WINDOW *win,string title,vector<string> options);
		int menu_IO();													//display menu and receive user input;
																		//return option number selected, index is 1 based
};

#endif
