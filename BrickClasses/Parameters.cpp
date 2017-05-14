#include "Parameters.h"

USING_NS_CC;
using namespace AstralGame;
using std::size_t;
using std::find_if;

Property * Parameters::getProperty(PROPS_TYPE tag)
{
	auto iter = find_if(properties.begin(), properties.end(),
		[tag](Property * property) { return property->getTag() == tag; });
	if (iter != properties.end())
		return *iter;
	else
		return nullptr;
}

bool Parameters::addPropertry(Property * property)
{
	CCASSERT(property != nullptr, "Property shouldn't be null!");
	if (getProperty(property->getTag()) == nullptr)
	{
		properties.pushBack(property);
		return true;
	}
	else
		return false;
}