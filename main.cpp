#include "common.h"
#include "InfoBase.h"
#include "InferenceEngine.h"
#include "RuleBase.h"
#include "KnowledgeBase.h"
#include "Parser.h"

int main(int argc, char* argv[]){

	InferenceEngine *ie = new InferenceEngine();
	Parser *p = new Parser();
	RuleBase *rb = new RuleBase();
	string line = "";

	if(argc > 1){
		for(int i=1; i<argc; i++){
			ifstream readFile(argv[i]);
			while(getline(readFile,line)){
				stringstream newStream(line);
				stringstream newStream1(line);
				p->addLine(newStream);
				p->processLine(newStream1);
			}
		}
	}
	p->printLines();
	// output "Hello, World!"
	cout << "Hello, World!\n";
	// wait for an input from the user
	string ch;
	getline(cin, ch);
	cout << ch << endl;
	
	delete(ie);
	delete(p);
	delete(rb);
	
	return 0;
}