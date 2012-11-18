#include <iostream>
#include <string>
#include <cmath>

#include "graphics.hpp"
#include "objects.hpp"
#include "fonts.hpp"

#undef main

using namespace std;

class character : public obj::objectBase
{
    public:
    SDL_PixelFormat* pixform;

    character(SDL_PixelFormat* pix)
    {
        pixform = pix;
    }

    string name;
    int hp;
    int magic;
    int armor;


};


void drawDividers(SDL_Surface* sur)
{
    // Top line
    for(int x = 0; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 0, 255, 255, 255);
    }

    // Bottom line
    for(int x = 0; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 479, 255, 255, 255);
    }

    // Left Side line
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 0, y, 255, 255, 255);
    }

    // Right Side line
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 639, y, 255, 255, 255);
    }


    // Mid line x
    for(int x = 0; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 340, 255, 255, 255);
    }

    // Mid line y
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 450, y, 255, 255, 255);
    }

    // Right half divider
    for(int x = 450; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 150, 255, 255, 255);
    }

}

int main()
{
    cout << "Rougelike Game 0.1" << endl;
    cout << endl;
    cout << "Starting SDL..." << endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_ShowCursor(0);
    cout << "Opening Window..." << endl;
    pix::window gwin;
    gwin.open(640, 480, 16, false);
    cout << endl;
    //cout << SDL_GetError() << endl;

    SDL_Event event;
    Uint8 *keystates;

    bff_font::font basicfont;
    basicfont.load("Media/Midevil.bff");


    character chest(gwin.screen->format);
    chest.load("chest.pfo");


    cout << endl;
    cout << "Entering main loop..." << endl;
    bool running = true;
    float x = 0;
    while(running)
    {
        SDL_LockSurface(gwin.screen);
        gwin.clear();





        //mainchar.draw(gwin.screen, 0, 0);
        //basicfont.drawstr(gwin.screen, 0, 0, 255, 100, 100, "= THE DUNGEONS OF DREMIN =");
        //basicfont.draw(gwin.screen, x, 1, 255, 255, 255, 'D');

        drawDividers(gwin.screen);
        basicfont.drawstr(gwin.screen, 450, 160, 255, 100, 100, "HP");



        // poll and shandle events
        while( SDL_PollEvent( &event ) )
        {
            keystates = SDL_GetKeyState( NULL ); // Update keystates
            if( event.type == SDL_QUIT ) // if x pressed, exit
            {
                running = false;
            }
            if(keystates[SDLK_ESCAPE]) // if esc pressed, exit
            {
                running = false;
            }
        }


        SDL_UnlockSurface(gwin.screen);

        // update screen
        gwin.update();

        //cout << SDL_GetError();
        x+=0.1;

    }

    SDL_Quit();

}
