#ifndef BFF_HPP_INCLUDED
#define BFF_HPP_INCLUDED

// Fonts.hpp - Luke Connor 11/8/12
// Graphics functions for sdl games with pixel manipulation.

#include <string>
#include <fstream>
#include "graphics.hpp"

using namespace std;


namespace ttf_font
{
    class fontwrapper
    {
        public:
		TTF_Font *fontd;
		string name;
        fontwrapper()
        {
			TTF_Init();
			fontd = NULL;
        }
		~fontwrapper()
		{
			TTF_CloseFont(fontd);
		}

        int load(std::string fname, int size)
        {
            name = fname;
			fontd = TTF_OpenFont(fname.c_str(), size);
			if( fontd == NULL )
			{
				return 1;
			}

            return 0;
        }
		
		void resize(int size)
		{
			load(name, size);
		}

		int drawstr(SDL_Surface* &sur, int xd, int yd, int r, int g, int b, string str)
        {
			//cout << "drawing font..." << endl;
			Uint8 pv;
			Uint8 tr, tg, tb;
			
			SDL_Surface* message = NULL;
			SDL_Color Fcolor = { r, g, b };
			SDL_Color Bcolor = { 0, 0, 0 };
			// If the text color is black, change the alpha
			if(Fcolor.r == 0 && Fcolor.g == 0 && Fcolor.b == 0) Bcolor.b = 1;
	
			
			message = TTF_RenderText_Shaded(fontd, str.c_str(), Fcolor, Bcolor);
			if(message == NULL)
			{
				return 1;
			}
			
			//SDL_ConvertSurface(message, sur->format, NULL);

			for(int x = 0; x < message->h/2; x++)
			{
				for(int y = 0; y < message->w/2; y++)
				{
					pv = pix::get_pixel16(message, y, x);
					SDL_GetRGB(pv, message->format, &tr,&tg,&tb);
					
					// Check if its the alpha color
					if(tr == Bcolor.r && tg == Bcolor.g && tb == Bcolor.b) continue;
					pix::put_pixel16(sur, y+xd, x+yd, tr, tg, tb);
				}
			}
			
		}
            


    };

}

#endif // BFF_HPP_INCLUDED
