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
		vector< vector<string> > lookup(string name);	// returns vector where first entry is operation and following are targets
		bool check(string name);			// true if rule with key "name" exists
		// Manipulation Functions ------------------------------------
		void add(string name, vector<string> targets);	// adds new rule w/ key "name"; if rule "name" already exists and targets is not a duplicate, appends targets. 
		void remove(string name);	// removes rule "name"
};