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
#include <bitset>

using namespace std;

Dijkstra::Dijkstra () {

}

Dijkstra::~Dijkstra () {
    
}

bool Dijkstra::Initialize(char* filename, int srcVertex, int &V, int &E, int destVertex) {

    ifstream input;
    input.open(filename);

    string line;
    bool firstLine = true;
    int spacePos, i;
    int src, dst, wt;
    Node *source, *dest;
    Edge *e;

    // IF FILE HAS BEEN OPENED PROPERLY FOR READING
    if (input.is_open())
    {
        while (getline (input,line))
        {
            spacePos = line.find('\r');
            if(spacePos == 0)
                continue;

            if (line.empty())
                continue;

            /*spacePos = line.find("");
            if(spacePos == 0)
                continue;*/

            if (firstLine) {
                spacePos = line.find(' ');
                n = stoi(line.substr(0, spacePos));

                // IF SOURCE VERTEX ENTERED IS OUTSIDE THE RANGE
                if (destVertex > n - 1)
                    exit(0);

                for (i = 0; i < n; i++)
                    vertices.push_back(new Node(i, INT_MAX));
                

                m = stoi(line.substr(spacePos+1));
                firstLine = false;
            }

            // FOR THE FIRST LINE OF THE INPUT FILE
            // n m --> n = #vertices, and m = #edges
            else {

                // SOURCE VERTEX
                spacePos = line.find(' ');
                src = stoi(line.substr(0, spacePos));
                line = line.substr(spacePos+1);

                // DESTINATION VERTEX
                spacePos = line.find(' ');
                dst = stoi(line.substr(0, spacePos));
                line = line.substr(spacePos+1);
                
                // WEIGHT OF THE EDGE <SOURCE> - <DESTINATION>
                spacePos = line.find(' ');
                wt = stoi(line.substr(0, spacePos));
                
                /* 
                   * SINCE IT IS AN UNDIRECTED GRAPH, WE ADD BOTH THE EDGES AS SHOWN BELOW:
                        SOURCE -> DESTINATION = WEIGHT
                        SOURCE <- DESTINATION = WEIGHT
                   * IF WORKING WITH A DIRECTED GRAPH, WE NEED TO ADD ONLY 1 EDGE:
                        SOURCE -> DESTINATION = WEIGHT
                */
                source = vertices[src];
                dest = vertices[dst];
                source->AddtoAdjList(dest, wt);
                dest->AddtoAdjList(source, wt);

                /*// VECTOR OF EDGES
                e = new Edge;
                e->startVertex = src;
                e->endVertex = dst;
                e->weight = wt;
                edges.push_back(e);*/

            }
        }
    }
    else {
        cerr << "Unable to open file " << filename;
        exit(0) ;
    }       

    V = n;
    E = m;
    input.close();
}


int Dijkstra::FindSSP (int source, int dest, std::vector<int> &verticesOnSP) {

    int i;

    vertices[source]->data = 0;

  	const clock_t begin_time = clock();

  	// CREATE AN EMPTY FIB HEAP AND POPULATE IT
  	for (i = 0; i < n; i++) {        
        //cout << "\t" << vertices[i]->vNumber << " : " << vertices[i]->data;
  		FHeap.Insert(vertices[i]);
    }

    Node *u, *v;
    Node *d = NULL;
    int edgeWeight;
    while (!FHeap.IsEmpty()) {

        u = FHeap.RemoveMin();

        for (i = 0; i < u->adjList.size(); i++) {
            v = u->adjList[i]->vertex;

            /* IF v IS THE DESTINATION NODE, STORE ITS ADDRESS.
                THIS WILL BE REQUIRED TO BACKTRACE THE SHORTEST PATH FROM v (DESTINATION)
                TO THE SOURCE
            */
            if (v->vNumber == dest && d == NULL)
                d = v;

            edgeWeight = u->adjList[i]->weight;

            if (v->data > u->data + edgeWeight) {
                FHeap.DecreaseKey (v, u->data + edgeWeight);
                v->data = u->data + edgeWeight;

                v->prevNode = u;
            }
        }
    }

    // TIME TAKEN BY DIJKSTRA'S ALGO
    //std::cout << "Time Taken: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " s" << endl;

    // THE SHORTEST PATH: START FROM THE LAST VERTEX (DESTINATION) AND START THE WAY BACK
    if (d->vNumber != NULL)
        i = vertices[source]->vNumber;
    else {
        return -1;
        exit(0);
    }

    while(d && d->vNumber) {
        verticesOnSP.insert(verticesOnSP.begin(), d->vNumber);
        d = d->prevNode;
    }

    // INSERT THE SOURCE VERTEX AT THE BEGINNING OF THE SHORTEST PATH
    verticesOnSP.insert(verticesOnSP.begin(), i);

    // LENGTH OF THE SHORTEST PATH
	return vertices[dest]->data;
}

