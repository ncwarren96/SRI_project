#include "common.h"
#include "InfoBase.h"

class RuleBase: public InfoBase{
	public:
		// Constructors and Destructors -----------------------------
		RuleBase();
		~RuleBase();
		// Access Functions ------------------------------------------
		virtual vector< vector<string> > lookup(string name);
		virtual bool check(string name);
		// Manipulation Functions ------------------------------------
		virtual void add(string name, vector<string> targets);
		virtual void remove(string name);
};