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
	string action = "";
	string body = "";
	getline(p_ss, action, ' ');
	getline(p_ss, body, '#');
	InEnMFP func = funcMap[action];
	(this->*func)(body);
}

void InferenceEngine::processFact(string p_string){
	vector<string> fact = p->processFact(p_string);
	kb->add(fact);
	cout<<"Inference processing fact"<<endl;
}

void InferenceEngine::processRule(string p_string){
	vector<string> rule = p->processRule(p_string);
	rb->add(rule);
	cout<<"Inference processing rule"<<endl;
}

void InferenceEngine::processLoad(string p_string){
	ifstream readFile(p_string);
	string line;
	while(getline(readFile, line)){
		stringstream iss(line);
		processLine(iss);
	}
	cout<<"Inference processing Load"<<endl;
}

void InferenceEngine::processDump(string p_string){
	ofstream outputFile;
	outputFile.open(p_string);
	vector<vector<string>> facts, rules;
	facts = kb->getFacts();
	rules = rb->getRules();
	for(int i=0; i<facts.size(); i++){
		vector<string> th = facts[i];
		string fact = genFact(th);
		outputFile<<fact<<endl;
	}
	for(int i=0; i<rules.size(); i++){
		vector<string> th = rules[i];
		string rule = genRule(th);
		outputFile<<rule<<endl;
	}
	outputFile.close();
	cout<<"Inference processing Dump"<<endl;
}

void InferenceEngine::processInference(string p_string){
	cout<<"Inference processing Inference"<<endl;
}

void InferenceEngine::processDrop(string p_string){
	if(kb->check(p_string)){
		kb->remove(p_string);
	}else if(rb->check(p_string)){
		rb->remove(p_string);
	}else{
		cout<<"Nothing to remove"<<endl;
	}
	cout<<"Inference processing Drop"<<endl;
}

string InferenceEngine::genFact(vector<string> p_strings){
	string ret = "";
	stringstream s_stream("FACT ", ios_base::in | ios_base::out);
	s_stream << p_strings[0] << "(";
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
	stringstream s_stream("RULE ", ios_base::in | ios_base::out);
	s_stream << "RULE " << p_strings[0] << ":- ";
	s_stream << p_strings[1] << " ";
	int i;
	for(i=0; i<p_strings.size()-1; i++){
		string s = p_strings[i];
		s_stream<<s<<" ";
	}
	getline(s_stream, ret);
	return ret;
}