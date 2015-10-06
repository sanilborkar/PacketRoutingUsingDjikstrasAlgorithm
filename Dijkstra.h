// DIJKSTRA'S SSP ALGO HEADER FILE
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "FibHeap.h"
#include "FibNode.h"
#include <map>
#include <vector>

typedef struct Edge Edge;

struct Edge
{
    int startVertex;
    int endVertex;
    int weight;    
};


class Dijkstra {
public:
    FibHeap FHeap;
    
    long int n;     // #VERTICES
    int m;          // #EDGES

    std::vector<Node*> vertices;
    //std::vector<Edge*> edges;

    // HASH-MAP WITH <key, value> = <VERTEX_NO, IP_ADDR_IN_BINARY>
    std::map<int, string> mNodeToIP;

    Dijkstra();
    ~Dijkstra();

    bool Initialize(char* filename, int srcVertex, int &V, int &E, int destVertex);

    /* FIND THE SHORTEST PATH USING DIJKSTRA'S ALGO
        INPUT: SOURCE VERTEX, DEST VERTEX, REFERENCE TO A VECTOR THAT WILL CONTAIN THE SHORTEST PATH FOUND
        OUTPUT: THE SHORTEST PATH DISTANCE
        RETURN VALUE: SHORTEST PATH FROM SOURCE TO DESTINATION (verticesOnSP)
    */
    int FindSSP(int source, int dest, std::vector<int> &verticesOnSP);

    void LoadIP(char* filename);

    /* FIND THE NEXT HOP FROM SOURCE TO DESTINATION USING SHORTEST PATH DIJKSTRA'S ALGO
        INPUT: SOURCE VERTEX, DEST VERTEX
        RETURN VALUE: NEXT HOP VERTEX NUMBER FROM SOURCE ON THE SHORTEST PATH FROM TO DESTINATION
    */
    int InitializeNode (int source, int dest);

    // ONCE THE NETWORK GRAPH HAS BEEN INITIALIZED, FIND OUT THE LONGEST MATCHING
    // PREFIX TO REACH FROM THE SOURCE TO THE DESTINATION
    void FindRoute(int source, int dest);

    void BuildTrie (int source);

};

#endif