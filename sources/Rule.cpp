#include "common.h"
#include "Rule.h"

Rule::Rule(string n, bool ro, vector<string> t){
	cout<<"creating new rule "<<n<<endl;
	
	name = n;
	rule_operator = ro;
	targets = t;
	
	
}

string Rule::getName(){
	return name;
}

bool Rule::getOperator(){
	return rule_operator;
}


