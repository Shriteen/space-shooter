#include "movable.h"

void movable::move()
{
	this->clean();
	this->x_pos+=x_speed;
	this->y_pos+=y_speed;
	this->draw();
}



/*class test:public movable
{
	public:
		test(WINDOW *win,float y,float x,float vy,float vx)
		{
			this->win=win;
			this->y_pos=y;
			this->x_pos=x;
			this->y_speed=vy;
			this->x_speed=vx;
			
			pixels[pair<int,int>{0,0}]='#';
			pixels[pair<int,int>{-1,0}]='+';
			pixels[pair<int,int>{0,-1}]='(';
			pixels[pair<int,int>{0,1}]=')';
			pixels[pair<int,int>{1,0}]='+';
			
		}
};



int main()
{
	initscr();
	
	test t(stdscr,10,35,1.5,0.5);
	
	for(int i=0;i<10;i++)
	{
		t.move();
		refresh();
		getch();		
	}
	
	
	endwin();
	
}
*/
