#include "ComponentsFactory.h"

USING_NS_CC;

ComponentsFactory * ComponentsFactory::create()
{
	ComponentsFactory * ret = new (std::nothrow) ComponentsFactory();
	if (ret != nullptr)
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}