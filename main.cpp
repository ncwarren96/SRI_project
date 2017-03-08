#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"

//helper function for initail processing of input
void get_usr_in(InferenceEngine * p_i){
	while(true){
		string ch;
		getline(cin, ch);
		
		//check for  quit
		if(ch == "quit" || ch == "q"){
			break;
			
		//otherwise send on to the inference engine
		}else{
			stringstream newStream(ch);
			p_i->processLine(newStream);
			//vector<string> strs = p_p->processLine(newStream);
			//p_i->processLine(strs);
		}
	}
}

void call_from_thread() {
	cout << "Hello, World" <<endl;
}

int main(int argc, char* argv[]){

	//thread t1(call_from_thread);
	ThreadManager * tm = new ThreadManager();
	//tm->addThread(thread(call_from_thread));
	thread * th1 = new thread(call_from_thread);
	thread * th2 = new thread(call_from_thread);
	thread * th3 = new thread(call_from_thread);
	tm->addThread(th1);
	tm->addThread(th2);
	tm->addThread(th3);
	
	tm->joinThreads();
	//Here's an example of declaring a new thread and manager and starting
	//not part of final code
	
	
	//initialize the engine, then begine obtaining input
	InferenceEngine *ie = new InferenceEngine();
	get_usr_in(ie);
	
	/*
	Parser *p = new Parser();
	RuleBase *rb = new RuleBase();
	
	if(argc > 1){
		for(int i=1; i<argc; i++){
			//vector<string> strs = p->processLoad(argv[i]);
			//ie->processLine(strs);
		}
	}
	*/
	
	delete(ie);
	delete(tm); //will also delete all threads
	
	return 0;
}