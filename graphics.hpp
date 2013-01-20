#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED
#include "../../include/sdl/sdl.h"
#include "../../include/sdl/begin_code.h"
#include "../../include/sdl/close_code.h"
#include "../../include/sdl-ttf/sdl_ttf.h"

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Graphics.hpp - Luke Connor 11/8/12
// Graphics functions for sdl games with pixel manipulation.

namespace pix
{
		
		struct point
		{
			int x,y;
		};
		
		
		
		Uint16 get_pixel16( SDL_Surface *surface, int x, int y )
        {
            //Convert the pixels to 16 bit
            Uint16 *pixels = (Uint16 *)surface->pixels;

            //Get the requested pixel
            return pixels[ ( y * surface->w ) + x ];
        }

        void put_pixel16(SDL_Surface *surface, int x, int y, int r, int g, int b )
        {
            //Convert the pixels to 16 bit
            Uint16 *pixels = (Uint16 *)surface->pixels;

            //Set the pixel
            pixels[ ( y * surface->w ) + x ] = SDL_MapRGB(surface->format, r, g, b);
        }
		
        class window
        {
            public:
            SDL_Surface* screen;
            int xres;
            int yres;
            int depth;

            window()
            {

            }

            ~window()
            {

            }

            bool open(int x, int y, int dep, bool fullsreen)
            {
                xres = x;
                yres = y;
                depth = dep;


                if(fullsreen)
                {
                    screen = SDL_SetVideoMode( xres, yres, depth, SDL_HWSURFACE);
                }
                else
                {
                    screen = SDL_SetVideoMode( xres, yres, depth, SDL_HWSURFACE | SDL_FULLSCREEN);
                }

                if(!screen) return 1;
				
				SDL_WM_SetCaption("Dev Build", "Dev Build");
				
                return 0;

            }

            void clear()
            {
                SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            }

            void update()
            {
                SDL_Flip(screen);
            }


        };
		

		void rasterLine(int p1x, int p1y, int p2x, int p2y, SDL_Surface* sur, int r, int g, int b)
		{
			int F, x, y;

			if (p1x > p2x)  // Swap points if p1 is on the right of p2
			{
				swap(p1x, p2x);
				swap(p1y, p2y);
			}

			// Handle trivial cases separately for algorithm speed up.
			// Trivial case 1: m = +/-INF (Vertical line)
			if (p1x == p2x)
			{
				if (p1y > p2y)  // Swap y-coordinates if p1 is above p2
				{
					swap(p1y, p2y);
				}

				x = p1x;
				y = p1y;
				while (y <= p2y)
				{
					put_pixel16(sur, x, y, 255, 0, 0);
					y++;
				}
				return;
			}
			// Trivial case 2: m = 0 (Horizontal line)
			else if (p1y == p2y)
			{
				x = p1x;
				y = p1y;

				while (x <= p2x)
				{
					put_pixel16(sur, x, y, r, g, b);
					x++;
				}
				return;
			}


			int dy            = p2y - p1y;  // y-increment from p1 to p2
			int dx            = p2x - p1x;  // x-increment from p1 to p2
			int dy2           = (dy << 1);  // dy << 1 == 2*dy
			int dx2           = (dx << 1);
			int dy2_minus_dx2 = dy2 - dx2;  // precompute constant for speed up
			int dy2_plus_dx2  = dy2 + dx2;


			if (dy >= 0)    // m >= 0
			{
				// Case 1: 0 <= m <= 1 (Original case)
				if (dy <= dx)   
				{
					F = dy2 - dx;    // initial F

					x = p1x;
					y = p1y;
					while (x <= p2x)
					{
						put_pixel16(sur, x, y, 255, 0, 0);
						if (F <= 0)
						{
							F += dy2;
						}
						else
						{
							y++;
							F += dy2_minus_dx2;
						}
						x++;
					}
				}
				// Case 2: 1 < m < INF (Mirror about y=x line
				// replace all dy by dx and dx by dy)
				else
				{
					F = dx2 - dy;    // initial F

					y = p1y;
					x = p1x;
					while (y <= p2y)
					{
						put_pixel16(sur, x, y, 255, 0, 0);
						if (F <= 0)
						{
							F += dx2;
						}
						else
						{
							x++;
							F -= dy2_minus_dx2;
						}
						y++;
					}
				}
			}
			else    // m < 0
			{
				// Case 3: -1 <= m < 0 (Mirror about x-axis, replace all dy by -dy)
				if (dx >= -dy)
				{
					F = -dy2 - dx;    // initial F

					x = p1x;
					y = p1y;
					while (x <= p2x)
					{
						put_pixel16(sur, x, y, 255, 0, 0);
						if (F <= 0)
						{
							F -= dy2;
						}
						else
						{
							y--;
							F -= dy2_plus_dx2;
						}
						x++;
					}
				}
				// Case 4: -INF < m < -1 (Mirror about x-axis and mirror 
				// about y=x line, replace all dx by -dy and dy by dx)
				else    
				{
					F = dx2 + dy;    // initial F

					y = p1y;
					x = p1x;
					while (y >= p2y)
					{
						put_pixel16(sur, x, y, 255, 0, 0);
						if (F <= 0)
						{
							F += dx2;
						}
						else
						{
							x++;
							F += dy2_plus_dx2;
						}
						y--;
					}
				}
			}
		}
		
