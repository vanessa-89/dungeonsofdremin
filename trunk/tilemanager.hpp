#ifndef TILEMANAGER_HPP_INCLUDED
#define TILEMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include "graphics.hpp"
using namespace std;

namespace tiles
{

	class tile
	{
		public:

		Uint16 frames[255][16][16];
		vector<int> contents;

		bool lightenabled;
		int lightintensity;
		bool collision;
		char frame;

		unsigned int id;

		tile()
		{

		}

		void draw(SDL_Surface* sur, int x, int y)
		{
			Uint8* r;
			Uint8* g;
			Uint8* b;

			for(int x = 0; x < 16; x++)
			{
				for(int y = 0; y < 16; y++)
				{
					SDL_GetRGB(frames[frame][x][y], sur->format, r, g, g);
					pix::put_pixel16(sur, x, y, (int)*r, (int)*g, (int)*b);
				}
			}
		}

	};

	class tilemap
	{
		public:
		tile tiledat[28][21];

		tilemap()
		{

		}

		void draw(SDL_Surface* sur, int x, int y)
		{
			for(int xs = 0; xs < 28; xs++)
			{
				for(int ys = 0; ys < 21; ys++)
				{
					tiledat[x][y].draw(sur, (xs*16)+x, (ys*16)+y);
				}
			}
		}


	};

	class light
	{
		// Needs testing
		int x;
		int y;

		int radius;
		int brightness;

		void calc(tilemap &data)
		{
			for(int xs = 0; xs < radius/2; xs++)
			{
				for(int ys = 0; ys < radius/2; ys++)
				{
					if(data.tiledat[xs+x][ys+y].lightenabled == true)
					{
						data.tiledat[xs+x][ys+y].lightintensity = brightness;
					}
				}
			}
		}
	};

}

#endif
