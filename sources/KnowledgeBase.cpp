#include "KnowledgeBase.h"

// Constructors and Destructors ------------------------------------------------
KnowledgeBase::KnowledgeBase(){
	cout<<"constructed KnowledgeBase\n";
}

KnowledgeBase::~KnowledgeBase(){
	cout<<"destructed KnowledgeBase\n";
}

// Access Functions ------------------------------------------------------------
vector< vector<string> > KnowledgeBase::lookup(string name){
	if( fact_map.count(name) == 0) {
		cout << "Invalid fact name: " << name << endl;
		exit(0);
	}
	vector< vector<string> > temp = fact_map[name];
	return temp;
}

bool KnowledgeBase::check(string name) {
	if( fact_map.count(name) == 0) {
		return false;
	} else {
		return true;
	}
}

// Manipulation Functions -------------------------------------------------------
void KnowledgeBase::add(string name, vector<string> targets) {
	vector< vector<string> > container;
	container.push_back(targets);
	auto wasAdded = fact_map.emplace(name, container);
	
	if( wasAdded.second == false ) {	//if emplace failed due to duplicate key
		(*wasAdded.first).second.push_back(targets);	//add targets to the vector at key "name" 
	}
}

void KnowledgeBase::remove(string name) {
	fact_map.erase(name);
}