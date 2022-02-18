#include "menu.h"

menu::menu(WINDOW *win,string title,vector<string> options)
{
	this->win=win;
	this->title=title;
	this->options=options;
}

int menu::menu_IO()
{
	noecho();												//do not echo pressed keystrokes on screen
	keypad(win,TRUE);										//turn on keypad usage
	wclear(win);
	
	int y,x;
	getmaxyx(win,y,x);										//get window height and width
	mvwprintw(win,											//centered title
			  2,
			  (x-title.length())/2,
			  "%s",title.c_str() );
	
	int selected=0;											//variable to keep tract of selection,
															//by default first option is selected
	
	for(int i=0;i<options.size();i++)						//display options centered
	{
		mvwprintw(win,
				  4+i,
				  (x-options[i].length())/2,
				  "%s",options[i].c_str());
	}
	
	mvwchgat(win,4+selected,0,-1,A_REVERSE,0,NULL);			//highlight default selection
	box(win,0,0);
	wrefresh(win);
	
	while(1)												//repeat until an option is not selected using enter
	{
		int ch=wgetch(win);									//input keystroke
		mvwchgat(win,4+selected,0,-1,A_NORMAL,0,NULL);		//unhighlight the selected entry 
		switch(ch)
		{
			case KEY_UP:							//for up; if on first option, then wrap to last option, select upper option otherwise
				if(selected==0)
					selected=options.size()-1;
				else
					selected--;
				break;
			case KEY_DOWN:							//for down; if on last option, then wrap to first option, select lower option otherwise
				if(selected==options.size()-1)
					selected=0;
				else
					selected++;
				break;
			case 10:
				echo();								//if enter pressed; turn back echo on and return selected
				wclear(win);
				return selected+1;
		}
		mvwchgat(win,4+selected,0,-1,A_REVERSE,0,NULL);		//highlight selected option
		box(win,0,0);
		wrefresh(win);
	}
}
