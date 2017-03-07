#include "common.h"
#include "Thread.h"

class ThreadAnd : public Thread{
	public:
		ThreadAnd();
		virtual void * threadMainBody(void * arg);
		~ThreadAnd();
};