// HASH-MAP TO MAP IP-ADDR TO VERTEX/NODE
void Dijkstra::LoadIP(char* filename) {

    ifstream input;
    input.open(filename);

    string line, binIP;
    int start, end, vertex = 0;
    bitset<8> bSet;
    binIP = "";
    start = 0;

    // LOAD THE IP-ADDRESSES AND CREATE A MAP : <VERTEX, IP-ADDRESS>
    if (input.is_open())
    {
        while (getline (input,line)) {

            if (line.empty())
                continue;

            // 1ST OCTET
            end = line.find('.');
            bSet.reset();
            bSet = bitset<8>(stoi(line.substr(start, end)));
            binIP += bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();
            //cout << endl << stoi(line.substr(start, end)) << " --> " << bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();

            // 2ND OCTET
            start = end + 1;
            end = line.find('.', end+1);
            bSet.reset();
            bSet = bitset<8>(stoi(line.substr(start, end)));
            binIP += bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();
            //cout << endl << stoi(line.substr(start, end)) << " --> " << bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();

            // 3RD OCTET
            start = end + 1;
            end = line.find('.', end+1);
            bSet.reset();
            bSet = bitset<8>(stoi(line.substr(start, end)));
            binIP += bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();
            //cout << endl << stoi(line.substr(start, end)) << " --> " << bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();

            // 4TH OCTET
            bSet.reset();
            bSet = bitset<8>(stoi(line.substr(end+1)));
            binIP += bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();
            //cout << endl << stoi(line.substr(start, end)) << " --> " << bSet.to_string<char,std::string::traits_type,std::string::allocator_type>();

            //cout << endl << endl << "---------- " << binIP << endl;
            mNodeToIP.insert(pair<int, string>(vertex, binIP));
            binIP = "";
            vertex++;
            start = 0;
        }
    }
    else {
        cerr << "Unable to open file " << filename;
        exit(0) ;
    }       

    input.close();
}


int Dijkstra::InitializeNode (int source, int dest) {

    int i, nextHopVertex;

    // CLEAR THE VERTICES OF THE PREVIOUS COMPUTATIONS
    // RE-CONSTRUCT THE GRAPH

    // RE-INITIALIZE VERTICES
    for (i = 0; i < n; i++) {
        vertices[i]->data = INT_MAX;
        vertices[i]->prevNode = NULL;
    }
    
    vertices[source]->data = 0;


    const clock_t begin_time = clock();

    // CREATE AN EMPTY FIB HEAP AND POPULATE IT
    if (FHeap.IsEmpty()) {
        for (i = 0; i < n; i++) {
            //cout << "\t" << vertices[i]->vNumber << " : " << vertices[i]->data;
            FHeap.Insert(vertices[i]);
        }
    }

    Node *u, *v;
    Node *d = NULL;
    int edgeWeight;
    while (!FHeap.IsEmpty()) {

        u = FHeap.RemoveMin();

        for (i = 0; i < u->adjList.size(); i++) {
            v = u->adjList[i]->vertex;
            edgeWeight = u->adjList[i]->weight;

            if (v->data > u->data + edgeWeight) {
                FHeap.DecreaseKey (v, u->data + edgeWeight);
                v->data = u->data + edgeWeight;

                v->prevNode = u;
            }
        }
    }

    // TIME TAKEN BY DIJKSTRA'S ALGO
    //std::cout << "Time Taken: " << float( clock () - begin_time ) /  CLOCKS_PER_SEC << " s" << endl;

    BuildTrie(source);

    for (i = 0; i < n; ++i)
        vertices[i]->T.RemoveCommonSubTries(NULL, vertices[i]->T.root);

}


