#include <iostream>
#include <string>
#include <cmath>
#include <typeinfo>

#include "graphics.hpp"
#include "fonts.hpp"
//#include "sprite.hpp"
#include "tilemanager.hpp"
#include "items.hpp"
#include "actors.hpp"
#include "gui.hpp"
#include "LegendaryDefinitions.hpp"

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
        pix::put_pixel16(sur, x, 337, 255, 255, 255);
    }

    // Mid line y
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 449, y, 255, 255, 255);
    }

    // Right half divider
    for(int x = 450; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 150, 255, 255, 255);
    }

}

void testfunc()
{
	cout << "test" << endl;
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
    gwin.open(640, 480, 16, true);
    cout << endl;

    SDL_Event event;
    Uint8 *keystates;
	
	TTF_Init(); // start font system
    ttf_font::fontwrapper basicfont;
	if(basicfont.load("media/alphbeta.ttf", 12) != 0)
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
				tmptile.dat[x][y].r = 255;
				tmptile.dat[x][y].g = 0;
				tmptile.dat[x][y].b = 0;
		}
	}
        
	tiles::tile tmptile2;
	tmptile2.clear();
        	
	for(int x = 0; x < 16; x++)
	{
		for(int y = 0; y < 16; y++)
		{
				tmptile2.dat[x][y].r = 0;
				tmptile2.dat[x][y].g = 255;
				tmptile2.dat[x][y].b = 0;
		}
	}
		
    // Create map
    tiles::tilemap map;
	map.clear();
        
    // Fill map with tmp tiles
    for(int sx = 0; sx < 28; sx++)
    {
        for(int sy = 0; sy < 21; sy++)
        {
			//map.tiledat[sx][sy] = tmptile2;
        }
    }
	
	map.tiledat[10][10] = tmptile2;
        
    // Items
    vector<items::itembase> itemTable;
        
    // How to construct a custom object and add it to the item table
    items::projectile* it = new items::projectile;
    it->name = "ROFLCANNON";
    it->desc = "Nyan cat's weapon of choice";
    it->value = 10000000;
    it->damage = 9001;
    it->range = 5000;
    it->delay = 0.1;
    it->r = 255;
    it->g = 0;
    it->b = 255;
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
	int frames = 0;
	char buffer[10];
	bool debugmode = false;
	string debugmessage;
	int fps = 0;
	float frametime = 0;
	float delta= 0;
	int xx = 0;
	int yy = 0;
	
	// Dev data
	bool devmode = false;
	
	
	sgui::button inventoryButton(450,460,639,479, 0, 0, 255, "INVENTORY", 12, 255, 0, 0, &testfunc, &basicfont);
	
	char r,g,b;
	r = 220;
	g = 200;
	b = 0;
	
	// Game Data
	
	char msgbuffer[10];
	unsigned int depth = 100;
	
	
	// Start frame timer
	startTime = SDL_GetTicks();
    while(running)
    {
		// poll and handle events
        while( SDL_PollEvent( &event ) )
        {
            if( event.type == SDL_QUIT ) // if x pressed, exit
            {
                cout << "Exit initiated." << endl;
                running = false;
            }
			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				if(event.button.button == SDL_BUTTON_LEFT)
				{
					// Update gui butttons
					inventoryButton.logicUpdate();
				}
			
			}
			
			
			if( event.type == SDL_KEYDOWN )
			{
				keystates = SDL_GetKeyState( NULL ); // Update keystates
				
				if(keystates[SDLK_ESCAPE]) // if esc pressed, exit
				{
					cout << "Exit initiated." << endl;
					running = false;
				}
				if(keystates[SDLK_F1])
				{
					if(devmode == true)
					{
						devmode = false;
					}
					if(debugmode == true)
					{
						debugmode = false;
					}
					else
					{
						debugmode = true;
					}
				}
				if(keystates[SDLK_F2])
				{
					/*
					if(debugmode == true)
					{
						debugmode = false;
					}
					if(devmode == true)
					{
						devmode = false;
					}
					else
					{
						devmode = true;
					}
					*/
				}
				
			}
            
        }
                
        // Lock the screen surface and clear it, then do drawing 
        //SDL_LockSurface(gwin.screen);
        //depth++;
		SDL_GetMouseState(&x, &y);
		

		gwin.clear();

        drawDividers(gwin.screen);
                
        // Draw the tilemap
        map.draw(gwin.screen, 1, 1);
        //tmptile.draw(gwin.screen, 0, 0);
        
		basicfont.resize(10);
		itoa(depth, msgbuffer, 10);
		basicfont.drawstr(gwin.screen, 460, 3, 135, 85, 45, (string)"DEPTH: " + (string)msgbuffer);
		
		basicfont.resize(12);
		itoa(depth, msgbuffer, 10);
		basicfont.drawstr(gwin.screen, 452, 160, 219, 50, 50, (string)"HEALTH: " + (string)msgbuffer);
		itoa(depth, msgbuffer, 10);
		basicfont.drawstr(gwin.screen, 452, 170, 153, 153, 153, (string)"ARMOR: " + (string)msgbuffer);
		itoa(depth, msgbuffer, 10);
		basicfont.drawstr(gwin.screen, 452, 180, 224, 202, 31, (string)"COINS: " + (string)msgbuffer);
		
		
		inventoryButton.graphicsUpdate(gwin.screen);
		
		if(debugmode == true)
		{
			basicfont.drawstr(gwin.screen, 2, 0, 255, 0, 255, "DEBUG MONITOR");
			// Mouse Pos
			debugmessage.clear();
			debugmessage = "MPOS: ";
			itoa(x, buffer, 10);
			debugmessage += buffer; 
			debugmessage += ", ";
			itoa(y, buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 20, 255, 0, 255, debugmessage);
			
			// FPS
			debugmessage.clear();
			debugmessage = "FPS: ";
			
			itoa(fps, buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 30, 255, 0, 255, debugmessage);
		}
		
		if(devmode == true)
		{
			basicfont.drawstr(gwin.screen, 2, 0, 255, 0, 255, "DEV CONSOLE");
			basicfont.drawstr(gwin.screen, 2, 10, 255, 0, 255, ">");
			
			while(keystates[SDLK_RETURN] != true)
			{
				keystates = SDL_GetKeyState( NULL ); // Update keystates
				//for(int k = 0; k < )
			
			}

		}
        
        // Unlock screen surface so we can update the screen
        //SDL_UnlockSurface(gwin.screen);
		
        // update screen
		
		//for(int p = 0; p < 50; p++)
		{
			//for(int l = 0; l < 50; l++)
			{
				//pix::put_pixel16(gwin.screen, p, l, r, g, b);
			
			}
		
		}
		
		pix::put_pixel16(gwin.screen, (float)xx*delta, (float)yy*delta, 255, 0, 0);
		cout << delta << endl;
		r !=0 ? r-=1 : 0;
		g !=0 ? g-=1 : 0;
		b !=0 ? b-=1 : 0;
		
		
        gwin.update();
		SDL_Delay(10);
		
		xx+=10;
		yy+=10;

		++frames;
		if(debugmode == true)
		{
			fps = ((float)1000/(float)frametime);
		}
		
		frametime = (float)((SDL_GetTicks() - startTime));
		delta = frametime/1000; 

		startTime = SDL_GetTicks();
		
		

    }

    SDL_Quit();
        cout << "Clean up complete, ending." << endl;
        exit(0);

}