		void rasterCircle(int x0, int y0, int radius, SDL_Surface* sur, int r, int g, int b)
		{
			int f = 1 - radius;
			int ddF_x = 1;
			int ddF_y = -2 * radius;
			int x = 0;
			int y = radius;
			
			
			//rasterLine(x0, y0 + radius, x0, y0 - radius, sur);
			//rasterLine(x0 + radius, y0, x0 - radius, y0, sur);
			
			//cin.get();
			//cin.get();
			
			// Put a pixel at each side of the circle
			put_pixel16(sur, x0, y0 + radius, r, g, b);
			put_pixel16(sur, x0, y0 - radius, r, g, b);
			put_pixel16(sur, x0 + radius, y0, r, g, b);
			put_pixel16(sur, x0 - radius, y0, r, g, b);
		 
			while(x < y)
			{
				// ddF_x == 2 * x + 1;
				// ddF_y == -2 * y;
				// f == x*x + y*y - radius*radius + 2*x - y + 1;
				if(f >= 0) 
				{
				  y--;
				  ddF_y += 2;
				  f += ddF_y;
				}
				x++;
				ddF_x += 2;
				f += ddF_x;
				
				//rasterLine(x0 + x, y0 - y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 + y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 + y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 - y, x0 - x, y0 - y, sur);
				
				// Draw sides
				
				// Left
				put_pixel16(sur, x0 + x, y0 + y, r, g, b);
				put_pixel16(sur, x0 - x, y0 + y, r, g, b);
				
				// Right
				put_pixel16(sur, x0 + x, y0 - y, r, g, b);
				put_pixel16(sur, x0 - x, y0 - y, r, g, b);
				
				
				// Top
				put_pixel16(sur, x0 + x, y0 + y, r, g, b);
				put_pixel16(sur, x0 - x, y0 + y, r, g, b);
				
				// Bottom
				put_pixel16(sur, x0 + x, y0 - y, r, g, b);
				put_pixel16(sur, x0 - x, y0 - y, r, g, b);

			}
		}
		
		
		void rasterLineData(int p1x, int p1y, int p2x, int p2y, vector<point> &data)
		{
			int F, x, y;
			point tmp;
			if (p1x > p2x)  // Swap points if p1 is on the right of p2
			{
				swap(p1x, p2x);
				swap(p1y, p2y);
			}

			// Handle trivial cases separately for algorithm speed up.
			// Trivial case 1: m = +/-INF (Vertical line)
			if (p1x == p2x)
			{
				if (p1y > p2y)  // Swap y-coordinates if p1 is above p2
				{
					swap(p1y, p2y);
				}

				x = p1x;
				y = p1y;
				while (y <= p2y)
				{
					tmp.x = x;
					tmp.y = y;
					data.push_back(tmp);
					y++;
				}
				return;
			}
			// Trivial case 2: m = 0 (Horizontal line)
			else if (p1y == p2y)
			{
				x = p1x;
				y = p1y;

				while (x <= p2x)
				{
					tmp.x = x;
					tmp.y = y;
					data.push_back(tmp);
					x++;
				}
				return;
			}


			int dy            = p2y - p1y;  // y-increment from p1 to p2
			int dx            = p2x - p1x;  // x-increment from p1 to p2
			int dy2           = (dy << 1);  // dy << 1 == 2*dy
			int dx2           = (dx << 1);
			int dy2_minus_dx2 = dy2 - dx2;  // precompute constant for speed up
			int dy2_plus_dx2  = dy2 + dx2;


			if (dy >= 0)    // m >= 0
			{
				// Case 1: 0 <= m <= 1 (Original case)
				if (dy <= dx)   
				{
					F = dy2 - dx;    // initial F

					x = p1x;
					y = p1y;
					while (x <= p2x)
					{
						tmp.x = x;
						tmp.y = y;
						data.push_back(tmp);
						if (F <= 0)
						{
							F += dy2;
						}
						else
						{
							y++;
							F += dy2_minus_dx2;
						}
						x++;
					}
				}
				// Case 2: 1 < m < INF (Mirror about y=x line
				// replace all dy by dx and dx by dy)
				else
				{
					F = dx2 - dy;    // initial F

					y = p1y;
					x = p1x;
					while (y <= p2y)
					{
						tmp.x = x;
						tmp.y = y;
						data.push_back(tmp);
						if (F <= 0)
						{
							F += dx2;
						}
						else
						{
							x++;
							F -= dy2_minus_dx2;
						}
						y++;
					}
				}
			}
			else    // m < 0
			{
				// Case 3: -1 <= m < 0 (Mirror about x-axis, replace all dy by -dy)
				if (dx >= -dy)
				{
					F = -dy2 - dx;    // initial F

					x = p1x;
					y = p1y;
					while (x <= p2x)
					{
						tmp.x = x;
						tmp.y = y;
						data.push_back(tmp);
						if (F <= 0)
						{
							F -= dy2;
						}
						else
						{
							y--;
							F -= dy2_plus_dx2;
						}
						x++;
					}
				}
				// Case 4: -INF < m < -1 (Mirror about x-axis and mirror 
				// about y=x line, replace all dx by -dy and dy by dx)
				else    
				{
					F = dx2 + dy;    // initial F

					y = p1y;
					x = p1x;
					while (y >= p2y)
					{
						tmp.x = x;
						tmp.y = y;
						data.push_back(tmp);
						if (F <= 0)
						{
							F += dx2;
						}
						else
						{
							x++;
							F += dy2_plus_dx2;
						}
						y--;
					}
				}
			}
		}

