#include "InferenceEngine.h"
#include "KnowledgeBase.h"
#include "RuleBase.h"
#include "Parser.h"

InferenceEngine::InferenceEngine(){
	cout<<"construct InferenceEngine\n";
	kb = new KnowledgeBase();
	rb = new RuleBase();
	
	funcMap.insert(make_pair("FACT", &InferenceEngine::processFact));
	funcMap.insert(make_pair("RULE", &InferenceEngine::processRule));
	funcMap.insert(make_pair("LOAD", &InferenceEngine::processLoad));
	funcMap.insert(make_pair("DUMP", &InferenceEngine::processDump));
	funcMap.insert(make_pair("INFERENCE", &InferenceEngine::processInference));
	funcMap.insert(make_pair("DROP", &InferenceEngine::processDrop));
}

InferenceEngine::~InferenceEngine(){
	delete(kb);
	delete(rb);
	delete(p);
	cout<<"destruct InferenceEngine\n";
}

void InferenceEngine::processLine(stringstream & p_ss){
	string action = ""; //the command entered (RULE, DUMP, etc)
	string body = ""; //the actual line of logic
	string rest = ""; //unimportant characters (like comments)
	
	getline(p_ss, action, ' ');
	getline(p_ss, rest, '#');
	stringstream newStream(rest);
	getline(newStream, body);
	
	InEnMFP func = funcMap[action];
	(this->*func)(body);
}

void InferenceEngine::processFact(string p_string){
	cout<<"added fact "<<p_string<<endl;
	vector<string> fact = p->processFact(p_string);
	kb->add(fact);
}

void InferenceEngine::processRule(string p_string){
	cout<<"added rule "<<p_string<<endl;
	map<string, vector<string>> rule = p->processRule(p_string);
	//rb->add(rule);
}

void InferenceEngine::processLoad(string p_string){
	cout<<"Inference processing Load"<<endl;
	ifstream readFile(p_string);
	string line;
	while(getline(readFile, line)){
		stringstream iss(line);
		processLine(iss);
	}
}

void InferenceEngine::processDump(string p_string){
	cout<<"Inference processing Dump"<<endl;
	ofstream outputFile;
	outputFile.open(p_string);
	vector<vector<string>> facts, rules;
	facts = kb->getFacts();
	rules = rb->getRules();
	for(int i=0; i<facts.size(); i++){
		vector<string> th = facts[i];
		string fact = genFact(th);
		if(p_string=="") cout<<fact<<endl;
		else outputFile<<fact<<endl;
	}
	for(int i=0; i<rules.size(); i++){
		vector<string> th = rules[i];
		string rule = genRule(th);
		if(p_string=="") cout<<rule<<endl;
		else outputFile<<rule<<endl;
	}
	outputFile.close();
}

void InferenceEngine::processInference(string p_string){
	cout<<"Inference processing Inference"<<endl;
	vector<string> ret = p->processInference(p_string);
	string name;
	stringstream newStream(p_string);
	getline(newStream, name, '(');
	string vars;
	//while(getline(newStream, vars, ','));
	if(kb->check(name)){
		vector<string> members;
		//members = kb->lookup(name);
		for(int i=0; i<kb->lookup(name).size(); i++){
			//members = kb->lookup(name)[i];
			cout<<kb->lookup(name)[i][0]<<endl;
		}
	}
	if(rb->check(p_string)){
		vector<vector<string>> rules = rb->lookup(p_string);
		for(int i; i<rules.size(); i++){
			for(int j; j<rules[i].size(); j++){
				cout<<rules[i][j]<<endl;
			}
		}
		cout<<"inf rule"<<endl;
	}
}

void InferenceEngine::processDrop(string p_string){
	if(kb->check(p_string)){
		kb->removeAll(p_string);
		cout<<"removed all FACTS with name "<<p_string<<endl;
	}else{
		cout<<"No FACTS of this name"<<endl;
	}
	if(rb->check(p_string)){
		rb->removeAll(p_string);
		cout<<"removed all RULES with name"<<p_string<<endl;
	}else{
		cout<<"No RULES of this name"<<endl;
	}
}

string InferenceEngine::genFact(vector<string> p_strings){
	string ret = "";
	stringstream s_stream("", ios_base::in | ios_base::out);
	s_stream << "FACT "<< p_strings[0] << "(";
	int i;
	for(i=1; i<p_strings.size()-1; i++){
		string s = p_strings[i];
		s_stream<<s<<", ";
	}
	string s = p_strings[i];
	s_stream<<s<<")";
	getline(s_stream, ret);
	return ret;
}

string InferenceEngine::genRule(vector<string> p_strings){
	string ret = "";
	stringstream s_stream("", ios_base::in | ios_base::out);
	s_stream << "RULE " << p_strings[0] << ":- ";
	s_stream << p_strings[1] << " ";
	int i;
	for(i=2; i<p_strings.size(); i++){
		string s = p_strings[i]; 
		s_stream<<s<<" ";
	}
	getline(s_stream, ret);
	return ret;
}