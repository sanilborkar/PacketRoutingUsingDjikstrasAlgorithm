CC = g++ -w -std=c++11

SRC_DIR = ./
BIN_DIR = ./

tag = -i

ifdef linux
tag = -n
endif

all: clean ssp routing

routing: FibHeap.o FibNode.o Dijkstra.o Routing.o BinTrie.o
	$(CC) -o $(BIN_DIR)routing $(BIN_DIR)FibHeap.o $(BIN_DIR)FibNode.o $(BIN_DIR)Dijkstra.o $(BIN_DIR)Routing.o $(BIN_DIR)BinTrie.o -g

ssp: FibHeap.o FibNode.o Dijkstra.o SSP.o BinTrie.o
	$(CC) -o $(BIN_DIR)ssp $(BIN_DIR)FibHeap.o $(BIN_DIR)FibNode.o $(BIN_DIR)Dijkstra.o $(BIN_DIR)SSP.o $(BIN_DIR)BinTrie.o -g

FibHeap.o: $(SRC_DIR)FibHeap.cc
	$(CC) -g -c $(SRC_DIR)FibHeap.cc -o $(BIN_DIR)FibHeap.o

FibNode.o: $(SRC_DIR)FibNode.cc
	$(CC) -g -c $(SRC_DIR)FibNode.cc -o $(BIN_DIR)FibNode.o

Dijkstra.o: $(SRC_DIR)Dijkstra.cc
	$(CC) -g -c $(SRC_DIR)Dijkstra.cc -o $(BIN_DIR)Dijkstra.o

SSP.o: $(SRC_DIR)SSP.cc
	$(CC) -g -c $(SRC_DIR)SSP.cc -o $(BIN_DIR)SSP.o

Routing.o: $(SRC_DIR)Routing.cc
	$(CC) -g -c $(SRC_DIR)Routing.cc -o $(BIN_DIR)Routing.o

BinTrie.o: $(SRC_DIR)BinTrie.cc
	$(CC) -g -c $(SRC_DIR)BinTrie.cc -o $(BIN_DIR)BinTrie.o

clean: 
	rm -f $(BIN_DIR)*.o
	rm -f $(BIN_DIR)*.out
	rm -f $(BIN_DIR)ssp
	rm -f $(BIN_DIR)routing