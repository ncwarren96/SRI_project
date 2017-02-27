#include "common.h"
#include "InfoBase.h"

class RuleBase{
	private:
		map< string, vector<map<string, vector<string>>>> rule_map;
	public:
		// Constructors and Destructors -----------------------------
		RuleBase();
		~RuleBase();
		// Access Functions ------------------------------------------
		vector<map<string, vector<string>>> lookup(string name);
		bool check(string name);
		
		int numRules();
		// Manipulation Functions ------------------------------------
		void add(map<string, vector<string>>);
		void removeAll(string name);	// deletes ENTIRE entry with key "name"
		void remove(vector<string> data);	// delete specific rule, where data.begin = name of rule
	
		vector<map<string, vector<string>>> getRules();
};