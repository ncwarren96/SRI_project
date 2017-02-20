SOURCES=./sources
SOURCESLIST=$(SOURCES)/InferenceEngine.cpp $(SOURCES)/InfoBase.cpp $(SOURCES)/KnowledgeBase.cpp $(SOURCES)/RuleBase.cpp /sources/Parse.cpp 
HEADERS=./headers
OBJECTS=./objects
EXEC = sri
GCC=g++
DEBUG= -g
INCLUDES= -I $(HEADERS)
GCC_FLAGS= -std=c++11

$(EXEC): $(OBJECTS)/main.o $(OBJECTS)/InfoBase.o
	$(GCC) $(OBJECTS)/main.o $(OBJECTS)/InfoBase.o -o $(EXEC)

clean:
	rm -rt $(EXEC)/*$(OBJECTS)*/

$(OBJECTS)/InferenceEngine.o: $(SOURCES)/InferenceEngine.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/InferenceEngine.cpp -o $(OBJECTS)/InferenceEngine.o

$(OBJECTS)/Parser.o: $(SOURCES)/Parser.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Parser.cpp -o $(OBJECTS)/Parser.o

$(OBJECTS)/InfoBase.o: $(SOURCES)/InfoBase.cpp
	$(GCC) -c $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/InfoBase.cpp -o $(OBJECTS)/InfoBase.o

$(OBJECTS)/RuleBase.o: $(SOURCES)/RuleBase.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/RuleBase.cpp -o $(OBJECTS)/RuleBase.o

$(OBJECTS)/KnowledgeBase.o: $(SOURCES)/KnowledgeBase.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/KnowledgeBase.cpp -o $(OBJECTS)/KnowledgeBase.o
	
$(OBJECTS)/main.o: main.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) main.cpp -o $(OBJECTS)/main.o