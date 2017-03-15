#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

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

void get_usr_(TCPSocket * p_socket){
	for(;;){
		string ch;
		getline(cin, ch);
		
		const char * c;
		c = ch.c_str();
		p_socket->writeToSocket(c, strlen(c));
		if(ch == "quit" || ch == "q"){
			break;
		}
	}
}
	
	
int main(int argc, char* argv[]){
	
	if ( argc != 2) 
	{
		printf ("Usage: ./client <server-address>\n");
		exit(1);
	}
	
	//init socket with arg and port 9999
	TCPSocket * socket = new TCPSocket(argv[1], 9999);
	
	get_usr_(socket);
	
	return 0;
}