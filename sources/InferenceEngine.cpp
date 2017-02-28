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
	rb->add(rule);
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
	vector<vector<string>> facts;
	vector<map<string, vector<string>>> rules;
	facts = kb->getFacts();
	rules = rb->getRules();
	for(int i=0; i<facts.size(); i++){
		vector<string> th = facts[i];
		string fact = genFact(th);
		if(p_string=="") cout<<fact<<endl;
		else outputFile<<fact<<endl;
	}
	for(int i=0; i<rules.size(); i++){
		map<string, vector<string>> th = rules[i];
		//vector<string> th = rules[i];
		string rule = genRule(th);
		if(p_string=="") cout<<rule<<endl;
		else outputFile<<rule<<endl;
	}
	outputFile.close();
}

void InferenceEngine::processInference(string p_string){
	cout<<"Inference processing Inference"<<endl;
	vector<string> query = p->processInference(p_string);
	string name = query[0];
	query.erase(query.begin());
	//FACT INFERENCE
	if(kb->check(name)){
		cout<<"inferenceing fact"<<endl;
		vector<vector<string>> members = kb->lookup(name); //get fact vector
		int nparams = query.size(); //get num params that are being queried
		vector< map<string,string>> result; //NEEDS TO BE INITIALIZED, THIS CAUSES SEG FAULT
		
		//iterate through all matching facts
		for(int fact = 0; fact<members.size(); fact++){
			
			//iterate through each queried param ($X, $Y, $Z)
			for(int i=0; i<nparams; i++){
				string curr = query[i]; //the current queried param ($X)
				map<string,string> param_map = result[fact]; //the map with current param as key ($X)
				string fact_item = members[fact][i]; //the next item in curent fact
				cout<<fact_item<<endl;
				//check if curr has been mapped
				/*if(param_map[curr] == ""){
					//if not mapped, map to next rule param
					param_map[curr] = fact_item;
				}else{
					//check if curr is same as the mapped item
					if(param_map[curr] != fact_item){
						break; //the fact does not match query
					}else{
						cout<<fact_item<<endl;
					}
				}*/
				//check if curr has been mapped
					
				//else
					
			}
		}
		
		//cout<<nparams<<endl;
		/*for(int i=0; i<members.size(); i++){
			if(nparams==members[i].size()){
				for(int j=0; j<nparams; j++){
					cout<<ret[j+1]<<": ";
					cout<<members[i][j]<<"\t";
				}
				cout<<endl;
			}
		}*/
	}
	
	//RULE INFERENCE
	if(rb->check(name)){
		vector<map<string, vector<string>>> rules = rb->lookup(name);
		map<string, vector<string>> rule;
		bool isrule = false;
		for(int i=0; i<rules.size(); i++){
			rule = rules[i];
			if(rule["vars"].size() != query.size()-1){
				continue;
			}else{
				isrule = true;
				break;
			}
		}
		if(isrule){
			cout<<"Found rule with "<<rule["vars"].size()<<" params"<<endl;
		}else{
			cout<<"No rule with "<<query.size()<<" params"<<endl;
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
	stringstream s_stream("FACT ", ios_base::in | ios_base::out);
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

string InferenceEngine::genRule(map<string, vector<string>> p_rule){
	string ret = "";
	stringstream s_stream(ios_base::in | ios_base::out);
	s_stream<<"RULE "<<p_rule["name"][0]<<"(";
	
	int i;
	for(i=0; i<p_rule["vars"].size()-1; i++){
		s_stream<<p_rule["vars"][i]<<", ";
	}
	s_stream<<p_rule["vars"][i]<<"):- "<<p_rule["operand"][0];
	
	i=1;
	string target = "target"+to_string(i);
	while(p_rule.find(target) != p_rule.end()){
		s_stream<<" "<<p_rule[target][0]<<"(";
		int j;
		for(j=1; j<p_rule[target].size()-1; j++){
			s_stream<<p_rule[target][j]<<",";
		}
		s_stream<<p_rule[target][j]<<")";
		i++;
		target = "target"+to_string(i);
	}
	
	getline(s_stream, ret);
	return ret;
}

/*string InferenceEngine::genRule(vector<string> p_strings){
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
}*/