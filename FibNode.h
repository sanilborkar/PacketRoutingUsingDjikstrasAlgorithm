// FIBONACCI NODE HEADER FILE
#ifndef FIBNODE_H
#define FIBNODE_H

#include <map>
#include <vector>
#include "BinTrie.h"

using namespace std;

typedef struct adjListNode adjListNode;

class Node;

struct adjListNode
{
	Node* vertex;
	int weight;
};

// STRUCTURE OF A FIBONACCI NODE
class Node
{
public:
	int vNumber;		// VERTEX NUMBER
	int data;			// WEIGHT OF AN (UNDIRECTED) EDGE WITH THIS NODE AS VERTEX
	int degree;
	Node* parent;
	Node* child;
	Node* left;
	Node* right;
	bool isChildCut;
	std::vector<adjListNode*> adjList;

	/* CONTAINS THE PREVIOUS NODE ON THE SHORTEST PATH TO THIS NODE
		THIS IS BASICALLY THE NODE THAT UPDATED this.data TO A LESSER VALUE
		DURING RELAXATION
	*/
	Node* prevNode;

	// MAP <DESTINATION, NEXT_HOP>
	//std::map<int, int> mRoutingTable;

	// TRIE OBJECT
	BinTrie T;

	Node();
	Node(int value, int weight);
	~Node();

	void AddtoAdjList(Node* dest, int weight);

	// ADD n AS A CHILD OF THE CURRENT (INVOKING) NODE
	bool AddAsChild(Node *n);

	// REMOVE THE CURRENT (INVOKING) NODE FROM THE FIB HEAP
	void RemoveFromHeap();

};

#endif