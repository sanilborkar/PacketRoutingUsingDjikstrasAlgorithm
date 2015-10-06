// MIN-FIBONACCI HEAP IMPLEMENTATION

#include "FibHeap.h"
#include <cstddef>
#include <string>
#include <iostream>

using namespace std;


FibHeap::FibHeap () {
	FH = NULL;
}

FibHeap::~FibHeap () {
	delete FH;
}

bool FibHeap::IsEmpty() {
	return (FH == NULL);
}

bool FibHeap::Insert (Node *ptr) {

	// EMPTY FIB HEAP
	if (FH == NULL) {
		FH = ptr;
		return true;
	}

	ptr->right = FH->right;
	if (FH->right)
		FH->right->left = ptr;
	FH->right = ptr;
	ptr->left = FH;

	// RE-ADJUST MIN. FIB HEAP POINTER
	if (ptr->data < FH->data)
		FH = ptr;

	return true;
}

void FibHeap::DecreaseKey (Node* ptr, int newValue) {

	if (newValue > ptr->data) {
		cerr << endl << "ERROR::DecreaseKey: New Key Value is greater than the current value!";
		return;
	}		

	ptr->data = newValue;
	Node *p = ptr->parent;

	// IF THIS NEW VALUED NODE HAS A PARENT, REMOVE IT FROM THE HEAP AND INSERT IT INTO
	// THE TOP-LEVEL CIRCULAR LIST
	if (p) {
		ptr->RemoveFromHeap();
		Insert(ptr);
		CascadingCut (p);
	}

	// UPDATE MIN FIB HEAP POINTER, IF NECESSARY
	if (ptr->data < FH->data)
		FH = ptr;
}


Node* FibHeap::RemoveMin () {

	// GET THE CHILD OF THE MIN ROOT NODE
	Node *leftChild = FH->child;
	
	Node *next, *temp;

	// ITERATE OVER ALL THE CHILDREN OF THE REMOVED NODE TO THE RIGHT OF ITS CHILD
	// AND INSERT THEM IN THE TOP-LEVEL LIST
	while (leftChild) {
		next = leftChild->right;
		leftChild->RemoveFromHeap();		// REMOVE THE SUBTREE ROOTED AT leftChild FROM THE HEAP
		Insert(leftChild);		// INSERT THE SUBTREE ROOTED AT leftChild TO THE TOP-LEVEL LIST
		leftChild = next;					// PROCEED
	}

	// ITERATE OVER ALL THE CHILDREN OF THE REMOVED NODE TO THE LEFT OF ITS CHILD
	// AND INSERT THEM IN THE TOP-LEVEL LIST
	if (FH->child)
		leftChild = FH->child;
	while (leftChild) {
		next = leftChild->left;
		leftChild->RemoveFromHeap();		// REMOVE THE SUBTREE ROOTED AT leftChild FROM THE HEAP
		Insert(leftChild);		// INSERT THE SUBTREE ROOTED AT leftChild TO THE TOP-LEVEL LIST
		leftChild = next;					// PROCEED
	}

	// STORE MIN ROOT'S RIGHT SIBLING TO MAKE IT THE MIN ROOT
	if (FH->right)
		next = FH->right;

	// THERE IS A SINGLE TREE ROOTED AT THIS (LEFTMOST) MIN ROOT
	else {
			temp = FH;
			Node *newFH = FH->left;
			FH->RemoveFromHeap();
			FH = newFH;
			return temp;
	}

	// MAKE MIN ROOT'S RIGHT SIBLING AS THE NEW MIN ROOT
	temp = FH;
	FH->RemoveFromHeap();
	FH = next;
	Node *leftNode = next->left;

	// INITIALIZE VECTOR OF DEGREES OF NODES TO BE USED FOR PAIR-WISE COMBINE
	std::vector<Node*> vNodeDegrees;
	for (int i = 0; i < 1000; ++i)
		vNodeDegrees.push_back(NULL);

	// TRAVERSE ALL NODES TO THE RIGHT OF CURRENT NODE
	while (next) {
		if (next->data < FH->data)
			FH = next;

		// ADVANCE TO THE RIGHT
		leftChild = next->right;
		PairwiseCombine (next, vNodeDegrees);
		next = leftChild;
	}

	next = leftNode;
	// TRAVERSE ALL NODES TO THE LEFT OF CURRENT NODE
	while (next) {
		if (next->data < FH->data)
			FH = next;

		// ADVANCE TO THE RIGHT
		leftChild = next->left;
		PairwiseCombine (next, vNodeDegrees);
		next = leftChild;
	}

	return temp;
}

