#include "common.h"


//class Thread;
class ThreadManager{
	
	private:
		vector <thread *> threads; // Vector of Thread pointers
	public:
		ThreadManager(); // Constructor
		void addThread (thread * p_thread); // Add a thread
		void joinThreads();
		void start();// Start all threads
		void barrier(); // Wait for all threads to finish
		~ThreadManager(); // Destructor
};