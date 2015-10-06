// BINARY TRIE IMPLEMENTATION
#include "BinTrie.h"

#include <iostream>

using namespace std;

/*BranchNode::BranchNode() {
	bitPosition = -1;
	left = NULL;
	right = NULL;
}

BranchNode::~BranchNode() {
	delete left;
	delete right;
}

ElementNode::ElementNode() {
	data = "";
	value = "";
	left = NULL;
	right = NULL;
}

ElementNode::~ElementNode() {
	delete left;
	delete right;
}
*/

BinTrie::BinTrie() {
	root = NULL;
}

BinTrie::~BinTrie() {
	delete root;
}



bool BinTrie::IsEmpty() {
	return (root == NULL);
}

TrieNode::TrieNode() {

}

// CONSTRUCTOR FOR BRANCH NODE
TrieNode::TrieNode (int type) {
	
	data = "";
	value = "";
	bitPosition = -1;
	nodeType = type;
	left = NULL;
	right = NULL;
}

// CONSTRUCTOR FOR ELEMENT NODE
TrieNode::TrieNode (string d, string val, int type) {
	
	data = d;
	value = val;
	bitPosition = -1;
	nodeType = type;
	left = NULL;
	right = NULL;
}

TrieNode::~TrieNode() {

}

bool BinTrie::Insert (string data, string value, bool isPostOrder) {

	/*cout << endl << "*******************";
	cout << endl << "Insert: " << data << " : " << value << endl;*/

	TrieNode *r = root;
	TrieNode *p, *gp;
	int level = 0;		
	
	// IF THE TRIE IS EMPTY
	if (IsEmpty()) {
		root = new TrieNode(data, value, ELEMENT_NODE);
		root->bitPosition = 0;
		return true;
	}

	while (r != NULL) {
		gp = p;
		p = r;
		
		if(data.at(level) == '0') {
			//if (r->left->nodeType == ELEMENT_NODE || r->left == NULL) break;
			r = r->left;
			//cout << endl << level << " : left";
		}
		else {
			r = r->right;	
			//if (r->right->nodeType == ELEMENT_NODE || r->right == NULL) break;
			//cout << endl << level << " : right";
		}
		
		level++;
	}		

	// THE LAST NODE THAT WE ENCOUNTERED BEFORE FALLING OFF
	// IF THIS NODE IS NOT AN ELEMENT NODE
	if (p->nodeType == BRANCH_NODE) {

		if (data.at(level-1) == '0') {
			p->left = new TrieNode(data, value, ELEMENT_NODE);
			p->left->bitPosition = level;
			//cout << endl << "BRANCH_NODE PRESENT: Add " << level << " : left";
		}
		else {
			p->right = new TrieNode(data, value, ELEMENT_NODE);
			p->right->bitPosition = level;
			//cout << endl << "BRANCH_NODE PRESENT: Add " << level << " : right";
		}
		
	}

	// IF THIS NODE IS AN ELEMENT NODE
	else {

		// IF THIS (ELEMENT) NODE CONTAINS THE SAME KEY WE ARE INSERTING
		if(!p->data.compare(data)) {
			cout << endl << "Duplicate IP Address!";
			return false;
		}
		
		// CREATE A NEW BRANCH NODE
		TrieNode *newBNode = new TrieNode(BRANCH_NODE);
		
		// CHECK PREVIOUS TO PREVIOUS BIT TO CHECK WHICH BIT WE BRANCHED ON
		// TO DECIDE IF THIS NEW BRANCH NODE WILL BE INSERTED AS A LEFT/RIGHT CHILD
		// WE HAD BRANCHED TO REACH gp ON BIT (level-2)
		bool isAdded = false;
		if(level >= 2) {
			if (p == gp->left) {
				gp->left = newBNode;
				//cout << endl << "GP: " << level << " : left";
			}
			else if (p == gp->right) {
				gp->right = newBNode;
				//cout << endl << "GP: " << level << " : right";
			}

			newBNode->bitPosition = level - 1;
			level--;
			isAdded = true;
		}
		else if (level == 1) {
			root = newBNode;
			newBNode->bitPosition = 0;
			root->bitPosition = 0;
		}
		
		if (!isAdded) {
			level--;
			isAdded = false;
		}
		
		// FIND THE 1ST BIT POSITION WHERE THE NEW DATA DIFFERS FROM THE DATA ALREADY
		// PRESENT AT THE ELEMENT NODE
		while (p->data.at(level) == data.at(level)) {				
			TrieNode *tempBNode = new TrieNode(BRANCH_NODE);	

			// IF BOTH HAVE (level)TH BIT AS 0				
			if(data.at(level) == '0') {
				newBNode->left = tempBNode;
				//cout << endl << level << " : left";
			}
			else {
				newBNode->right = tempBNode;
				//cout << endl << level << " : right";
			}

			newBNode->bitPosition = level;				
			newBNode = tempBNode;

			// THE HEIGHT OF THE TRIE INCREASES BY 1
			level++;
		}				
		
		// IF level = 1ST BIT POSITION WHERE THE DATA DIFFERS
		if(data.at(level) == '0') {
			//cout << endl << "Adding BranchNode at " << level << " : left";
			newBNode->left = new TrieNode(data, value, ELEMENT_NODE);
			newBNode->left->bitPosition = level + 1;
			newBNode->right = p;
		}
		else {
			//cout << endl << "Adding BranchNode at " << level << " : right";
			newBNode->left = p;
			newBNode->right = new TrieNode(data, value, ELEMENT_NODE);
			newBNode->right->bitPosition = level + 1;
		}
	}

	if (isPostOrder) {

		//string v;
		/*cout << endl << "---------------------------- BEFORE ---------------"; 
		string p = LongestPrefixMatch("11000000000000101010100000000100", v);*/

		RemoveCommonSubTries(NULL, root);

		/*cout << endl << "---------------------------- AFTER ---------------";
		p = LongestPrefixMatch("11000000000000101010100000000100", v);*/

		isPostOrder = false;
	}

	return true;			
}

