// FIBONACCI HEAP NODE IMPLEMENTATION
#include "FibHeap.h"
#include <cstddef>
#include <iostream>

using namespace std;

Node::Node () {
	
}

Node::Node (int value, int weight) {
	vNumber = value;
	data = weight;
	degree = 0;
	parent = NULL;
	child = NULL;
	left = NULL;
	right = NULL;
	isChildCut = false;
}

Node::~Node () {
	
}

void Node::AddtoAdjList(Node* dest, int weight) {
	adjListNode *ALNode = new adjListNode();
	ALNode->vertex = dest;
	ALNode->weight = weight;
	adjList.push_back(ALNode);
}

bool Node::AddAsChild(Node *n)
{
	// SINCE n IS MADE A CHILD OF this, SET ITS isChildCut = false
	n->isChildCut = false;

	// INSERT n TO THE LEFT OF THE CURRENT child AND UPDATE THE child POINTER
    if (child) {
    	child->left = n;
    	n->right = child;
    }

    child = n;
    n->parent = this;
    degree++;
    return true;
}

void Node::RemoveFromHeap() {
	
	if (parent) {
		if (parent->child == this) {
			
			// IF INVOKING NODE HAS A LEFT SIBLING, CHANGE PARENT'S CHILD POINTER TO POINT TO IT
			if (left)
				parent->child = left;
			// ELSE IF INVOKING NODE HAS A RIGHT SIBLING, CHANGE PARENT'S CHILD POINTER TO POINT TO IT
			else if (right)
				parent->child = right;
			// ELSE IF INVOKING NODE WAS THE ONLY CHILD
			else
				parent->child = NULL;
		}

		parent->degree--;
	}

	// UPDATE LEFT SIBLING POINTER
	if (left)
		left->right = right;

	// UPDATE RIGHT SIBLING POINTER
	if (right)
		right->left = left;

	// UPDATE OTHER POINTERS OF INVOKING NODE
	left = NULL;
	right = NULL;
	parent = NULL;

}