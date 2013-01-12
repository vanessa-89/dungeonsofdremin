#ifndef TILEMANAGER_HPP_INCLUDED
#define TILEMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include "graphics.hpp"
#include "items.hpp"
using namespace std;

namespace tiles
{

    struct pixeldat
    {
        int r;
		int g;
		int b;
		bool alpha;

        pixeldat()
        {
			alpha = false;
			//r = 0;
			//g = 0;
			//b = 0;
        }
		
		pixeldat(int ar, int ag, int ab, bool aalpha)
        {
			alpha = aalpha;
			r = ar;
			g = ag;
			b = ab;
        }
		
		void draw(SDL_Surface* sur, int x, int y)
		{
			pix::put_pixel16(sur, x, y, r, g, b );
		}

    };
	
	
	struct tiledat
	{
		pixeldat data[16][16];
		int x;
		int y;
		
		
		void clear()
		{
			for(int xx = 0; xx < 16; xx++)
			{
				for(int yy = 0; yy < 16; yy++)
				{
					data[xx][yy].alpha = false;
					data[xx][yy].r = 0;
					data[xx][yy].g = 0;
					data[xx][yy].b = 0;
				}
			
			}
		}
		
		tiledat()
		{
			//clear();
		}
		
		void draw(SDL_Surface* sur)
		{
			for(int xx = 0; xx < 16; xx++)
			{
				for(int yy = 0; yy < 16; yy++)
				{
					data[xx][yy].draw(sur, xx+x,yy+y); // Draw with offsets
				}
			}
		}
		
	
	};
		
		
	struct tilemap
	{
		vector<tiledat> tiledata;
		int xsize;
		int ysize;
		int xoff;
		int yoff;
		
		tilemap(int axsize, int aysize, int axoff, int ayoff)
		{
			ysize = axsize;
			xsize = aysize;
			xoff = axoff;
			yoff = ayoff;
			tiledata.resize(xsize*ysize);
			clear();
		}
		
		void clear()
		{
			for(int xx = 0; xx < xsize; xx++)
			{
				for(int yy = 0; yy < ysize; yy++)
				{
					tiledata[xsize * xx + yy].clear();
					tiledata[xsize * xx + yy].x = xx*16+xoff;
					tiledata[xsize * xx + yy].y = yy*16+yoff;
				}
			}
		}
		
		void writeTile(tiledat* tile, int xpos, int ypos)
		{
			for(int tx = 0; tx < 16; tx++)
			{
				for(int ty = 0; ty < 16; ty++)
				{
					tiledata[xsize * xpos + ypos].data[tx][ty].r = tile->data[tx][ty].r;
					tiledata[xsize * xpos + ypos].data[tx][ty].g = tile->data[tx][ty].g;
					tiledata[xsize * xpos + ypos].data[tx][ty].b = tile->data[tx][ty].b;
				}
			}
		}
		
		void draw(SDL_Surface* sur)
		{
			for(int xx = 0; xx < xsize; xx++)
			{
				for(int yy = 0; yy < ysize; yy++)
				{
					tiledata[xsize * xx + yy].draw(sur);
				}
			}
		
		}
		
	
	};
	
	struct pointLight
	{
		int x;
		int y;
		int radius;
		int brightness;
		
		pointLight()
		{
			radius = 0;
			brightness = 0;
			x = 0;
			y = 0;
		}
		
		void calculateCircle()
		{
			
		
		}
	
	};
	
	
	
}

#endif
