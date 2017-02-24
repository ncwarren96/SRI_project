#include "common.h"
#include "InfoBase.h"

class KnowledgeBase: public InfoBase{
	private:
		unordered_map< string, vector<string> > fact_map;
	public:
		KnowledgeBase();
		~KnowledgeBase();
		vector<string> lookup(string name);
		bool check(string name);
		void add(string name, vector<string> targets);
		void remove(string name);

};