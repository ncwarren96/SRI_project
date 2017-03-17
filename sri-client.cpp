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
		}else if(ch == "LOAD"){

		}else{
			stringstream newStream(ch);
			p_i->processLine(newStream);
			//vector<string> strs = p_p->processLine(newStream);
			//p_i->processLine(strs);
		}
	}
}

string getLoad(string p_file){
	stringstream newStream("");
	newStream<<"LOAD ";

	ifstream readFile(p_file);
	string line;

	while(getline(readFile, line)){
		//cout<<line<<endl;
		newStream<<line<<endl;
	}
	//cout<<newStream.str()<<endl;
	return newStream.str();
}

void get_usr_(TCPSocket * p_socket){
	for(;;){
		string ch, file, head;
		getline(cin, ch);
		stringstream news(ch);
		getline(news, head, ' ');

		const char * c;
		char * buffer = new char[2048];

		if(ch == "quit" || ch == "q"){
			c = ch.c_str();
			p_socket->writeToSocket(c, strlen(c));
			break;

		}else if(head == "LOAD"){
			getline(news, file);
			string readFile = getLoad(file);
			c = readFile.c_str();
			//cout<<c<<endl;

		}else{
			c = ch.c_str();

		}
		p_socket->writeToSocket(c, strlen(c));
		int nBytes = p_socket->readFromSocket(buffer, 2048);
		string newString(buffer);
		cout<<newString<<endl;
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
	delete(socket);
	return 0;
}