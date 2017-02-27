#include "common.h"

class Rule{
	private:
		string name; //name of rule
		bool rule_operator; //true=AND, false=OR
		vector<string> targets; //the fact targets the rule operates on.
	public:
		Rule(string n, bool ro, vector<string> t);
		~Rule();
		
		string getName();
		bool getOperator();
		
};