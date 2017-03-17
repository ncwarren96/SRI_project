#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"



void connectionThread(TCPSocket * recSock) {
	// handles individual client connections

	
	InferenceEngine * ie = new InferenceEngine();

	string t = "hi";
	for(;;){
		char * buffer = new char[256];
		const char * c;
		int nBytes = recSock->readFromSocket(buffer, 256);
		
		string retString;

		string ch(buffer);
		cout<<buffer<<endl;
		if(ch == "quit" || ch == "q"){
			break;
		}else{
<<<<<<< HEAD
			cout<<ch<<endl;
			stringstream newStream(ch);
			retString = ie->processLine(newStream);
=======
			stringstream newStream(ch);
			ie->processLine(newStream);
			//vector<string> strs = p_p->processLine(newStream);
			//p_i->processLine(strs);
>>>>>>> 0809bcd5547db0c2eefad6d6eafb9bbe65f3b08e
		}
		/*if(t == retString){
			break;
		}*/
		t = retString;
		c = t.c_str();
		recSock->writeToSocket(c, strlen(c));
	}
	
<<<<<<< HEAD
	delete(ie);
=======
	//initialize the engine, then begine obtaining input


	//IS THE FOLLOWING NECESSARY?
	/* 

	//InferenceEngine *ie = new InferenceEngine();
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
>>>>>>> 0809bcd5547db0c2eefad6d6eafb9bbe65f3b08e
}

int main(int argc, char* argv[]){

	//init server socker
	TCPServerSocket * server = new TCPServerSocket("0.0.0.0", 9999, 100);
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