		void rasterCircleData(int x0, int y0, int radius, vector<point> &data)
		{
			int f = 1 - radius;
			int ddF_x = 1;
			int ddF_y = -2 * radius;
			int x = 0;
			int y = radius;
			point tmp;
			
			//rasterLine(x0, y0 + radius, x0, y0 - radius, sur);
			//rasterLine(x0 + radius, y0, x0 - radius, y0, sur);
			
			//cin.get();
			//cin.get();
			
			// Put a pixel at each side of the circle
			tmp.x = x0;
			tmp.y = y0 + radius;
			data.push_back(tmp);
			
			tmp.x = x0;
			tmp.y = y0 - radius;
			data.push_back(tmp);
			
			tmp.x = x0 + radius;
			tmp.y = y0;
			data.push_back(tmp);
			
			tmp.x = x0 - radius;
			tmp.y = y0;
			data.push_back(tmp);
		 
			while(x < y)
			{
				// ddF_x == 2 * x + 1;
				// ddF_y == -2 * y;
				// f == x*x + y*y - radius*radius + 2*x - y + 1;
				if(f >= 0) 
				{
				  y--;
				  ddF_y += 2;
				  f += ddF_y;
				}
				x++;
				ddF_x += 2;
				f += ddF_x;
				
				//rasterLine(x0 + x, y0 - y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 + y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 + y, x0 - x, y0 + y, sur);
				//rasterLine(x0 + x, y0 - y, x0 - x, y0 - y, sur);
				
				// Draw sides
				// BUG: DUPLICATIONS 
				// Left
				tmp.x = x0 + x;
				tmp.y = y0 + y;
				data.push_back(tmp);
				
				tmp.x = x0 - x;
				tmp.y = y0 + y;
				data.push_back(tmp);
				
				
				// Right
				tmp.x = x0 + x;
				tmp.y = y0 - y;
				data.push_back(tmp);
				
				tmp.x = x0 - x;
				tmp.y = y0 - y;
				data.push_back(tmp);
	
				// Top
				tmp.x = x0 + x;
				tmp.y = y0 + y;
				data.push_back(tmp);
				
				tmp.x = x0 - x;
				tmp.y = y0 + y;
				data.push_back(tmp);
				
				
				// Bottom
				tmp.x = x0 + x;
				tmp.y = y0 - y;
				data.push_back(tmp);
				
				tmp.x = x0 - x;
				tmp.y = y0 - y;
				data.push_back(tmp);
			}
		}
		
}

#endif // GRAPHICS_H_INCLUDED
