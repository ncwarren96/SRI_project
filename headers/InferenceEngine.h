#include "common.h"
//#include "KnowledgeBase.h"
class KnowledgeBase;
class RuleBase;
class Parser;

class InferenceEngine{
	private:
		typedef void (InferenceEngine::*InEnMFP)(string);
		map<string, InEnMFP> funcMap;	// function pointers
		KnowledgeBase * kb;
		RuleBase * rb;
		Parser * p;
		
		// thread class for processing rule targets
		void threadRule(vector<vector<string>> * targets, vector<vector<map<string,string>>> * target_returns, int curr_target);
			
	public:
		InferenceEngine();
		~InferenceEngine();
		
		void processLine(stringstream & p_ss); // processes instructions on line
		void processFact(string p_string); // processes and adds facts to KB
		void processRule(string p_string); // processes and adds facts to KB
		void processLoad(string p_string); // imports a .sri file
		void processDump(string p_string); // exports a .sri file
		vector<map<string,string>> inferenceFact(string p_name, vector<string> & p_vars); // perform inference on a fact
		vector<map<string,string>> inferenceRule(string p_name, vector<string> & p_vars); // perform inference on a rule
		map<string, vector<string>> findRule(string p_name, int p_size); // locates and returns a rule for inferencing
		vector<map<string,string>> findAND(vector<vector<map<string,string>>> p_targets); // performs AND operation
		vector<map<string,string>> findOR (vector<vector<map<string,string>>> p_targets); // performs OR operation
		void processInference(string p_string); // processes and executes an Inference
		void processDrop(string p_string); // perform a drop
		
		string genFact(vector<string> p_strings); // generates a string representing a fact
		string genRule(map<string, vector<string>> p_rule); // generates a string representing a rule
	
	
};