// FIND THE LONGEST PREFIX THAT MATCHES val
string BinTrie::LongestPrefixMatch (string key, string &value) {

	//cout << endl << "Looking for: " << key << endl;

	TrieNode *r = root;
	TrieNode *p;
	int level = 0;
	string prefix = "";

	// IF THE TRIE IS EMPTY
	if (IsEmpty())
		return "";

	// WALK DOWN THE TRIE TO FIND THE LONGEST PREFIX MATCH
	while (r != NULL && level < 32) {

		p = r;
		if(key.at(level) == '0') {
			r = r->left;
			if (r) {
				prefix += "0";
				//cout << endl << "level = " << level << " : " << prefix;
				level++;
			}
			/*else
				cout << endl << "%%%%%%%%%%%%%%%%%%%%%% FALLING....";*/


		}
		else {
			r = r->right;
			if (r) {
				prefix += "1";
				//cout << endl << "level = " << level << " : " << prefix;
				level++;
			}
			/*else
				cout << endl << "%%%%%%%%%%%%%%%%%%%%%% FALLING....";*/
		}

/*		if (!r) {
			prefix += key.at(level);
			level++;
		}*/
	}

	if (level == 32) {
		//prefix += r->value;
		value = r->value;
	}
	else {
		//prefix += p->value;
		value = p->value;
	}

	return prefix;
}


// PERFORM A POST-ORDER TRAVERSAL OF THE BINARY TRIE
void BinTrie::RemoveCommonSubTries(TrieNode* p, TrieNode* r) {

	if (r == NULL)
		return;

	// POST-ORDER TRAVERSAL
	RemoveCommonSubTries(r, r->left);
	RemoveCommonSubTries(r, r->right);

	// IF r = BRANCH NODE
	if (r->nodeType == BRANCH_NODE) {

		// IF IT HAS BOTH LEFT & RIGHT CHILDREN
		if (r->left && r->right) {

			// IF THESE ARE ELEMENT NODES
			if (r->left->nodeType == ELEMENT_NODE && r->right->nodeType == ELEMENT_NODE) {

				// AND BOTH THEIR VALUES ARE EQUAL
				if (r->left->value.compare(r->right->value) == 0) {

					// CHECK IF r IS THE LEFT OR RIGHT CHILD OF p
					// COMPACT TRIE
					if (p->left == r)
						p->left = r->left;
					else
						p->right = r->left;
				}
			}
		}

		// IF IT HAS EITHER LEFT OR RIGHT CHILD
		// IF IT HAS ONLY A LEFT CHILD
		else if (r->left && r->right == NULL) {

			if (r->left->nodeType == ELEMENT_NODE && r->left->value.empty() == false) {

				// CHECK IF r IS THE LEFT OR RIGHT CHILD OF p
				// COMPACT TRIE
				if (p->left == r)
					p->left = r->left;
				else
					p->right = r->left;
			}
			
		}

		// IF IT HAS ONLY A RIGHT CHILD
		else if (r->left == NULL && r->right) {

			if (r->right->nodeType == ELEMENT_NODE && r->right->value.empty() == false) {

				// CHECK IF r IS THE LEFT OR RIGHT CHILD OF p
				// COMPACT TRIE
				if (p->left == r)
					p->left = r->right;
				else
					p->right = r->right;
			}
		}
	}
}