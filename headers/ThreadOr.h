#include "common.h"
#include "Thread.h"

class ThreadOr : public Thread{
	public:
		ThreadOr();
		virtual void * threadMainBody(void * arg);
		~ThreadOr();
};