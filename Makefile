HEADERS=./headers
SOURCES=./sources
SOURCESLIST=$(SOURCES)/InferenceEngine.cpp $(SOURCES)/InfoBase.cpp $(SOURCES)/KnowledgeBase.cpp $(SOURCES)/RuleBase.cpp $(SOURCES)/Parser.cpp $(SOURCES)/ThreadManager.cpp $(SOURCES)/TCPSocket.cpp $(SOURCES)/TCPServerSocket.cpp
OBJECTS=./objects
OBJECTSLIST= $(OBJECTS)/InferenceEngine.o $(OBJECTS)/Parser.o $(OBJECTS)/InfoBase.o $(OBJECTS)/KnowledgeBase.o $(OBJECTS)/RuleBase.o $(OBJECTS)/ThreadManager.o $(OBJECTS)/TCPSocket.o $(OBJECTS)/TCPServerSocket.o
EXEC =sri
GCC=g++
DEBUG= -g
INCLUDES= -I $(HEADERS)
GCC_FLAGS= -std=c++11 -c 

$(EXEC): $(OBJECTSLIST) $(OBJECTS)/main.o
	$(GCC) -pthread $(OBJECTSLIST) $(OBJECTS)/main.o -o $(EXEC)
	
server:
	$(GCC) -std=c++11 -pthread $(INCLUDES) sri-server.cpp $(SOURCESLIST) -o sri-server
	
client:
	$(GCC) -std=c++11 -pthread $(INCLUDES) sri-client.cpp $(SOURCESLIST) -o sri-client
	
simple:	
	$(GCC) -std=c++11 -pthread $(INCLUDES) main.cpp $(SOURCESLIST) -o $(EXEC)
	
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
	
$(OBJECTS)/ThreadManager.o: $(SOURCES)/ThreadManager.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/ThreadManager.cpp -o $(OBJECTS)/ThreadManager.o

$(OBJECTS)/TCPSocket.o: $(SOURCES)/TCPSocket.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/TCPSocket.cpp -o $(OBJECTS)/TCPSocket.o
	
$(OBJECTS)/TCPServerSocket.o: $(SOURCES)/TCPServerSocket.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/TCPServerSocket.cpp -o $(OBJECTS)/TCPServerSocket.o