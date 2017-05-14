#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

#include "Properties\Property.h"

namespace AstralGame
{
	class Parameters : public cocos2d::Ref
	{
	protected:

		Parameters() = default;

	public:

		CREATE_FROM_REF(Parameters);

	public:

		//we can get by tag
		Property * getProperty(PROPS_TYPE tag);

		template<typename T>
		T getProperty(PROPS_TYPE tag)
		{
			static_assert(std::is_convertible<T, Property *>::value, "Invalid Type for cocos2d::Vector<T>!");
			auto iter = find_if(properties.begin(), properties.end(),
				[tag](Property * property) { return property->getTag() == tag; });
			if (iter != properties.end())
				return dynamic_cast<T>(*iter);
			else
				return nullptr;
		}

		//but we can't add with tag, cause tag sets automaticly by derived class
		//return true if add success
		bool addPropertry(Property * property);

	private:

		cocos2d::Vector<Property *> properties;

	};
}

#endif //__PARAMETERS_H__