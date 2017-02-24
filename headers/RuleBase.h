#include "common.h"
#include "InfoBase.h"

class RuleBase: public InfoBase{
	private:
		unordered_map< string, vector< vector<string> > rule_map; 
	public:
		// Constructors and Destructors -----------------------------
		RuleBase();
		~RuleBase();
		// Access Functions ------------------------------------------
		virtual vector< vector<string> > lookup(string name);
		virtual bool check(string name);
		// Manipulation Functions ------------------------------------
		virtual void add(vector<string> data);
		virtual void remove(string name);
};