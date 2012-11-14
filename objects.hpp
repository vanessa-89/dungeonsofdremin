#ifndef OBJECTS_HPP_INCLUDED
#define OBJECTS_HPP_INCLUDED

#include "graphics.hpp"

#include <iostream>
#include <fstream>
#include <vector>

struct rgb
{
    char c[3];
};

using namespace std;

namespace obj
{
    class objectBase
    {
        public:

        Uint16 data[255][16][16];
        int x;
        int y;

        objectBase()
        {
            x = 0;
            y = 0;
        }

        int load(std::string fname)
        {
            // Pixel Frame Object
            cout << "Loading PFO Object " << fname << endl;
        }


        void draw(SDL_Surface* &sur, int xp, int yp, char frame)
        {

        }

    };
}

#endif // OBJECTS_HPP_INCLUDED
