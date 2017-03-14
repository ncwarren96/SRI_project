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
	TCPServerSocket * server = new TCPServerSocket(INADDR_ANY, 9999, 1);
	server->initializeSocket();
	
	//get connected socket and init to recSock, with 20 sec timeout
	TCPSocket * recSock = server->getConnection(20,1);
	
	//init buffer and read from the recieved socket
	char * buffer = new char[256];
	int nBytes = recSock->readFromSocket(buffer, 256);
	
	//print recieved data
	cout<<"num of bytes read: "<<nBytes<<endl;
	cout<<buffer<<endl;
	
	
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