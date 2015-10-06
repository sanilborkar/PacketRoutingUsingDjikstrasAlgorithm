#include "FibHeap.h"
#include "FibNode.h"
#include "Dijkstra.h"

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <ctime>

using namespace std;

int main (int argc, char *argv[])
{
	if (argc != 4) {
		cout << endl << "USAGE: ./ssp <filename> <source_vertex> <destination_vertex>";
		exit(0);
	}

    int source = atoi(argv[2]);
    int dest = atoi(argv[3]);
    int numVertices, numEdges;

    Dijkstra D;
    D.Initialize (argv[1], source, numVertices, numEdges, atoi(argv[3]));

    std::vector<int> verticesOnSP;
    int shortestPath = D.FindSSP (source, dest, verticesOnSP);
    if (shortestPath != -1) {
        cout << shortestPath;
        cout << endl;
        
        for (int i = 0; i < verticesOnSP.size(); i++)
            cout << verticesOnSP[i] << " ";
    }
/*    else
        cout << endl << "No shortest path available from " << source << " to " << dest;*/

    cout << endl;
	return 0;
}