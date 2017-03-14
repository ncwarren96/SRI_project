#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

int main(int argc, char* argv[]){


	TCPServerSocket * server = new TCPServerSocket(INADDR_ANY, 9999, 1);
	server->initializeSocket();
	TCPSocket * recSock = server->getConnection(20,1);
	char * buffer = new char[256];
	cout<<buffer<<endl;
	int nBytes = recSock->readFromSocket(buffer, 256);
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