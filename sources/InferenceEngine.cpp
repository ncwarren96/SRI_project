#include "InferenceEngine.h"

InferenceEngine::InferenceEngine(){
	std::cout<<"construct InferenceEngine\n";
	kb = new KnowledgeBase();
}

InferenceEngine::~InferenceEngine(){
	std::cout<<"destruct InferenceEngine\n";
}

void InferenceEngine::add(vector<string> line){
	string type = line[0];
	line.erase(line.begin());
	
	if(type == "fact") {
		
		//kb->add(line);//add fact
		
	}else if(type == "rule"){
		//add rule
	}
}