#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include <string>
#include <iostream>

#include "graphics.hpp"
#include "fonts.hpp"

using namespace std;

namespace sgui
{


	
	class button
	{
		
		int x1;
		int y1;
		int x2;
		int y2;
		
		char br;
		char bg;
		char bb;
		
		char tr;
		char tg;
		char tb;
		
		ttf_font::fontwrapper* fnt;
		
		
		string text;
		int textsize;
		void (*callback)();
		
		public:
		
		button(int ax1, int ay1, int ax2, int ay2, char abr, char abg, char abb, string atext, int atextsize, char atr, char atg, char atb, void (*acallback)(), ttf_font::fontwrapper* afnt)
		{
			
				
				x1 = ax1;
				y1 = ay1;
				x2 = ax2;
				y2 = ay2;
				
				br = abr;
				bg = abg;
				bb = abb;
				
				text = atext;
				textsize = atextsize;
				callback = acallback;
				
				tr = atr;
				tg = atg;
				tb = atb;
				
				fnt = afnt;
		}
		
		void logicUpdate()
		{
			int mx;
			int my;
			SDL_GetMouseState(&mx, &my);
			
			if(x2 > mx && mx > x1) // X bounds // Check if mouse is in the box
			{
				if(y2 > my && my > y1) // Y bounds
				{
					callback();
				}
					
			}
					
		}
		
		
		void graphicsUpdate(SDL_Surface* sur)
		{
			// Draw box
			for(int x = x1; x < x2; x++)
			{
				for(int y = y1; y < y2; y++)
				{
					pix::put_pixel16(sur, x, y, br, bg, bb);
				}
			}
			// Draw text
			fnt->drawstr(sur, ((x2+x1)/2-text.size()*2), ((y2+y1)/2)-textsize/2, tr, tg, tb, text);
			
		}
		
	
	};


}


#endif