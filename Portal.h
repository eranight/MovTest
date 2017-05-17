#ifndef  __PORTAL_H__
#define	  __PORTAL_H__

#include "cocos2d.h"

namespace AstralGame
{
	class Portal : public cocos2d::Node
	{
	protected:

		Portal() = default;

	public:

		bool init() override;

		CREATE_FUNC(Portal);

	private:

		cocos2d::Node * view;

	};
}

#endif  //__PORTAL_H__