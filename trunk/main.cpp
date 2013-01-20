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
        pix::put_pixel16(sur, x, 0, 0, 255, 0);
    }

    // Bottom line
    for(int x = 0; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 449, 0, 255, 0);
    }

    // Left Side line
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 0, y, 0, 255, 0);
    }

    // Right Side line
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 639, y, 0, 255, 0);
    }
        
    // Mid line x
    for(int x = 0; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 337, 0, 255, 0);
    }

    // Mid line y
    for(int y = 0; y < 480; y++)
    {
        pix::put_pixel16(sur, 449, y, 0, 255, 0);
    }

    // Right half divider
    for(int x = 450; x < 640; x++)
    {
        pix::put_pixel16(sur, x, 150, 0, 255, 0);
    }

}

void openInventory()
{
	static bool open;
	if(open == false)
	{
		cout << "Inventory Opened." << endl;
		open = true;
	}
	else
	{
		cout << "Inventory Closed." << endl;
		open = false;
		return;
	}
	
	
	
	return;
}


int main()
{
    cout << "Rougelike Game" << endl;
    cout << endl;
    cout << "Starting SDL..." << endl;
	
	vector<pix::point> dat;

	
 	
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
	if(basicfont.load("media/alphbeta.ttf", 12) != 0)
	{
		cout << "[ERROR] Could Not Find Font File!" << endl;
		exit(1);
	}
    
	cout << "Loading... " << endl;
	
        
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
	
    cout << endl;
    cout << "Entering main loop..." << endl;
    bool running = true;
	
	// Testing data
	int xx = 0;
	int yy = 0;	
	
	// System data
	Uint32 startTime; 
	int frames = 0;
	char buffer[10];
	bool debugmode = false;
	string debugmessage;
	int fps = 0;
	
	
	float frametime = 0;
	float delta = 0;
	float averageframetime;
	float frametimes[60];
	int frametimesindex = 0;
	
	// Dev data
	bool devmode = false;
	sgui::button inventoryButton(450, 450, 639, 479, 0, 0, 255, "INVENTORY", 12, 255, 0, 0, &openInventory, &basicfont);
	
	// Game Data
	int mousex = 0;
	int mousey = 0;
	char msgbuffer[10];
	unsigned int depth = 100;
	
	tiles::tilemap map(28,28,1,1);
	tiles::tiledat * tdat = new tiles::tiledat;
	
	for(int fx = 0; fx < 16; fx++)
	{
		for(int fy = 0; fy < 16; fy++)
		{
			tdat->data[fx][fy].r = 255;
			tdat->data[fx][fy].g = 0;
			tdat->data[fx][fy].b = fx*16;
			tdat->data[fx][fy].alpha = false;
		}
	}
	//tdat->data[0][0].r = 255;
	//tdat->data[0][0].g = 0;
	//tdat->data[0][0].b = 0;
	
	map.writeTile(tdat, 20, 10);
	map.writeTile(tdat, 10, 10);
	map.writeTile(tdat, 15, 14);
	
	
	
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
					
				}
				
			}
            
        }
                
        // Lock the screen surface and clear it, then do drawing 
        //SDL_LockSurface(gwin.screen);
        //depth++;
		SDL_GetMouseState(&mousex, &mousey);
		
		
		gwin.clear();
		// START DRAWING

        drawDividers(gwin.screen);
                
        
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
		
		
		
		map.draw(gwin.screen);
		pix::put_pixel16(gwin.screen, (float)xx*delta, (float)yy*delta, 255, 0, 0);
		//cout << delta << endl;
		inventoryButton.graphicsUpdate(gwin.screen);
		

		//pix::rasterCircle(100, 100, 60, gwin.screen, 255, 0, 0);
		rasterCircleData(0,0,20, dat);
		for(int x = 0; x < dat.size(); x++)
		{
			pix::put_pixel16(gwin.screen, dat[x].x+50, dat[x].y+50, 255, 0, 0);
		}
		
		
		// END DRAWING
		if(debugmode == true)
		{
			basicfont.drawstr(gwin.screen, 2, 0, 255, 0, 255, "DEBUG MONITOR");
			// Mouse Pos
			debugmessage.clear();
			debugmessage = "MPOS: ";
			itoa(mousex, buffer, 10);
			debugmessage += buffer; 
			debugmessage += ", ";
			itoa(mousey, buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 20, 255, 0, 255, debugmessage);
			
			// FPS
			debugmessage.clear();
			debugmessage = "FPS: ";
			
			itoa(fps, buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 30, 255, 0, 255, debugmessage);
			
			// Frame Time
			debugmessage.clear();
			debugmessage = "FRAMET: ";
			
			itoa((int)(frametime), buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 40, 255, 0, 255, debugmessage);
			
			// Delta
			debugmessage.clear();
			debugmessage = "DELTA (x1000): ";
			
			itoa((int)(delta*1000), buffer, 10);
			debugmessage += buffer;
			basicfont.drawstr(gwin.screen, 2, 50, 255, 0, 255, debugmessage);
			
		}
		
		if(devmode == true)
		{
			basicfont.drawstr(gwin.screen, 2, 0, 255, 0, 255, "DEV CONSOLE");
			basicfont.drawstr(gwin.screen, 2, 10, 255, 0, 255, ">");
			
			//while(keystates[SDLK_RETURN] != true)
			{
				//keystates = SDL_GetKeyState( NULL ); // Update keystates
				//for(int k = 0; k < )
			
			}

		}
        
		
        // Unlock screen surface so we can update the screen
        //SDL_UnlockSurface(gwin.screen);
		
        // update screen
        gwin.update();
		xx+=10;
		yy+=10;
		
		SDL_Delay(2); // Reduce CPU usage
		// FPS Calculation
		if(debugmode == true)
		{
			fps = ((float)1000/(float)frametime);
		}
		++frames;
		
		// Timer based movement with smoothing system
		frametime = (float)((SDL_GetTicks() - startTime));
		frametimes[frametimesindex] = frametime;
		//delta = frametime/1000;
		frametimesindex++;
		
		if(frametimesindex == 60)
		{
			frametimesindex = 0;
			averageframetime = 0;
			for(int av = 0; av < 60; av++)
			{
				averageframetime += frametimes[av];
			}
			averageframetime /= 60;
			delta = averageframetime/1000;
		}
		// Reset starttime for the next frame
		startTime = SDL_GetTicks();

    }

    SDL_Quit();
    cout << "Clean up complete, exiting." << endl;
    exit(0);

}