#include "ThreadChild.h"

ThreadChild::ThreadChild(){
	
}

void * ThreadChild::threadMainBody(void * arg){
	cout<<"ran ThreadChild main body"<<endl;
}

ThreadChild::~ThreadChild(){
	
}