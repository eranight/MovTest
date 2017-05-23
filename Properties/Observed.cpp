#include "Observed.hpp"
#include "Observer.hpp"

USING_NS_CC;
using namespace AstralGame;

Observed::Observed() : Property(PROPS_TYPE::observed)
{
}

Observed::~Observed()
{
	resetObserver();
}

void Observed::addObserver(Observer * observer)
{
	observers.insert(observer);
}

void Observed::removeObserver(Observer * observer)
{
	observers.erase(observer);
}

void Observed::resetObserver()
{
	for (auto & iter : observers)
		iter->loseTarget();

	observers.clear();
}