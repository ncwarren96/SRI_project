HEADERS=./headers
SOURCES=./sources
SOURCESLIST=$(SOURCES)/InferenceEngine.cpp $(SOURCES)/InfoBase.cpp $(SOURCES)/KnowledgeBase.cpp $(SOURCES)/RuleBase.cpp $(SOURCES)/Parser.cpp $(SOURCES)/Thread.cpp $(SOURCES)/ThreadManager.cpp
OBJECTS=./objects
OBJECTSLIST=$(OBJECTS)/main.o $(OBJECTS)/InferenceEngine.o $(OBJECTS)/Parser.o $(OBJECTS)/InfoBase.o $(OBJECTS)/KnowledgeBase.o $(OBJECTS)/RuleBase.o $(OBJECTS)/Thread.o $(OBJECTS)/ThreadManager.o
EXEC =sri
GCC=g++
DEBUG= -g
INCLUDES= -I $(HEADERS)
GCC_FLAGS= -std=c++11 -c 

$(EXEC): $(OBJECTSLIST)
	$(GCC) -pthread $(OBJECTSLIST) -o $(EXEC)

simple:	
	$(GCC) -std=c++11 $(INCLUDES) main.cpp $(SOURCESLIST) -o $(EXEC)
	
clean:
	rm -rf $(OBJECTS)/* $(EXEC)

$(OBJECTS)/main.o: main.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) main.cpp -o $(OBJECTS)/main.o

$(OBJECTS)/InferenceEngine.o: $(SOURCES)/InferenceEngine.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/InferenceEngine.cpp -o $(OBJECTS)/InferenceEngine.o

$(OBJECTS)/Parser.o: $(SOURCES)/Parser.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Parser.cpp -o $(OBJECTS)/Parser.o

$(OBJECTS)/InfoBase.o: $(SOURCES)/InfoBase.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/InfoBase.cpp -o $(OBJECTS)/InfoBase.o

$(OBJECTS)/RuleBase.o: $(SOURCES)/RuleBase.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/RuleBase.cpp -o $(OBJECTS)/RuleBase.o

$(OBJECTS)/KnowledgeBase.o: $(SOURCES)/KnowledgeBase.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/KnowledgeBase.cpp -o $(OBJECTS)/KnowledgeBase.o
	
$(OBJECTS)/Thread.o: $(SOURCES)/Thread.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Thread.cpp -o $(OBJECTS)/Thread.o

$(OBJECTS)/ThreadManager.o: $(SOURCES)/ThreadManager.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/ThreadManager.cpp -o $(OBJECTS)/ThreadManager.o