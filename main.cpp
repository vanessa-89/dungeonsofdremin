#include <iostream>
#include <string>
#include <cmath>

#include "graphics.hpp"
#include "fonts.hpp"
#include "objects.hpp"
#include "tilemanager.hpp"

#undef main
//commit test

using namespace std;

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
        pix::put_pixel16(sur, x, 340, 255, 255, 0);
    }

    // Mid line y
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 450, y, 255, 0, 255);
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
	
	// Temporary tile defintion for testing
	tiles::tile tmptile;
	tmptile.clear();
	
	tmptile.frames[0][0][0] = 12435;
	tmptile.frames[0][0][16] = 12435;
	tmptile.frames[0][16][0] = 12435;
	tmptile.frames[0][16][16] = 12435;
	
	tmptile.frames[0][8][8] = 1249456;
	
	// Create map
	tiles::tilemap map;
	
	// Tmp
	for(int sx = 0; sx < 28; sx++)
	{
		for(int sy = 0; sy < 21; sy++)
		{
			map.tiledat[sx][sy] = &tmptile;
		}
	}
	
	
    cout << endl;
    cout << "Entering main loop..." << endl;
    bool running = true;
    float x = 0;
    while(running)
    {
        // poll and handle events
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
		
		// Lock the screen surface and clear it, then do drawing 
		SDL_LockSurface(gwin.screen);
        gwin.clear();

        //mainchar.draw(gwin.screen, 0, 0);
        //basicfont.drawstr(gwin.screen, 0, 0, 255, 100, 100, "= THE DUNGEONS OF DREMIN =");
        //basicfont.draw(gwin.screen, x, 1, 255, 255, 255, 'D');

        drawDividers(gwin.screen);
        basicfont.drawstr(gwin.screen, 450, 160, 255, 100, 100, "HP");
		
		// Draw the tilemap
		map.draw(gwin.screen, 2, 2);
		//tmptile.draw(gwin.screen, 0, 0);
		
		
		// Unlock screen surface so we can update the screen
        SDL_UnlockSurface(gwin.screen);

        // update screen
        gwin.update();

        //cout << SDL_GetError();
        x+=0.1;

    }

    SDL_Quit();

}
