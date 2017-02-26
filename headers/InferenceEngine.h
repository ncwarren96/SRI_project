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
		void processInference(string p_string);
		void processDrop(string p_string);
		
		string genFact(vector<string> p_strings);
		string genRule(vector<string> p_strings);
};