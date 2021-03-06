#include "InferenceEngine.h"
#include "KnowledgeBase.h"
#include "RuleBase.h"
#include "Parser.h"
#include "ThreadManager.h"

// mutexes used
mutex fact_result_mtx;
mutex targ_returns;

// PRIVATE THREAD METHODS ----------------------------------------------
void threadFact(vector<string> member, int nparams, vector<string> p_vars, vector< map<string,string>> * result){
		//cout<<"thread function running"<<endl;
		if(nparams != member.size()) return; // if param numbers dont match, move to next fact in the kb

		map<string,string> param_map; 
		bool matches = true;

		//iterate through each queried param ($X, $Y, $Z)
		for(int i=0; i<nparams; i++){

			string curr = p_vars.at(i); //the current queried param ($X)
			string fact_item = member[i]; //the next item in curent fact

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
	// CRITICAL SECTION ------------------
		fact_result_mtx.lock();
		//if the fact has parameters that match the queried params ($X, $Y, $Z) add the map to the result
		if(matches){
			result->push_back(param_map);
		}
		fact_result_mtx.unlock();
	// CRITICAL SECTION END --------------
}

void threadAND(bool * ended, bool * isTrue, vector<vector<map<string,string>>> & p_targets, vector<int> * pos, map<string,string> * eval, int curr_target) {
	*isTrue = true;
	vector<map<string,string>> myMaps = p_targets[curr_target];
	int position = pos->at(curr_target);

	for(auto const &x : myMaps[position]){

		if(eval->count(x.first) == 0){
			eval->emplace(x.first, x.second);
		}else{
			if((eval->at(x.first)!=x.second)==1){
				*isTrue = false;
			}
		}
	}
	
	if(curr_target==p_targets.size()-1){
		int j = curr_target;
		while(j>=-1){

			if(j == -1){
				*ended = true;
				return;
			}

			pos->at(j) += 1;
			if(pos->at(j) == p_targets[j].size()){
				pos->at(j) = 0;
				j -= 1;
			}else{
				return;
			}
		}
	}
	return;
}

void InferenceEngine::threadRule(vector<vector<string>> * targets, vector<vector<map<string,string>>> * target_returns, int curr_target) {
	string name = targets->at(curr_target).at(0);
	targets->at(curr_target).erase(targets->at(curr_target).begin());
		
	//infer target fact
	if(kb->check(name)){
			
		vector<map<string,string>> t = inferenceFact(name, (*targets).at(curr_target));
		
		targ_returns.lock();
		target_returns->push_back(t);
		targ_returns.unlock();
			
			
		
	}
	//infer target rule
	if(rb->check(name)){
		
		vector<map<string,string>> t2 = inferenceRule(name, (*targets).at(curr_target));
		t2.erase(t2.begin());
		
		targ_returns.lock();
		target_returns->push_back(t2);
		targ_returns.unlock();
	}
}

InferenceEngine::InferenceEngine(){
	//cout<<"construct InferenceEngine\n";
	kb = new KnowledgeBase();
	rb = new RuleBase();
	
	//Fill map with all SRI commands
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
	//cout<<"destruct InferenceEngine\n";
}

string InferenceEngine::processLine(stringstream & p_ss){
	string action = ""; //the command entered (RULE, DUMP, etc)
	string body = ""; //the actual line of logic
	string rest = ""; //unimportant characters (like comments)
	
	getline(p_ss, action, ' ');

	if(action == "LOAD"){
		while(getline(p_ss, rest)){
			body += rest + "\n";
		}
	}else{
		getline(p_ss, rest, '#'); //ignore comments
		stringstream newStream(rest);
		getline(newStream, body);
	}
	
	
	//cout<<body<<endl;

	string retString;

	//check for incorrect command
	InEnMFP func = funcMap[action];
	if(func!=NULL){
		retString = (this->*func)(body); //call mapped function
	}else{
		cout<<"Could not process that instruction"<<endl;
		retString = "Could not process that instruction";
	}
	return retString;
}

string InferenceEngine::processFact(string p_string){
	//cout<<"added fact "<<p_string<<endl;
	
	//parse fact string
	vector<string> fact = p->processFact(p_string);
	
	//add to kb
	kb->add(fact);
	return "Added Fact";
}

string InferenceEngine::processRule(string p_string){
	//cout<<"added rule "<<p_string<<endl;
	
	//parse rule string
	map<string, vector<string>> rule = p->processRule(p_string);
	
	//add to rb
	rb->add(rule);
	return "Added Rule";
}

string InferenceEngine::processLoad(string p_string){
	//cout<<"Inference processing Load"<<endl;
	
	/*read in file
	ifstream readFile(p_string);
	string line;
	
	//process each line and execute command
	while(getline(readFile, line)){
		stringstream iss(line);
		processLine(iss);
	}*/
	//cout<<p_string<<endl;
	stringstream news(p_string);
	string line;
	while(getline(news, line)){
		stringstream iss(line);
		cout<<line<<endl;
		processLine(iss);
	}

	return "Processed Load";

}

string InferenceEngine::processDump(string p_string){
	//cout<<"Inference processing Dump"<<endl;
	
	//create file named p_string
	//ofstream outputFile;
	//outputFile.open(p_string);
	
	//load facts and rules from rb and kb
	vector<vector<string>> facts;
	vector<map<string, vector<string>>> rules;
	facts = kb->getFacts();
	rules = rb->getRules();
	
	stringstream news;

	//interate through facts and write
	for(int i=0; i<facts.size(); i++){
		vector<string> th = facts[i];
		string fact = genFact(th);
		news<<fact<<endl;
		//if(p_string=="") cout<<fact<<endl; //if no file given print to cout
		//else outputFile<<fact<<endl; //write to file
	}
	
	//iterate through rules and write
	for(int i=0; i<rules.size(); i++){
		map<string, vector<string>> th = rules[i];
		//vector<string> th = rules[i];
		string rule = genRule(th);
		news<<rule<<endl;
		//if(p_string=="") cout<<rule<<endl; //if no file given print to cout
		//else outputFile<<rule<<endl; //write to file
	}
	return news.str();
	//outputFile.close();
}

//INFERENCE------------------------------------------------------------------------------
string InferenceEngine::processInference(string p_string){
	//cout<<"Inference processing Inference"<<endl;
	//Thread * thread = new Thread()
	vector<string> query = p->processInference(p_string);
	string name = query[0];
	query.erase(query.begin());

	string outfact = "";
	stringstream newS(p_string);
	getline(newS,outfact,')');
	getline(newS,outfact, ' ');
	getline(newS,outfact);
	
	//cout<<"OUTPUT:"<<outfact<<":end"<<endl;

	//FACT INFERENCE
	if(kb->check(name)){
		// async not useful at this time, since future's immediately gotten
		//auto fut_r = async(&InferenceEngine::inferenceFact, this, name, std::ref(query));
		//vector<map<string,string>> result = fut_r.get();
		
		vector<map<string,string>> result = inferenceFact(name, query);
		
		stringstream news("");

		//print results of inference
		for(int r=0; r<result.size(); r++){
			for(int p=0; p<query.size(); p++){
				string par = query[p];
				news<<par<<": "<<result[r][par]<<"\t";
			}
			news<<endl;
		}

		return news.str();
	}
	
	//RULE INFERENCE
	if(rb->check(name)){
		// async not useful at this time, since future's immediately gotten
		//auto fut_rs = async(&InferenceEngine::inferenceRule, this, name, std::ref(query));
		//vector<map<string,string>> results = fut_rs.get();
		
		vector<map<string,string>> results = inferenceRule(name, query);
		
		stringstream news("");

		auto q = results[0];
		results.erase(results.begin());
		if(q["returned"] == "false"){
			cout<<"No rule found"<<endl;
			news<<"No rule found"<<endl;
			return news.str();
		}

		if(outfact == "" || outfact == " "){
			for(int i=0; i<results.size(); i++){
				for(int p=0; p<query.size(); p++){
					string par = query[p];
					cout<<par<<": "<<results[i][par]<<"\t";
					news<<par<<": "<<results[i][par]<<"\t";
				}
				cout<<endl;
				news<<endl;
			}
			return news.str();
		}else{
			// create new facts from results
			vector<string> fact;
			for(int i = 0; i < results.size(); i++) {
				fact.push_back(outfact);
				for(int p = 0; p<query.size(); p++) {
					string par = query[p];
					fact.push_back(results[i][par]);
				}
				kb->add(fact);
				fact.clear();
			}
			news<<"FACTS added with name: "<<outfact;
			return news.str();
		}
	}
}



vector<map<string,string>> InferenceEngine::inferenceFact(string p_name, vector<string> & p_vars){
	ThreadManager * thread_mgr = new ThreadManager();
	vector<vector<string>> members = kb->lookup(p_name); //get fact vector
	int nparams = p_vars.size(); //get num params that are being queried 
	vector< map<string,string>> result; 
		
	//iterate through all matching facts
	for(int fact = 0; fact<members.size(); fact++){
		
		// create a thread for each fact to check if they match the desired form concurrently
		thread_mgr->addThread(new thread(threadFact, members[fact], nparams, p_vars, &result));
		
	}
	thread_mgr->joinThreads();
	delete(thread_mgr);
	return result;
}



vector<map<string,string>> InferenceEngine::inferenceRule(string p_name, vector<string> & p_vars){
	ThreadManager * thread_mgr = new ThreadManager();
	
	vector<map<string,string>> result; //vector to return
	int s = p_vars.size();
	map<string, vector<string>> rule = findRule(p_name, s); //get the rule we want to use
	string ret = rule["returned"][0]; //ret = "false" if rule doesnt exist, "true" if it does

	map<string,string> vars;
	for(int i=0; i<p_vars.size(); i++){
		vars[p_vars[i]] = rule["vars"][i];
	}

	//make sure the calling function knows whether there actually is a rule for the one the user wants to inference
	if(ret == "false"){
		map<string,string> fa;
		fa["returned"] = "false";
		result.push_back(fa);
		return result;
	}
	
	//build target vector
	vector<vector<string>> targets;
	for(int i=1; i<rule["ts"].size()+1; i++){
		string target = "target"+to_string(i);
		vector<string> t = rule[target];
		targets.push_back(t);
	}
	
	//process the rule targets
	vector<vector<map<string,string>>> target_returns;
	for(int i=0; i<targets.size(); i++){
		// SHOULD DO THIS WITH THREADS
		thread_mgr->addThread(new thread(&InferenceEngine::threadRule, this, &targets, &target_returns, i));
	}
	
	thread_mgr->joinThreads();
	
	
	//Run logical operand on targets
	string op = rule["operand"][0];
	
	//AND inference
	if(op == "AND"){
		result = findAND(target_returns);
		
	//OR inference
	//use threads here?
	}else if(op == "OR"){
		for(int i = 0; i<target_returns.size(); i++){
			for(int j = 0; j<target_returns[i].size(); j++){
				//if(target_returns[i][j][""] != ){
					result.push_back(target_returns[i][j]);
				//}
			}
			
		}
		
	}
	
	map<string,string> fa;
	fa["returned"] = "true";
	result.insert(result.begin(), fa);
	delete(thread_mgr);
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
	ThreadManager * thread_mgr = new ThreadManager();
	vector<map<string,string>> result;
	vector<map<string,string>> first = p_targets[0];
	
	vector<int> pos(p_targets.size(), 0);
	bool ended = false;

	while(!ended){
		map<string,string> eval;
		bool isTrue;
		
		for(int i=0; i<p_targets.size(); i++){
			
			// create threads to evaluate AND concurrently
			thread_mgr->addThread(new thread(threadAND, &ended, &isTrue, std::ref(p_targets), &pos, &eval, i));
		}
		// thread join 
		thread_mgr->joinThreads();
				  
		if(isTrue == true){
			
			result.push_back(eval);
		}
	}
 	delete(thread_mgr);	
	return result;
}

string InferenceEngine::processDrop(string p_string){
	//check for matching fact
	if(kb->check(p_string)){
		kb->removeAll(p_string);
		cout<<"removed all FACTS with name "<<p_string<<endl;
	}else{
		cout<<"No FACTS of this name"<<endl;
	}
	
	stringstream news("");
	string str;

	//check for matching rule
	if(rb->check(p_string)){
		rb->removeAll(p_string);
		news<<"removed all RULES with name"<<p_string<<endl;
		cout<<"removed all RULES with name"<<p_string<<endl;
	}else{
		news<<"No RULES of this name"<<endl;
		cout<<"No RULES of this name"<<endl;
	}

	getline(news, str);
	return str;
}

string InferenceEngine::genFact(vector<string> p_strings){
	string ret = "";
	
	//write the FACT command string
	stringstream s_stream("FACT ", ios_base::in | ios_base::out);
	s_stream << "FACT "<< p_strings[0] << "(";
	int i;
	
	//write all params
	for(i=1; i<p_strings.size()-1; i++){
		string s = p_strings[i];
		s_stream<<s<<", ";
	}
	
	//close string and return
	string s = p_strings[i];
	s_stream<<s<<")";
	getline(s_stream, ret);
	
	return ret;
}

string InferenceEngine::genRule(map<string, vector<string>> p_rule){
	string ret = "";
	
	//write the RULE command string
	stringstream s_stream(ios_base::in | ios_base::out);
	s_stream<<"RULE "<<p_rule["name"][0]<<"(";
	
	//write all the var params
	int i;
	for(i=0; i<p_rule["vars"].size()-1; i++){
		s_stream<<p_rule["vars"][i]<<",";
	}
	
	//add the operand and :-
	s_stream<<p_rule["vars"][i]<<"):- "<<p_rule["operand"][0];
	
	//write all the targets
	for(int t=1; t<=p_rule["ts"].size(); t++){
		string target = "target"+to_string(t);
		s_stream<<" "<<p_rule[target][0]<<"(";
		//cout<<p_rule[target].size()<<endl;
		int j;
		for(j=1; j<p_rule[target].size()-1; j++){
			s_stream<<p_rule[target][j]<<",";
		}
		s_stream<<p_rule[target][j]<<")";
	}
	getline(s_stream, ret);
	
	return ret;
}