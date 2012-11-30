#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>

#include "graphics.hpp"
#include "fonts.hpp"
#include "sprite.h"
#include "tilemanager.hpp"
#include "items.hpp"

#undef main

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
        pix::put_pixel16(sur, x, 337, 255, 255, 0);
    }

    // Mid line y
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 449, y, 255, 0, 255);
    }

    // Right half divider
    for(int x = 450; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 150, 255, 255, 255);
    }

}

int main()
{
    cout << "Rougelike Game" << endl;
    cout << endl;
    cout << "Starting SDL..." << endl;

    SDL_Init(SDL_INIT_EVERYTHING);
    //SDL_ShowCursor(0); // Hide courser
    cout << "Opening Window..." << endl;
    pix::window gwin;
    gwin.open(640, 480, 16, false);
    cout << endl;

    SDL_Event event;
    Uint8 *keystates;
	
	
	TTF_Init(); // start font system
    ttf_font::fontwrapper basicfont;
	if(basicfont.load("media/alphbeta.ttf", 30) != 0)
	{
		cout << "[ERROR] Could Not Find Font File!" << endl;
		exit(1);
	}
        
    // Temporary tile defintion for testing
	tiles::tile tmptile;
	tmptile.clear();
        
		
	for(int x = 0; x < 16; x++)
	{
		for(int y = 0; y < 16; y++)
		{
				tmptile.frames[0][x][y] = x;
		}
	}
		
		
    tmptile.frames[0][0][0] = 12435;
    tmptile.frames[0][0][16] = 12435;
    tmptile.frames[0][16][0] = 12435;
    tmptile.frames[0][16][16] = 12435;
        
    tmptile.frames[0][8][8] = 455675;
        
    // Create map
    tiles::tilemap map;
        
    // Fill map with tmp tiles
    for(int sx = 0; sx < 28; sx++)
    {
        for(int sy = 0; sy < 21; sy++)
        {
			map.tiledat[sx][sy] = &tmptile;
        }
    }
        
    // Items test
    vector<items::itembase> itemTable;
        
    // How to construct a custom object and add it to the item table
    items::projectile* it = new items::projectile;
    it->name = "ROFLCANNON";
    it->desc = "Nyan cat's weapon of choice";
    it->value = 10000000000000000;
    it->damage = 9001;
    it->range = 5000;
    it->delay = 0.1;
    it->r = 255;
    it->g = 0;
    it->b = 0;
    itemTable.push_back(*it);
    delete it;
        
    cout << itemTable[0].desc << endl;
        
    cout << endl;
    cout << "Entering main loop..." << endl;
    bool running = true;
	
    int x = 0;
	int y = 0;
	
	// Debug data
	Uint32 startTime; 
	Uint8 r, g, b;
	int frames = 0;
	char buffer[10];
	bool debugmode = false;
	string debugmessage;
	int fps = 0;
	float frametime = 0;
	
	startTime = SDL_GetTicks();
    while(running)
    {
		// poll and handle events
        while( SDL_PollEvent( &event ) )
        {
            keystates = SDL_GetKeyState( NULL ); // Update keystates
            if( event.type == SDL_QUIT ) // if x pressed, exit
            {
                cout << "Exit initiated." << endl;
                running = false;
            }
            if(keystates[SDLK_ESCAPE]) // if esc pressed, exit
            {
                cout << "Exit initiated." << endl;
                running = false;
            }
			if(keystates[SDLK_F1]) // if esc pressed, exit
            {
                if(debugmode == true)
				{
					debugmode = false;
				}
				else
				{
					debugmode = true;
				}
            }
        }
                
        // Lock the screen surface and clear it, then do drawing 
        //SDL_LockSurface(gwin.screen);
        
		SDL_GetMouseState(&x, &y);
		//cout << x << ", " << y << endl; 
		
		SDL_GetRGB(pix::get_pixel16(gwin.screen, x, y), gwin.screen->format, &r, &g, &b);
		//cout << (int)r << ", " << (int)g << ", " << (int)b << endl;
		gwin.clear();

		
        //mainchar.draw(gwin.screen, 0, 0);
        //basicfont.drawstr(gwin.screen, 0, 0, 255, 100, 100, "= THE DUNGEONS OF DREMIN =");
        //basicfont.draw(gwin.screen, x, 1, 255, 255, 255, 'D');

        drawDividers(gwin.screen);
                
        // Draw the tilemap
        map.draw(gwin.screen, 1, 1);
        //tmptile.draw(gwin.screen, 0, 0);
        
		basicfont.drawstr(gwin.screen, 450, 160, 255, 100, 100, "HP: 100");
		
		if(debugmode == true)
		{
			// Mouse Pos
			debugmessage.clear();
			debugmessage = "MPOS: ";
			itoa(x, buffer, 10);
			debugmessage += buffer; 
			debugmessage += ", ";
			itoa(y, buffer, 10);
			debugmessage += buffer; 
			basicfont.drawstr(gwin.screen, 0, 0, 255, 0, 255, debugmessage);
			
			// FPS
			debugmessage.clear();
			debugmessage = "FPS: ";
			
			itoa(fps, buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 0, 10, 255, 0, 255, debugmessage);
		}
		//itoa(xs, buffer, 10);
		//basicfont.drawstr(gwin.screen, 0, 0, 255, 0, 255, buffer);
                
        // Unlock screen surface so we can update the screen
        //SDL_UnlockSurface(gwin.screen);

        // update screen
        gwin.update();

        //cout << SDL_GetError();
		++frames;
		if(debugmode == true)
		{
			frametime = ((SDL_GetTicks() - startTime));
			cout << fps << endl;
			fps = ((float)1000/(float)frametime);
			startTime = SDL_GetTicks();
		}

    }

    SDL_Quit();
        cout << "Clean up complete, ending." << endl;
        exit(0);

}