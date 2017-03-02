#include "RuleBase.h"

// Constructors and Destructors --------------------------------------------
RuleBase::RuleBase(){
	//cout<<"contructed RuleBase\n";
}

RuleBase::~RuleBase(){
	//cout<<"destructed RuleBase\n";
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

void RuleBase::removeAll(string name){
	rule_map.erase(name);
}

void RuleBase::remove(map<string, vector<string>> data) {
	vector<string> temp = data.at("name");
	
	// look for item:
	auto it = std::find(rule_map.at(temp[0]).begin(), rule_map.at(temp[0]).end(), data);
	// if found:
	if ( it != rule_map.at(temp[0]).end()) {
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
	return ret;
}

int RuleBase::numRules(){
	return rule_map.size();
}