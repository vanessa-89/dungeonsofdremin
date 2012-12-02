#ifndef ITEMS_HPP_INCLUDED
#define ITEMS_HPP_INCLUDED

#include <vector>

using namespace std;

namespace actors
{

	class actor
	{
		public:
		vector<items::itembase> inventory;
		vector<unsigned int> invamount; // of given inv item
		
		items::itembase equipped[9];
		unsigned int eqamount[9];
		
		actor()
		{
		
		
		}
		
		virtual void update()
		{
		
		
		}
		
		void equip(int iitem, int eitem)
		{
			equipped[eitem] = inventory[iitem];
			eqamount[eitem] = invamount[iitem];
			inventory.erase(item);
			invamount.erase(item);
		}
		
		void unequip(int eitem, int iitem)
		{
			equipped[eitem]
			invamount.insert(eqamount[eitem])
			inventory.erase(item);
			invamount.erase(item);
		}
		
		
		
	};


}



#endif