#ifndef BFF_HPP_INCLUDED
#define BFF_HPP_INCLUDED

// Fonts.hpp - Luke Connor 11/8/12
// Graphics functions for sdl games with pixel manipulation.

#include <string>
#include <fstream>

using namespace std;


namespace bff_font
{
    class font
    {
        public:
        bool data[255][16][16];
        font()
        {

        }

        int load(std::string fname)
        {
            // BFF Bool Font Format
            cout << "Loading BFF Font " << fname << endl;
            char buffer[17];
            ifstream file;
            file.open(fname.c_str());
            if(file == NULL)
            {
                file.close();
                cout << "Error: Could Not Find Font File " << fname << endl;
                return 1;
            }

            int letter = 0;
            while(!file.eof())
            {

                for(int y = 0; y < 16; y++)
                {
                    file.getline(buffer, 17);
                    //cout << buffer << endl;

                    for(int x = 0; x < 16; x++)
                    {
                        data[letter][y][x] = buffer[x] - '0'; // convert to int, then bool
                    }

                }

                letter++;

            }

            file.close();
            return 0;
        }

        void draw(SDL_Surface* &sur, int xp, int yp, char r, char g, char b, char c)
        {
            for(int x = 0; x < 16; x++)
            {
                for(int y = 0; y < 16; y++)
                {
                    //cout << data[1][x][y];
                    if(data[(int)c-60][x][y] == 1)
                    {
                        pix::put_pixel16(sur, y+xp, x+yp, r, g, b);
                    }
                }
                //cout << endl;
            }

        }

        void drawstr(SDL_Surface* &sur, int xd, int yd, int r, int g, int b, string str)
        {
            int xr = 0;
            for(int letter = 0; letter < str.size(); letter++)
            {
                xr++;
                //cout << (letter*16) << endl;
                if(str[letter] == '\n')
                {
                    yd += 16;
                    xr = 0;
                }
                if(str[letter] == ' ')
                {
                    xr++;
                    continue;
                }
                draw(sur, xd+xr*16, yd, r, g, b, str[letter]);
            }
        }


    };

}

#endif // BFF_HPP_INCLUDED
