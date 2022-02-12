#include<map>
#include<ncurses.h>
using namespace std;

/*	Sprite class is to be used as base class
 *  for objects having physical appearance	*/
class sprite
{
	protected:
		int x_pos;									//position x-coordinate
		int y_pos;									//position y-coordinate
		map< pair<int,int> , char > pixels;			//map which represents pixels as characters as value and
													//keys are pairs of coordinates relative to position in (y,x) form
		WINDOW *win;								//window in which sprite is drawn
	public:
		virtual void draw();						//draw the sprite in the virtual window (Not visible until refresh is called)
		void clean();								//fills the position with spaces effectively erasing the sprite
		bool touches(sprite &other);				//Return true if touching other sprite
		
};

void sprite::draw()
{
	//iterate over map and print the characters by computing position of each character
	for(map< pair<int,int> , char >::iterator ptr=pixels.begin();
		ptr!=pixels.end();
		ptr++)
	{
		mvwaddch(win,
				 y_pos + ptr->first.first,
				 x_pos + ptr->first.second,
				 ptr->second );
	}	
}

void sprite::clean()
{
	//iterate over map and print space at position of each character
	for(map< pair<int,int> , char >::iterator ptr=pixels.begin();
		ptr!=pixels.end();
		ptr++)
	{
		mvwaddch(win,
				 y_pos + ptr->first.first,
				 x_pos + ptr->first.second,
				 ' ' );
	}	
}

bool sprite::touches(sprite &other)
{
	//iterate over both maps and return true if any computed positions are same
	for(map< pair<int,int> , char >::iterator itr1=this->pixels.begin();
		itr1!=this->pixels.end();
		itr1++)
	{
		for(map< pair<int,int> , char >::iterator itr2=other.pixels.begin();
			itr2!=other.pixels.end();
			itr2++)
		{
			if( (this->y_pos + itr1->first.first) == (other.y_pos + itr2->first.first) &&
			    (this->x_pos + itr1->first.second) == (other.x_pos + itr2->first.second) )
			{
				return 1;
			}
		}
	}
	return 0;
}

/*class test:public sprite
{
	public:
		test(WINDOW *win,int y,int x)
		{
			this->win=win;
			this->y_pos=y;
			this->x_pos=x;
			
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
	
	test t(stdscr,10,35);
	t.draw();
	
	test s(stdscr,11,36);
	s.draw();
	refresh();
	getch();		
	
	endwin();
	
}
*/
