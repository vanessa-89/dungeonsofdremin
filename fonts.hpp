#ifndef BFF_HPP_INCLUDED
#define BFF_HPP_INCLUDED

// Fonts.hpp - Luke Connor 11/8/12

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
			//TTF_SetFontKerning(fontd, 0);
			//TTF_SetFontHinting(fontd, TTF_HINTING_NONE);
			//TTF_SetFontStyle(fontd, TTF_STYLE_ITALIC);

            return 0;
        }
		
		void resize(int size)
		{
			load(name, size);
		}

		int drawstr(SDL_Surface* &sur, int xd, int yd, int r, int g, int b, string str)
        {
			//cout << "drawing font..." << endl;

			SDL_Color Fcolor = {r, g, b}; 
			SDL_Color Bcolor = {0, 0, 0}; 
			
			SDL_Surface* message = NULL;
			
			message = TTF_RenderText_Shaded(fontd, str.c_str(), Fcolor, Bcolor);
			if(message == NULL)
			{
				return 1;
			}
			
			SDL_ConvertSurface(message, sur->format, NULL);
			SDL_SetColorKey(message, SDL_SRCCOLORKEY, SDL_MapRGB(message->format, 0, 0, 0));
			
			SDL_Rect offset;
			offset.x = xd;
			offset.y = yd;
			
			SDL_BlitSurface(message, NULL, sur, &offset );
			
			
		}
            


    };

}

#endif // BFF_HPP_INCLUDED
