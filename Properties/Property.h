#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "cocos2d.h"

namespace AstralGame
{


	enum class PROPS_TYPE
	{
		hittable,
		observed,
		observer,
		count
	};

	class Property : public cocos2d::Ref
	{
	protected:

		Property(PROPS_TYPE tag);

	public:

		PROPS_TYPE getTag() { return tag; }

	private:

		//this field set by derived classes!
		PROPS_TYPE tag;

	};


#define CREATE_FROM_REF(__TYPE__) \
	static __TYPE__* create() \
	{ \
	__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
	if (pRet != nullptr) \
	{ \
	pRet->autorelease(); \
	return pRet; \
		} \
	else \
	{ \
	delete pRet; \
	pRet = nullptr; \
	return nullptr; \
		} \
		}


}

#endif //__PROPERTY_H__