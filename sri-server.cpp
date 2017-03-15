#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

int main(int argc, char* argv[]){

	//init server socker
	TCPServerSocket * server = new TCPServerSocket("0.0.0.0" , 9999, 100);
	server->initializeSocket();
	
	//get connected socket and init to recSock, with 20 sec timeout
	TCPSocket * recSock = server->getConnection();
	
	for(;;){
		char * buffer = new char[256];
		int nBytes = recSock->readFromSocket(buffer, 256);
		
		cout<<"num of bytes read: "<<nBytes<<endl;
		cout<<buffer<<endl;
		
		string ch(buffer);
		if(ch == "quit" || ch == "q"){
			break;
		}
	}
	
	//initialize the engine, then begine obtaining input
	InferenceEngine *ie = new InferenceEngine();
	//get_usr_in(ie);
	
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
	
	return 0;
}