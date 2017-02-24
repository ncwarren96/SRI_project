#include "common.h"
//#include "KnowledgeBase.h"


class InferenceEngine{
	private:
		//KnowledgeBase * kb;
		//RuleBase * rb;
	
	public:
		InferenceEngine();
		~InferenceEngine();
		
		void add(vector<string> line);
};