// ARBITRARY REMOVE
Node* FibHeap::Remove (Node* ptr) {

	// IF ptr POINTS TO THE MIN ROOT, INVOKE RemoveMin()
	if (ptr == FH)
		return RemoveMin();

	// ELSE REMOVE ptr FROM THE HEAP AND RETURN A POINTER TO IT
	else {
		Node *p = ptr->parent;

		ptr->RemoveFromHeap();

		// PERFORM A CASCADING CUT
		CascadingCut (p);

		return ptr;
	}
}


void FibHeap::PairwiseCombine (Node *ptr, std::vector<Node*> &vNodeDegrees) {

	Node* sameDegNode = vNodeDegrees[ptr->degree];

	// NO OTHER ROOT WITH SAME DEGREE AS NODE ptr
	if (sameDegNode == NULL) {
		vNodeDegrees[ptr->degree] = ptr;
		return;
	}

	// ANOTHER MATCHING ROOT NODE WITH SAME DEGREE AS ptr
	vNodeDegrees[ptr->degree] = NULL;

	if (ptr->data < sameDegNode->data || ptr == FH) {
		sameDegNode->RemoveFromHeap();
		ptr->AddAsChild(sameDegNode);

		// AFTER ADDING IT AS A CHILD, ITS DEGREE WILL GO UP BY ONE.
		// IF THERE IS NO OTHER NODE WITH THIS SAME NEW DEGREE, NO MORE COMBINING
		if (vNodeDegrees[ptr->degree] == NULL)
			vNodeDegrees[ptr->degree] = ptr;
		
		// NOW CHECK IF THERE IS SOME OTHER NODE WITH THIS SAME NEW DEGREE.
		else
			PairwiseCombine (ptr, vNodeDegrees);
	}
	else
	{
		ptr->RemoveFromHeap();
		sameDegNode->AddAsChild(ptr);

		// AFTER ADDING IT AS A CHILD, ITS DEGREE WILL GO UP BY ONE.
		// IF THERE IS NO OTHER NODE WITH THIS SAME NEW DEGREE, NO MORE COMBINING
		if (vNodeDegrees[sameDegNode->degree] == NULL)
			vNodeDegrees[sameDegNode->degree] = sameDegNode;
		
		// NOW CHECK IF THERE IS SOME OTHER NODE WITH THIS SAME NEW DEGREE.
		else
			PairwiseCombine (sameDegNode, vNodeDegrees);	
	}

}


void FibHeap::CascadingCut (Node* p) {

	if (OPT) return;

	// IF p IS NULL
	if (!p)
		return;

	// IF p IS THE ROOT (isChildCut IS NOT DEFINED FOR THE ROOT)
	if (!p->parent) {
		p->isChildCut = false;
		return;
	}

	if (!p->isChildCut) {
		p->isChildCut = true;
		return;
	}

	// STORE p'S PARENT IN ORDER TO BACK TRACK UP THE TREE
	Node *par = p->parent;

	// REMOVE p FROM THE FIB HEAP AND INSERT IN THE TOP-LEVEL LIST
	p->RemoveFromHeap();
	Insert(p);
	CascadingCut(par);
}