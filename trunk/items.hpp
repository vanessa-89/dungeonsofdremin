#ifndef ITEMS_HPP_INCLUDED
#define ITEMS_HPP_INCLUDED

#include <string>
//#include <>

namespace items
{
        class itembase
        {
                public:
                string name;
                string desc;
                int value;
                itembase()
                {
        
                }
				virtual void use()
				{
				
				}
        };
        
		class healing : public itembase
		{
			public:
			int hpr;
			bool overflow;
			
			healing()
			{
				hpr = 0;
				overflow = false;
			}
			
			virtual void use(int &bhp)
			{
				if(overflow == false && bhp >= 100)
				{
					return;
				}
				
				bhp += hpr;
				
				
			
			}
			
		};
		
		
        class weapon : public itembase
        {
                public:
                int damage; // Damage
                int range; // Range of attack
                float delay; // time before another attack
				
				weapon()
				{
					damage = 0;
					range = 0; 
					delay = 0;
				
				}
				
        };
        
        
        class projectile : public weapon
        {
                public:
                int r, g, b; // Color for projectile
				
				virtual void use()
				{
				
					// Shoot projectile
				}

        };
		
        
}





#endif