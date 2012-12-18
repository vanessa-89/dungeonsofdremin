#ifndef TILEMANAGER_HPP_INCLUDED
#define TILEMANAGER_HPP_INCLUDED

#include <vector>
#include <string>
#include "graphics.hpp"
#include "items.hpp"
using namespace std;

namespace tiles
{

	class tile
	{
		public:
		SDL_Color dat[16][16]; // Store color data
		vector<int> contents; // Item ID's stored in this tile

        // Lighting flags and values
		bool lightenabled; // Can this tile be lit?

		bool collision; // Collide with this tile?

		tile()
		{

		}
		
		
		void clear()
		{
			for(int sx = 0; sx < 16; sx++)
			{
				for(int sy = 0; sy < 16; sy++)
				{
					// Clear each xy combonation
					dat[sx][sy].r = 0;
					dat[sx][sy].g = 0;
					dat[sx][sy].b = 0;
					
				}
			}
	
		}

		void draw(SDL_Surface* sur, int xpos, int ypos)
		{

			for(int sx = 0; sx < 16; sx++)
			{
				for(int sy = 0; sy < 16; sy++)
				{
                    // Output the data with offsets (x and y)
					//cout << "da" << endl;
					//cout << dat[sx][sy].r << endl;
					pix::put_pixel16(sur, sx+xpos, sy+ypos, dat[sx][sy].r, dat[sx][sy].g, dat[sx][sy].b);
				}
			}
		}

	};

	class tilemap
	{
		public:
		tile* tiledat[28][21];

		tilemap()
		{

		}
		
		void draw(SDL_Surface* sur, int x, int y)
		{
			// For every tile in tiledat, call its draw function with the proper offsets
			for(int sx = 0; sx < 28; sx++)
			{
				for(int sy = 0; sy < 21; sy++)
				{
					tiledat[x][y]->draw(sur, (sx*16)+x, (sy*16)+y);
				}
			}
		}
		
		void clear()
		{
			for(int x = 0; x < 28; x++)
			{
				for(int y = 0; y < 21; x++)
				{
					tiledat[x][y]->clear();
				}
			
			}
		}

	};

}

#endif
