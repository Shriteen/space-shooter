#ifndef SPRITE_INCLUDED
	#define SPRITE_INCLUDED

#include<map>
#include<ncurses.h>
using namespace std;

/*	Sprite class is to be used as base class
 *  for objects having physical appearance	*/
class sprite
{
	protected:
		float x_pos;								//position x-coordinate
		float y_pos;								//position y-coordinate
		map< pair<int,int> , char > pixels;			//map which represents pixels as characters as value and
													//keys are pairs of coordinates relative to position in (y,x) form
		WINDOW *win;								//window in which sprite is drawn
	public:
		virtual void draw();						//draw the sprite in the virtual window (Not visible until refresh is called)
		void clean();								//fills the position with spaces effectively erasing the sprite
		bool touches(sprite &other);				//Return true if touching other sprite
		
};

#endif
