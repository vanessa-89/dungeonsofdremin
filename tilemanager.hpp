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
		Uint16 frames[32][16][16]; // Store frame data
		vector<int> contents; // Item ID's stored in this tile

        // Lighting flags and values
		bool lightenabled; // Can this tile be lit?

		bool collision; // Collide with this tile?

		char frame; // Current frame

		unsigned int Tid; // Tile ID

		tile()
		{
			frame = 0;
		}
		
		
		void clear()
		{
			// For each frame(f)
			for(int f = 0; f < 32; f++)
			{
				for(int sx = 0; sx < 16; sx++)
				{
					for(int sy = 0; sy < 16; sy++)
					{
						// Clear each xy combonation
						frames[f][sx][sy] = 0;
					}
				}
			
			}
		}

		void draw(SDL_Surface* sur, int xpos, int ypos)
		{
			// vars
			// x - x offset
			// y - y offset
			// sx - surface x pos
			// sy - surface y pos

			// Color storage
			Uint8 r = 0;
			Uint8 g = 0;
			Uint8 b = 0;

			for(int sx = 0; sx < 16; sx++)
			{
				for(int sy = 0; sy < 16; sy++)
				{
					// Get the RGB color from a pixel in the frame data
					SDL_GetRGB(frames[frame][sx][sy], sur->format, &r, &g, &b);
                    // Output the data with offsets (x and y)
					pix::put_pixel16(sur, sx+xpos, sy+ypos, r, g, b);
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


	};

}

#endif
