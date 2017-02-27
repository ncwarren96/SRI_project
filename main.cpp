#include "common.h"
#include "InfoBase.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"

void get_usr_in(InferenceEngine * p_i){
	while(true){
		string ch;
		getline(cin, ch);
		if(ch == "quit" || ch == "q"){
			break;
		}else if(ch == "print" || ch == "p"){
			//p_p->printLines();
		}else{
			stringstream newStream(ch);
			p_i->processLine(newStream);
			//vector<string> strs = p_p->processLine(newStream);
			//p_i->processLine(strs);
		}
	}
}

int main(int argc, char* argv[]){
	InferenceEngine *ie = new InferenceEngine();
	//Parser *p = new Parser();
	//RuleBase *rb = new RuleBase();
	
	if(argc > 1){
		for(int i=1; i<argc; i++){
			//vector<string> strs = p->processLoad(argv[i]);
			//ie->processLine(strs);
		}
	}
	
	get_usr_in(ie);
	
	delete(ie);
	//delete(p);
	//delete(rb);
	
	return 0;
}