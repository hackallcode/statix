#ifndef __FILES_POOL_INCLUDED__
#define __FILES_POOL_INCLUDED__

#include "../Common/Pool.h"
#include "General.h"
#include "Cache.h"

namespace files
{
	class FilesPool
		: public statix::Pool<Task, Callback>
	{
	public:
		FilesPool(Cache const& cache, size_t threadNum, CallbackFunc callback);

	protected:
		virtual void Tick_(TaskElem task, CallbackFunc callback) override;

	private:
		Cache const& cache_;

	};
}

#endif // !__FILES_POOL_INCLUDED__