void Dijkstra::BuildTrie(int source) {
    // AFTER DIJSKTRA'S ALGO EXECUTES, ALL NODES CONTAIN ITS THE SHORTEST DISTANCE
    // FROM THE SOURCE, AND ALSO THE PATH

    Node *d;
    int nextHopVertex, dest;

    //CHECK FOR EACH DESTINATION
    for (int i = 0; i < n; ++i) {

        if (vertices[i]->vNumber == source)
            continue;

        d = vertices[i];
        dest = vertices[i]->vNumber;
        nextHopVertex = -1;
        
        while(d->prevNode) {
            if (d->prevNode->vNumber == source) {
                nextHopVertex = d->vNumber;
                break;
            }
            d = d->prevNode;
        }

        // INSERT IN THE ROUTING TABLE OF THE VERTEX i
        //vertices[source]->mRoutingTable.insert(pair<int, int>(dest, nextHopVertex));
    
        // CONSTRUCT A TRIE AT THIS SOURCE NODE WITH <key, value> PAIRS: 
        // <DESTINATION, NEXT_HOP>
        
        // GET THE IP ADDRESS OF THE NEXT-HOP IN BINARY FORMAT
        string destIP = mNodeToIP[dest];
        
        //cout << endl << "Inserting: " << destIP << ", " << to_string(nextHopVertex);

        // INSERT THE <DESTINATION_IP_ADDRESS, NEXT_HOP_NODE> PAIR IN THE TRIE
        // AFTER ALL THE <DESTINATION, NEXT_HOP> PAIRS OF THE CURRENT SOURCE
        // HAVE BEEN INSERTED INTO THE TRIE, REMOVE THE COMMON SUB-TRIES
        //if ((source != n-1 && dest == n-1) || (source == n-1 && dest == n-2))
        vertices[source]->T.Insert(destIP, to_string(nextHopVertex), false);
        //else
        //    vertices[source]->T.Insert(destIP, to_string(nextHopVertex), false);
    }
}


// ONCE THE NETWORK GRAPH HAS BEEN INITIALIZED, FIND OUT THE LONGEST MATCHING
// PREFIX TO REACH FROM THE SOURCE TO THE DESTINATION
void Dijkstra::FindRoute(int source, int dest) {

    string prefix, value;
    int i, dist = 0;
    std::vector<string> vPrefix;

    while (source != dest) {
        // VALUE = NEXT_HOP
        value = "";

        //cout << endl << "Checking source: " << source << endl;
        prefix = vertices[source]->T.LongestPrefixMatch(mNodeToIP[dest], value);
        vPrefix.push_back(prefix);
        

        // GET THE DISTANCE TO THE NEXT HOP
        for (i = 0; i < vertices[source]->adjList.size(); ++i)
        {
            if (vertices[source]->adjList[i]->vertex->vNumber == stoi(value)) {
                dist += vertices[source]->adjList[i]->weight;
                break;
            }
                
        }

        source = stoi(value);
    }

    // PRINT THE DISTANCE
    cout << dist << endl;

    // PRINT THE PREFIXES
    for (i = 0; i < vPrefix.size(); i++)
        cout << vPrefix[i] << " ";

    cout << endl;
}