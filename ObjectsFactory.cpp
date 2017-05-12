#include "ObjectsFactory.h"

USING_NS_CC;

ObjectsFactory * ObjectsFactory::create()
{
	ObjectsFactory * ret = new (std::nothrow) ObjectsFactory();
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