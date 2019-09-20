#ifndef __NET_POOL_INCLUDED__
#define __NET_POOL_INCLUDED__

#include "../Common/Pool.h"
#include "General.h"
#include "Session.h"

namespace net
{
	class NetPool
		: public statix::Pool<Task, Callback>
	{
	public:
		NetPool(Parser const& parser, size_t threadNum, CallbackFunc callback);

	protected:
		virtual void Tick_(TaskElem task, CallbackFunc callback) override;

	private:
		Parser const& parser_;
	};
}

#endif // !__NET_POOL_INCLUDED__
