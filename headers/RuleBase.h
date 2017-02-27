#include "common.h"
#include "InfoBase.h"

class RuleBase: public InfoBase{
	private:
		unordered_map< string, vector< vector<string> > > rule_map;
	public:
		// Constructors and Destructors -----------------------------
		RuleBase();
		~RuleBase();
		// Access Functions ------------------------------------------
		virtual vector< vector<string> > lookup(string name);
		virtual bool check(string name);
		
		int numRules();
		// Manipulation Functions ------------------------------------
		virtual void add(vector<string> data);
		void removeAll(string name);	// deletes ENTIRE entry with key "name"
		void remove(vector<string> data);	// delete specific rule, where data.begin = name of rule
	
		vector<vector<string>> getRules();
};