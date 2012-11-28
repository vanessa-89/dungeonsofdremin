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
	};
	
	class weapon : public itembase
	{
		public:
		int damage; // Damage
		int range; // Range of attack
		float delay; // time before another attack
	};
	
	
	class projectile : public weapon
	{
		public:
		int r, g, b; // Color for projectile
	};
	
}





#endif