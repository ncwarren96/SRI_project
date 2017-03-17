#include "common.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"
#include "ThreadManager.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

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

void dumpToFile(string p_fileName, string p_fileContents){
	ofstream outputFile;
	outputFile.open(p_fileName);
	outputFile<<p_fileContents;
	outputFile.close();
}

void get_usr_(TCPSocket * p_socket){
	for(;;){
		string ch, file, head;
		getline(cin, ch);
		stringstream news(ch);
		getline(news, head, ' ');

		const char * c;
		char * buffer = new char[1024];

		if(ch == "quit" || ch == "q"){
			c = ch.c_str();
			p_socket->writeToSocket(c, strlen(c));
			break;

		}else if(head == "LOAD"){
			getline(news, file);
			string readFile = getLoad(file);
			c = readFile.c_str();
			//cout<<c<<endl;

		}else if(head == "DUMP"){
			getline(news, file);
			c = head.c_str();

		}else{
			c = ch.c_str();

		}
		p_socket->writeToSocket(c, strlen(c));
		int nBytes = p_socket->readFromSocket(buffer, 1024);
		string newString(buffer);

		if(head == "DUMP"){
			if(file == "" || file == " "){
				cout<<newString<<endl;
			}else{
				dumpToFile(file, newString);
			}
		}else{
			cout<<newString<<endl;
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