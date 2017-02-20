SOURCES=./sources
SOURCESLIST=$(SOURCES)/InferenceEngine.cpp $(SOURCES)/InfoBase.cpp $(SOURCES)/KnowledgeBase.cpp $(SOURCES)/RuleBase.cpp /sources/Parse.cpp 
HEADERS=./headers
OBJECTS=./objects
EXEC = sri
GCC=g++
DEBUG= -g
INCLUDES= -I $(HEADERS)
GCC_FLAGS= -std=c++11

$(EXEC): $(OBJECTS)/main.o $(OBJECTS)/InferenceEngine.o
	$(GCC) $(OBJECTS)/main.o -o $(EXEC)

clean:
	rm -rt $(EXEC)/*$(OBJECTS)*/
	
$(OBJECTS)/main.o: main.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) main.cpp -o $(OBJECTS)/main.o

$(OBJECTS)/InferenceEngine.o: $(SOURCES)/InferenceEngine.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUES) $(SOURCES)/InferenceEngine.cpp -o $(OBJECTS)/InferenceEngine.o