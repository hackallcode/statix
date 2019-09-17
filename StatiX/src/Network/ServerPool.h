#ifndef __SERVER_POOL_INCLUDED__
#define __SERVER_POOL_INCLUDED__

#include "../Common/Pool.h"
#include "General.h"
#include "Session.h"

namespace serv
{
	class NetPool
		: public statix::Pool<Task, Callback>
	{
	public:
		NetPool(size_t threadNum, Session const& session, CallbackFunc callback);

	protected:
		virtual void Tick_(TaskElem task, CallbackFunc callback) override;

	private:
		Session const& session_;

	};
}

#endif // !__SERVER_POOL_INCLUDED__
