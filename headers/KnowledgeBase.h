#include "common.h"
#include "InfoBase.h"

class KnowledgeBase: public InfoBase{
	private:
		unordered_map< string, vector< vector<string> > > fact_map;
	public:
		// Constructors and Destructors ------------------------------
		KnowledgeBase();
		~KnowledgeBase();

		// Access Functions ------------------------------------------
		vector< vector<string> > lookup(string name);	// returns the vector mapped at "name"
		bool check(string name);			// true if fact with key "name" exists
		// Manipulation Functions ------------------------------------
		void add(string name, vector<string> targets);	// creates new fact with key "name" or appends targets to vector if "name" already mapped
		void remove(string name);			// deletes entry with key "name"

};