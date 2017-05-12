#ifndef  __COMPONENTSFACTORY_H__
#define  __COMPONENTSFACTORY_H__

#include "cocos2d.h"

class ComponentsFactory : public cocos2d::Ref
{

public:

	static ComponentsFactory * create();

protected:

	ComponentsFactory() {}

};

#endif //__COMPONENTSFACTORY_H__