#ifndef ACTORS_HPP_INCLUDED
#define ACTORS_HPP_INCLUDED

#include <vector>
#include "items.hpp"

using namespace std;

namespace actors
{

	class actor
	{
		public:
		vector<items::itembase> inventory;
		vector<unsigned int> invamount; // of given inv item
		
		items::itembase equipped[9];
		unsigned int equippedamount[9];
		
		actor()
		{
		
		
		}
		
		virtual void update()
		{
		
		
		}
		
		void equip(int iitem, int eitem)
		{
			//equipped[eitem] = inventory[iitem];
			//eqamount[eitem] = invamount[iitem];
			//inventory.erase(iitem);
			//invamount.erase(iitem);
		}
		
		
		
	};


}



#endif