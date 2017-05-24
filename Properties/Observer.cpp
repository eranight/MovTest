#include "Observer.hpp"
#include "Observed.hpp"
#include "BrickClasses\Parameters.h"

USING_NS_CC;
using namespace AstralGame;

Observer::Observer() : Property(PROPS_TYPE::observer)
{
	target = nullptr;
}

Observer::~Observer()
{
	//loseTarget();
}

void Observer::captureTarget(Node * target)
{
	auto observed = dynamic_cast<Parameters *>(target->getUserObject())->getProperty<Observed *>(PROPS_TYPE::observed);
	CCASSERT(observed != nullptr, "Observed shouldn't be null!");
	observed->addObserver(this);
	this->target = target;
}

void Observer::loseTarget()
{
	target = nullptr;
	loseTargetReaction();
}

void Observer::dropTarget()
{
	if (target != nullptr)
	{
		auto observed = dynamic_cast<Parameters *>(target->getUserObject())->getProperty<Observed *>(PROPS_TYPE::observed);
		CCASSERT(observed != nullptr, "Observed shouldn't be null!");
		observed->removeObserver(this);
	}
}