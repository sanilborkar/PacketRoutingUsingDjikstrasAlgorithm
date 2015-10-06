// BINARY TRIE HEADER FILE
#ifndef BINTRIE_H
#define BINTRIE_H

#define BRANCH_NODE 0
#define ELEMENT_NODE 1

#include <string>

using namespace std;

// BINARY TRIE NODE STRUCTURE
class TrieNode
{
public:
	string data;
	string value;
	int bitPosition;
	int nodeType;
	TrieNode* left;
	TrieNode* right;

	TrieNode();
	TrieNode(int type);
	TrieNode(string d, string val, int type);
	~TrieNode();
};


/*class BranchNode: TrieNode
{
public:
	int bitPosition;
	BranchNode();
	~BranchNode();
};

class ElementNode: TrieNode
{
public:
	string data;
	string value;
	ElementNode();
	~ElementNode();
};*/


// BINARY TREE CLASS DECALRATION
class BinTrie
{
public:
	TrieNode* root;

	BinTrie();
	~BinTrie();

	void RemoveCommonSubTries(TrieNode* p, TrieNode* r);

	bool IsEmpty();

	bool Insert (string key, string value, bool isPostOrder);
	string LongestPrefixMatch (string key, string &value);

};

#endif