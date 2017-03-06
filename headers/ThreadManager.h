#include "common.h"
#include "Thread.h"

class Thread;
class ThreadManager{
	
	private:
		vector <Thread *> threads; // Vector of Thread pointers
	public:
		ThreadManager(); // Constructor
		void addThread (Thread * p_thread); // Add a thread
		void start();// Start all threads
		void barrier(); // Wait for all threads to finish
		~ThreadManager(); // Destructor
};