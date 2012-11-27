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
		Uint16 frames[255][16][16]; // Store frame data
		vector<int> contents; // Item ID's stored in this tile

        // Lighting flags and values
		bool lightenabled;
		int lightintensity;

		bool collision; // Collide with this tile?

		char frame; // Current frame

		unsigned int Tid; // Tile ID

		tile()
		{

		}

		void draw(SDL_Surface* sur, int x, int y)
		{
			// vars
			// x - x offset
			// y - y offset
			// sx - surface x pos
			// sy - surface y pos

			// Color storage
			Uint8* r;
			Uint8* g;
			Uint8* b;

			for(int x = 0; sx < 16; sx++)
			{
				for(int y = 0; sy < 16; sy++)
				{
					// Get the RGB color from a pixel in the frame data
					SDL_GetRGB(frames[frame][sx][sy], sur->format, r, g, b);
                    // Output the data with offsets (x and y)
					pix::put_pixel16(sur, sx+x, sy+y, (int)*r, (int)*g, (int)*b);
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
