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

//INFERENCE------------------------------------------------------------------------------
void InferenceEngine::processInference(string p_string){
	cout<<"Inference processing Inference"<<endl;
	vector<string> query = p->processInference(p_string);
	string name = query[0];
	query.erase(query.begin());

	string outfact = "";
	stringstream newS(p_string);
	getline(newS,outfact,')');
	getline(newS,outfact, ' ');
	getline(newS,outfact);
	
	cout<<"OUTPUT:"<<outfact<<":end"<<endl;

	//FACT INFERENCE
	if(kb->check(name)){
		vector<map<string,string>> result = inferenceFact(name, query);

		//print results of inference
		for(int r=0; r<result.size(); r++){
			for(int p=0; p<query.size(); p++){
				string par = query[p];
				cout<<par<<": "<<result[r][par]<<"\t";
			}
			cout<<endl;
		}
	}
	
	//RULE INFERENCE
	if(rb->check(name)){
		vector<map<string,string>> results = inferenceRule(name, query);
		auto q = results[0];
		results.erase(results.begin());
		if(q["returned"] == "false"){
			cout<<"No rule found"<<endl;
			return;
		}

		for(int i=0; i<results.size(); i++){
			for(int p=0; p<query.size(); p++){
				string par = query[p];
				cout<<par<<": "<<results[i][par]<<"\t";
			}
			cout<<endl;
		}
		cout<<"inf rule"<<endl;
	}
}

vector<map<string,string>> InferenceEngine::inferenceFact(string p_name, vector<string> & p_vars){
	
	vector<vector<string>> members = kb->lookup(p_name); //get fact vector
	int nparams = p_vars.size(); //get num params that are being queried 
	vector< map<string,string>> result; //NEEDS TO BE INITIALIZED, THIS CAUSES SEG FAULT
		
		
	//iterate through all matching facts
	for(int fact = 0; fact<members.size(); fact++){
			
		if(nparams != members[fact].size()) continue; // if param numbers dont match, move to next fact in the kb

		map<string,string> param_map; 
		bool matches = true;;

		//iterate through each queried param ($X, $Y, $Z)
		for(int i=0; i<nparams; i++){

			string curr = p_vars[i]; //the current queried param ($X)
			string fact_item = members[fact][i]; //the next item in curent fact

			//check if curr has been mapped
			if(param_map.find(curr) == param_map.end()){

				//if not mapped, map to next rule param
				param_map[curr] = fact_item;
			}else{

				//check if curr is same as the mapped item
				if(param_map[curr] != fact_item){
					matches = false;
					break; //the fact does not match query
				}
			}
		}

		//if the fact has parameters that match the queried params ($X, $Y, $Z) add the map to the result
		if(matches){
			result.push_back(param_map);
		}
	}
	return result;
}

vector<map<string,string>> InferenceEngine::inferenceRule(string p_name, vector<string> & p_vars){
	vector<map<string,string>> result; //vector to return
	map<string, vector<string>> rule = findRule(p_name, p_vars.size()); //get the rule we want to use
	string ret = rule["returned"][0]; //ret = "false" if rule doesnt exist, "true" if it does
	
	//make sure the calling function knows whether there actually is a rule for the one the user wants to inference
	if(ret == "false"){
		map<string,string> fa;
		fa["returned"] = "false";
		result.push_back(fa);
		return result;
	}else{
		
	}

	vector<vector<string>> targets;
	for(int i=1; i<rule["ts"].size()+1; i++){
		string target = "target"+to_string(i);
		vector<string> t = rule[target];
		targets.push_back(t);
	}

	vector<vector<map<string,string>>> target_returns;
	for(int i=0; i<targets.size(); i++){
		string name = targets[i][0];
		targets[i].erase(targets[i].begin());
		if(kb->check(name)){
			vector<map<string,string>> t = inferenceFact(name, targets[i]);
			target_returns.push_back(t);
		}else if(rb->check(name)){
			vector<map<string,string>> t = inferenceRule(name, targets[i]);
			target_returns.push_back(t);
		}
	}

	string op = rule["operand"][0];

	if(op == "AND"){
		result = findAND(target_returns);
	}else if(op == "OR"){
		//result = findOR(target_returns);
	}

	//result = findAND(target_returns);
	map<string,string> fa;
	fa["returned"] = "true";
	result.insert(result.begin(), fa);
	return result;
}

map<string, vector<string>> InferenceEngine::findRule(string p_name, int p_size){
	vector<map<string, vector<string>>> rules = rb->lookup(p_name);
	map<string, vector<string>> rule;

	for(int i=0; i<rules.size(); i++){
		rule = rules[i];
		if(rule["vars"].size() == p_size){
			rule["returned"].push_back("true");
			return rule;
		}
	}

	rule["returned"].push_back("false");
	return rule;
}

vector<map<string,string>> InferenceEngine::findAND(vector<vector<map<string,string>>> p_targets){
	vector<map<string,string>> result;
	vector<map<string,string>> first = p_targets[0];
	
	vector<int> pos(p_targets.size(), 0);
	bool ended = false;

	while(!ended){
		map<string,string> eval;
		bool isTrue = true;
		for(int i=0; i<p_targets.size(); i++){

			bool isTrue = true;
			vector<map<string,string>> myMaps = p_targets[i];
			int position = pos[i];

			for(auto const &x : myMaps[position]){
				if(eval.count(x.first) == 0){
					eval[x.first] = x.second;
				}else{
					if(eval[x.first] != x.second){
						isTrue = false;
					}
				}
			}

			if(i==p_targets.size()-1){
				int j=i;
				while(j>=-1){

					if(j == -1){
						ended = true;
						break;
					}

					pos[j] += 1;
					if(pos[j] == p_targets[j].size()){
						pos[j] = 0;
						j -= 1;
					}else{
						break;
					}
				}
			}
		}

		if(isTrue){
			result.push_back(eval);
		}
	}

	return result;
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
		s_stream<<p_rule["vars"][i]<<",";
	}
	s_stream<<p_rule["vars"][i]<<"):- "<<p_rule["operand"][0];

	for(int t=1; t<=p_rule["ts"].size(); t++){
		string target = "target"+to_string(t);
		s_stream<<" "<<p_rule[target][0]<<"(";
		cout<<p_rule[target].size()<<endl;
		int j;
		for(j=1; j<p_rule[target].size()-1; j++){
			s_stream<<p_rule[target][j]<<",";
		}
		s_stream<<p_rule[target][j]<<")";
	}
	
	getline(s_stream, ret);
	return ret;
}