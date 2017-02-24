#include "common.h"
#include "InfoBase.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"

void get_usr_in(Parser * p_p){
	while(true){
		string ch;
		getline(cin, ch);
		if(ch == "quit" || ch == "q"){
			break;
		}else if(ch == "print" || ch == "p"){
			p_p->printLines();
		}else{
			stringstream newStream(ch);
			stringstream newStream1(ch);
			p_p->processLine(newStream);
			p_p->addLine(newStream1);
		}
	}
}

int main(int argc, char* argv[]){

	InferenceEngine *ie = new InferenceEngine();
	Parser *p = new Parser();
	RuleBase *rb = new RuleBase();
	
	if(argc > 1){
		for(int i=1; i<argc; i++){
			p->processLoad(argv[i]);
		}
	}
	//p->printLines();
	// output "Hello, World!"
	//cout << "Hello, World!\n";
	// wait for an input from the user
	/*string ch;
	getline(cin, ch);
	cout << ch << endl;*/
	get_usr_in(p);
	
	delete(ie);
	delete(p);
	delete(rb);
	
	return 0;
}