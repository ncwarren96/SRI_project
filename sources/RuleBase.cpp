#include "RuleBase.h"

// Constructors and Destructors --------------------------------------------
RuleBase::RuleBase(){
	cout<<"contructed RuleBase\n";
}

RuleBase::~RuleBase(){
	cout<<"destructed RuleBase\n";
}

// Access Functions --------------------------------------------------------
vector<map<string, vector<string>>> RuleBase::lookup(string name){
	if( rule_map.find(name) == rule_map.end() ) {
		cout << "Invalid rule name: " << name << endl;
		exit(0);
	}
	return (rule_map[name]);
}

bool RuleBase::check(string name){
	if( rule_map.find(name) == rule_map.end()) {
		return false;
	} else {
		return true;
	}
}

// Manipulation Functions --------------------------------------------------
void RuleBase::add(map<string, vector<string>> data){
	string name = data["name"][0];
	rule_map[name].push_back(data);
}


/*void RuleBase::add(vector<string> data){
	string name = data.front();	// store first element as name
	data.erase(data.begin());	// delete first element
	cout<<"Adding rule: "<<name<<endl;
	vector< vector<string> > container;	// create 2D vector for emplace()
	container.push_back(data);	// add data to the 2D vector container
	auto wasAdded = rule_map.emplace(name, container);	// attempt to create new map entry w/ key "name"
	
	if( wasAdded.second == false ) {	//if emplace failed due to duplicate key
		// check to be sure it's not a duplicate:
		if ( (std::find((*wasAdded.first).second.begin(), (*wasAdded.first).second.end(), data) == (*wasAdded.first).second.end())) {
			(*wasAdded.first).second.push_back(data);	// if not, add targets to the vector at key "name" 
		}
	}
}*/

void RuleBase::removeAll(string name){
	rule_map.erase(name);
}

void RuleBase::remove(map<string, vector<string>> data) {
	vector<string> temp = data.at("name");
	
	// look for item:
	auto it = std::find(rule_map.at(temp[0]).begin(), rule_map.at(temp[0]).end(), data);
	// if found:
	if ( it != rule_map.at(temp[0]).end()) {
		//std::cout << "found duplicate";
		rule_map.at(temp[0]).erase(it); // erase item
	
	}
}

vector<map<string, vector<string>>> RuleBase::getRules(){
	vector<map<string, vector<string>>> ret;
	for(pair<string, vector<map<string, vector<string>>>> element : rule_map){
		for(int i=0; i<element.second.size(); i++){
			map<string, vector<string>> rule = element.second[i];
			ret.push_back(rule);
		}
	}
	/*for(pair<string, vector<vector<string>>> element : rule_map ){
		for(int i=0; i<element.second.size(); i++){
			vector<string> rule = element.second[i];
			rule.insert(rule.begin(), element.first);
			ret.push_back(rule);
		}
	}*/
	return ret;
}

int RuleBase::numRules(){
	return rule_map.size();
}