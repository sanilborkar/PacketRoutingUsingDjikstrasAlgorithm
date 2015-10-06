// FIBONACCI HEAP HEADER FILE
#ifndef FIBHEAP_H
#define FIBHEAP_H
#define OPT true

#include "FibNode.h"
#include <string>

class FibHeap {
private:
	Node *FH;

	void PairwiseCombine (Node *ptr, std::vector<Node*> &vNodeDegrees);
	void CascadingCut (Node *p);

public:
	FibHeap ();
	~FibHeap ();

	bool IsEmpty();

	bool Insert (Node* ptr);
	void DecreaseKey (Node *ptr, int newValue);

	void RemoveFromHeap();
	Node* RemoveMin ();
	Node* Remove (Node* ptr);
};

#endif