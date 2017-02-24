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
	
	return fact_map[name];
}

bool KnowledgeBase::check(string name) {
	if( fact_map.count(name) == 0) {
		return false;
	} else {
		return true;
	}
}

// Manipulation Functions -------------------------------------------------------
void KnowledgeBase::add(vector<string> data) {
	string name = data.front();	// store first element as name
	data.erase(data.begin());	// delete first element
	
	vector< vector<string> > container;	// create 2D vector for emplace()
	container.push_back(data);	// add data to the 2D vector container
	
	auto wasAdded = fact_map.emplace(name, container);	// attempt to create new map entry w/ key "name"
	
	if( wasAdded.second == false ) {	//if emplace failed due to duplicate key
		(*wasAdded.first).second.push_back(targets);	//add targets to the vector at key "name" 
	}
}

void KnowledgeBase::remove(string name) {
	fact_map.erase(name);
}