// ROUTING CLASS
#include "Dijkstra.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main (int argc, char *argv[])
{
	if (argc != 5) {
		cout << endl << "USAGE: ./routing <graph_filename> <ip_filename> <source_vertex> <destination_vertex>";
		exit(0);
	}


	Dijkstra D;
	int source = atoi(argv[3]);
    int dest = atoi(argv[4]);
	int numVertices, numEdges;

	// INITIALIZE THE NETWORK GRAPH
	D.Initialize(argv[1], source, numVertices, numEdges, dest);

	// READ THE IP ADDRESSES
	D.LoadIP(argv[2]);

	/* INTIALIZE THE NODES
		*  FIND NEXT HOP
		*  CONSTRUCT ROUTING TABLE AT EACH NODE
		*  CONSTRUCT TRIE AT EACH NODE
	*/
	for (int i = 0; i < numVertices; ++i) {
		if (D.InitializeNode(i, numVertices-1) == -1);
			//cout << endl << "No Next Hop Found!" << endl;
	}


	// ONCE THE NETWORK GRAPH HAS BEEN INITIALIZED, FIND OUT THE LONGEST MATCHING
	// PREFIX TO REACH FROM THE SOURCE TO THE DESTINATION
	D.FindRoute(source, dest);

	return 0;
}