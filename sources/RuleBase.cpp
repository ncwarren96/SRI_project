#include "RuleBase.h"

RuleBase::RuleBase(){
	cout<<"contructed RuleBase\n";
}

RuleBase::~RuleBase(){
	cout<<"destructed RuleBase\n";
}

vector< vector<string> > RuleBase::lookup(string name){
	return vector<vector<string>>();
}

bool RuleBase::check(string name){
	return true;
}

void RuleBase::add(string name, vector<string> targets){

}

void RuleBase::remove(string name){

}