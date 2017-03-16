#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

<<<<<<< HEAD

void connectionThread(TCPSocket * recSock) {
	InferenceEngine *ie = new InferenceEngine();
=======
void connectionThread(TCPSocket * recSock) {
	// handles individual client connections
>>>>>>> origin/master
	
	for(;;){
		char * buffer = new char[256];
		int nBytes = recSock->readFromSocket(buffer, 256);
		
		cout<<"num of bytes read: "<<nBytes<<endl;
		cout<<buffer<<endl;
		
		string ch(buffer);
		if(ch == "quit" || ch == "q"){
			break;
		}else{
			stringstream newStream(ch);
			ie->processLine(newStream);
			//vector<string> strs = p_p->processLine(newStream);
			//p_i->processLine(strs);
		}
	}
	
	//initialize the engine, then begine obtaining input
<<<<<<< HEAD

	//IS THE FOLLOWING NECESSARY?
	/* 
=======
	//InferenceEngine *ie = new InferenceEngine();
	//get_usr_in(ie);
	
	/*
>>>>>>> origin/master
	Parser *p = new Parser();
	RuleBase *rb = new RuleBase();
	
	if(argc > 1){
		for(int i=1; i<argc; i++){
			//vector<string> strs = p->processLoad(argv[i]);
			//ie->processLine(strs);
		}
	}
	*/
}

int main(int argc, char* argv[]){

	//init server socker
	TCPServerSocket * server = new TCPServerSocket(INADDR_ANY, 9999, 100);
	server->initializeSocket();
	
	
	for(;;) {
		//get connected socket and init to recSock, with 30 sec timeout
		//TCPSocket * recSock = server->getConnection(30,1);
		
		// get connected socket and init to recSock, in blocking mode
		TCPSocket * recSock = server->getConnection(0,0);
		
		if(recSock == NULL) break; // error occured, break the loop
		thread * th = new thread(connectionThread, recSock);
		th->detach(); // detach thread so it runs independantly
	}
	
	delete(server);
	//delete(ie);
	
	return 0;
}