#ifndef  __OBJECTSFACTORY_H__
#define  __OBJECTSFACTORY_H__

#include "cocos2d.h"

class ObjectsFactory : public cocos2d::Ref
{
	
public:

	static ObjectsFactory * create();

protected:

	ObjectsFactory() {}

};


#endif //__OBJECTSFACTORY_H__