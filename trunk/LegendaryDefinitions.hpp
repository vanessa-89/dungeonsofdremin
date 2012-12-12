#ifndef LEGEBD_HPP_INCLUDED
#define LEGEND_HPP_INCLUDED

#include "items.hpp"

namespace legends
{
	
	class legendary
	{
		public:
		items::projectile* ROFLCANNON; // LUKE CONNOR
      
		weps()
		{
			ROFLCANNON = new items::projectile;
			ROFLCANNON->name = "ROFLCANNON";
			ROFLCANNON->desc = "Nyan Cat's weapon of choice";
			ROFLCANNON->value = 10000000000000000;
			ROFLCANNON->damage = 9001;
			ROFLCANNON->range = 5000;
			ROFLCANNON->delay = 0.1;
			ROFLCANNON->r = 255;
			ROFLCANNON->g = 0;
			ROFLCANNON->b = 255;
	
		
		}
		
		
		~weps()
		{
			delete ROFLCANNON;
		
		}
	
	};


}


#endif