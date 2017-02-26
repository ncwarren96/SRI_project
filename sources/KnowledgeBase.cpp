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
		// check to be sure element is not a duplicate:
		if ( (std::find((*wasAdded.first).second.begin(), (*wasAdded.first).second.end(), data) == (*wasAdded.first).second.end())) {
			(*wasAdded.first).second.push_back(data);	// if not, add targets to the vector at key "name" 
		}
	}
}

void KnowledgeBase::removeAll(string name) {
	fact_map.erase(name);
}

void KnowledgeBase::remove(vector<string> data) {
	string name = data.front();	// store first element as name
	data.erase(data.begin());	// delete first element
	
	vector< vector<string> > container;	// create 2D vector for emplace()
	container.push_back(data);	// add data to the 2D vector container
	
	// look for item:
	auto it = std::find(fact_map.at(name).begin(), fact_map.at(name).end(), data);
	// if found:
	if ( it != fact_map.at(name).end()) {
		fact_map.at(name).erase(it); // erase item
	}
	
}

vector<vector<string>> KnowledgeBase::getFacts(){
	vector<vector<string>> ret;
	for(pair<string, vector<vector<string>>> element : fact_map ){
		for(int i=0; i<element.second.size(); i++){
			vector<string> fact = element.second[i];
			fact.insert(fact.begin(), element.first);
			ret.push_back(fact);
		}
	}
	return ret;
}
