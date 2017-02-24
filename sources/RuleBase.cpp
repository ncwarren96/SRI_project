#include "RuleBase.h"

// Constructors and Destructors --------------------------------------------
RuleBase::RuleBase(){
	cout<<"contructed RuleBase\n";
}

RuleBase::~RuleBase(){
	cout<<"destructed RuleBase\n";
}

// Access Functions --------------------------------------------------------
vector< vector<string> > RuleBase::lookup(string name){
	if( rule_map.count(name) == 0 ) {
		cout << "Invalid rule name: " << name << endl;
		exit(0);
	}
	return (rule_map[name]);
}

bool RuleBase::check(string name){
	if( rule_map.count(name) == 0) {
		return false;
	} else {
		return true;
	}
}

// Manipulation Functions --------------------------------------------------
void RuleBase::add(vector<string> data){
	string name = data.front();	// store first element as name
	data.erase(data.begin());	// delete first element
	
	vector< vector<string> > container;	// create 2D vector for emplace()
	container.push_back(data);	// add data to the 2D vector container
	
	auto wasAdded = rule_map.emplace(name, container);	// attempt to create new map entry w/ key "name"
	
	if( wasAdded.second == false ) {	//if emplace failed due to duplicate key
		(*wasAdded.first).second.push_back(data);	//add targets to the vector at key "name" 
	}
}

void RuleBase::remove(string name){
	rule_map.erase(name);
}