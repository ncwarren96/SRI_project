#include "common.h"
#include "InfoBase.h"

class RuleBase: public InfoBase{
	public:
		// Constructors and Destructors -----------------------------
		RuleBase();
		~RuleBase();
		// Access Functions ------------------------------------------
		vector<string> lookup(string name);	// returns vector where first entry is operation and following are targets
		boolean check(string name);			// true if rule with key "name" exists
		// Manipulation Functions ------------------------------------
		void add(string name, vector<string> targets);	// adds new rule w/ key "name"; if rule "name" already exists, does nothing
		void remove(string name);			// removes rule with key "name"
};