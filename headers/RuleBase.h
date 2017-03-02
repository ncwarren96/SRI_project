#include "common.h"

class RuleBase{
	private:
		map< string, vector<map<string, vector<string>>>> rule_map;
	public:
		// Constructors and Destructors ------------------------------------------------------
		RuleBase();
		~RuleBase();
	
		// Access Functions ------------------------------------------------------------------
		vector<map<string, vector<string>>> lookup(string name); // returns the rule "name"
		bool check(string name);	// true if rule "name" exists
		int numRules();	// number of rules in the rule base
	
		// Manipulation Functions ------------------------------------------------------------
		void add(map<string, vector<string>> data);
		void removeAll(string name);	// deletes ENTIRE entry with key "name"
		void remove(map<string, vector<string>> data);	// delete specific rule, where data.begin = name of rule
	
		vector<map<string, vector<string>>> getRules(); // returns all the rules in the rule base
};