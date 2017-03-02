#include "common.h"
//#include "KnowledgeBase.h"
class KnowledgeBase;
class RuleBase;
class Parser;

class InferenceEngine{
	private:
		typedef void (InferenceEngine::*InEnMFP)(string);
		map<string, InEnMFP> funcMap;
		KnowledgeBase * kb;
		RuleBase * rb;
		Parser * p;
	
	
	public:
		InferenceEngine();
		~InferenceEngine();
		
		void processLine(stringstream & p_ss);
		void processFact(string p_string);
		void processRule(string p_string);
		void processLoad(string p_string);
		void processDump(string p_string);
		vector<map<string,string>> inferenceFact(string p_name, vector<string> & p_vars);
		vector<map<string,string>> inferenceRule(string p_name, vector<string> & p_vars);
		map<string, vector<string>> findRule(string p_name, int p_size);
		vector<map<string,string>> findAND(vector<vector<map<string,string>>> p_targets);
		vector<map<string,string>> findOR (vector<vector<map<string,string>>> p_targets);
		void processInference(string p_string);
		void processDrop(string p_string);
		
		string genFact(vector<string> p_strings);
		string genRule(map<string, vector<string>> p_rule);
};