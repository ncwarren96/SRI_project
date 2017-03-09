#include "ThreadManager.h"

// Constructor
ThreadManager::ThreadManager() {}

// Add a thread
void ThreadManager::addThread (thread * p_thread) {
	cout<<"added thread "<<p_thread->get_id()<<endl;
	threads.push_back(p_thread); // Push back thread pointer to threads vector
}

// Start all threads
void ThreadManager::start() {
	// Loop on all vector threads and start them
	//for ( int i = 0 ; i < threads.size();i++) threads[i]->start();
}

void ThreadManager::joinThreads(){
	for ( int i = 0 ; i < threads.size();i++){
		if(threads[i]->joinable()){
			cout<<"completed thread "<<threads[i]->get_id()<<endl;
			threads[i]->join();
		} 
	}
}

// Wait on barrier on all threads
void ThreadManager::barrier() {
	// Loop on all vector thread and block until terminated
	//for ( int i = 0 ; i < threads.size();i++) threads[i]->waitForRunToFinish();
}

// Destructor
ThreadManager::~ThreadManager() {
	// Loop on threads vector and delete all threads
	for ( int i = 0 ; i < threads.size();i++) delete (threads[i]);
	cout<<"destructed ThreadManager and all threads"<<endl;
}