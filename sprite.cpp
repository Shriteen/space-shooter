#include "sprite.h"

void sprite::draw()
{
	//iterate over map and print the characters by computing position of each character
	for(map< pair<int,int> , char >::iterator ptr=pixels.begin();
		ptr!=pixels.end();
		ptr++)
	{
		mvwaddch(win,
				 int(y_pos + ptr->first.first),
				 int(x_pos + ptr->first.second),
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

bool sprite::touches(sprite other)
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
			if( int(this->y_pos + itr1->first.first) == int(other.y_pos + itr2->first.first) &&
			    int(this->x_pos + itr1->first.second) == int(other.x_pos + itr2->first.second) )
			{
				return 1;
			}
		}
	}
	return 0;
}

sprite::~sprite()
{
	this->clean();
}

