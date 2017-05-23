#ifndef  __OBSERVRED_HPP__
#define  __OBSERVRED_HPP__

#include "Property.h"

namespace AstralGame
{
	class Observer;

	class Observed : public Property
	{
	protected:
		Observed();
		
	public:
	
		CREATE_FROM_REF(Observed);
		~Observed();

	public:

		void addObserver(Observer * observer);
		void removeObserver(Observer * observer);
		void resetObserver();

	private:

		std::set<Observer *> observers;
		
	};
}

#endif //__OBSERVRED_HPP__