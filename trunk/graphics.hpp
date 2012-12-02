#ifndef GRAPHICS_HPP_INCLUDED
#define GRAPHICS_HPP_INCLUDED
#include "../../include/sdl/sdl.h"
#include "../../include/sdl/begin_code.h"
#include "../../include/sdl/close_code.h"
#include "../../include/sdl-ttf/sdl_ttf.h"

// Graphics.hpp - Luke Connor 11/8/12
// Graphics functions for sdl games with pixel manipulation.

namespace pix
{
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

}


#endif // GRAPHICS_H_INCLUDED
