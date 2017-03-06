#include "common.h"
#include "Thread.h"

class ThreadChild : public Thread{
	public:
		ThreadChild();
		virtual void * threadMainBody(void * arg);
		~ThreadChild();
};