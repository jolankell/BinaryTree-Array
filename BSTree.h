////
// Description: This class is a binary search tree stored
// in an array. The root starts at index 1, and a index's
// left child is the index * 2, while the right child is
// (index * 2) + 1. Things inserted into the tree are
// sorted based on their assigned key. Multiple functions
// are available for use, like print, insert, & remove. 
// The arrays size is manually grown when needed, it is 
// doubled every time it grows.
////

#include "BSTInterface.h"
#include <string>

using namespace std;
template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >
{
private:
	
	/*
	* Private "Node" Class...for this implementation, the Pair is the Node
	*/
	class Pair 	{
		public:
			KeyComparable key;
			Value value;
						
			//Initialize class members from constructor arguments 
			//by using a member initializer list.
			//This method uses direct initialization, which is more
			//efficient than using assignment operators inside the constructor body.
			Pair( KeyComparable & key, Value & value )
				: value{ value },  key{ key }
			{
				// empty constructor...member initializer is doing all the work
			}

	};   // end of Pair class

	// number of values stored in the tree
	int count = 0;
	// capacity of array holding the tree
	int size = 25;
	// the array that holds the pairs
	Pair **root = new Pair*[size];
		
	/*
	* Prints the data of the tree in order based on the key to the output stream
	*/
	void printTree(int index, std::ostream & out) const {
		if (root[1] != nullptr) {

			if ((index * 2) < size && root[index * 2] != nullptr) {
				printTree(index * 2, out);
			}

				out << *root[index]->value << endl;

			if (((index * 2) + 1) < size && root[((index * 2) + 1)] != nullptr) {
				printTree(((index * 2) + 1), out);
			}
		}
	}
	
public:
	BinarySearchTree() {
		for (int i = 0; i < size; i++) {
			root[i] = nullptr;
		}
	}
	
	~BinarySearchTree() {
		for (int i = 0; i < size; i++) {
			if (root[i] != nullptr) {
				delete root[i];
			}
		}
		delete root;
	}

	/*
	* Finds the node with the smallest element in the tree	
	*/
	const Value findMin() const {
		int index = 1;
		if (root[1] != nullptr) {
			while (root[(index * 2)] != nullptr) {
				index = index * 2;
			}
			return (root[index]->value);
		}
		return nullptr;
	}

	/*
	* Finds the node with the largest element in the tree
	*/
	const Value findMax() const {
		int index = 1;
		if (root[1] != nullptr) {
			while (root[(index * 2) + 1] != nullptr) {
				index = (index * 2) + 1;
			}
			return (root[index]->value);
		}
		return nullptr;
	}

	/*
	* Finds the node with a key that matches the argKey 
	* updates the founditem refrerence if found
	* returns true if it was found 
	* returns false if it was not 
	*/
	bool find(const KeyComparable & argKey , Value & founditem) const 	{
		int index = 1;
		bool done = false;

		while (done == false) {
			if (root[index] == nullptr) {
				return false;
			}
			else if (argKey > root[index]->key) {
				index = (index * 2) + 1;
				continue;
			}
			else if (argKey < root[index]->key) {
				index = (index * 2);
				continue;
			}
			else {//argKey == root[index]->key
				founditem = root[index]->value;
				return true;
			}
		}
		return false;
	}

	/*
	* Returns true if the item is found in the tree
	*/
	bool contains(const KeyComparable & argKey) const {
		//int index = 1;
		//bool done = false;

		//while (done == false) {
		//	if (root[index] == nullptr) {
		//		return false;
		//	}
		//	else if (argKey > root[index]->key) {
		//		index = (index * 2) + 1;
		//		continue;
		//	}
		//	else if (argKey < root[index]->key) {
		//		index = (index * 2);
		//		continue;
		//	}
		//	else {//argKey == root[index]->key
		//		return true;
		//	}	
		//}
		for (int i = 0; i < size; i++) {
			if (root[i] != nullptr) {
				if (root[i]->key == argKey) {
					return true;
				}
			}
		}
		return false;
	}

	/*
	* Returns true if tree has no nodes
	*/
	bool isEmpty() const {
		if (root[1] == nullptr) {
			return true;
		}
		return false;
	}

	/*
	* Prints all the data from the tree in order based on key
	*/
	void printTree(std::ostream & out = cout) const {
		printTree(1, out);
	}

	/*
	* Removes all nodes from the tree
	*/
	void makeEmpty() {
		for (int i = 0; i < size; i++) {
			root[i] = nullptr;
		}
		count = 0;
	}

	/*
	* Inserts a node into the tree
	* maintains this property of the tree:
	*     All nodes to the left will be less
	*     All nodes to the right will be greater
	*/
	bool insert( Value value,  KeyComparable key, int index) 	{

		if (root[1] == nullptr) {
		//if nothing in tree array
			root[1] = new Pair(key, value);
			count++;
			return true;
		}
		else {//if something is in tree

			if (key > root[index]->key) {
				index = (index * 2) + 1;
				if (index >= size) {
					root = updateSize();
				}
				if (root[index] == nullptr) {
					root[index] = new Pair(key, value);
					count++;
					return true;
				}
				else {//if root[index] != nullptr
					insert(value, key, index);
				}
			}
			else if (key < root[index]->key) {
				index = index * 2;
				if (index >= size) {
					root = updateSize();
				}
				if (root[index] == nullptr) {
					root[index] = new Pair(key, value);
					count++;
					return true;
				}
				else {//if root[index] != nullptr
					insert(value, key, index);
				}
			}
		}
		return false;
	}

	Pair** updateSize() {
		int oldSize = size;
		size = size * 2;
		Pair** updatedRoot = new Pair*[size];
		for (int i = 0; i < oldSize; i++) {
			updatedRoot[i] = root[i];
		}
		for (int i = oldSize; i < size; i++) {
			updatedRoot[i] = nullptr;
		}
		delete root;
		return updatedRoot;
	}

	// Removes the node associated with key if it is in the tree
	bool remove(const KeyComparable& key) {
		int index = 1; int left = 0; int right = 0;

		do {
			if (root[index] == nullptr || index >= size) {
				return false;
			}
			else if (key > root[index]->key) {
				index = (index * 2) + 1;
			}
			else if (key < root[index]->key) {
				index = index * 2;
			}
		} while (root[index]->key != key);

		left = index * 2; right = left + 1;

		if ((left >= size || root[left] == nullptr) && (right >= size || root[right] == nullptr)) {
			delete root[index]; root[index] = nullptr; count--;
			return true;
		}
		else {
			orphanPreventor(index);
			return true;
		}
	}

	void orphanPreventor(int& index) {
		int left = index * 2; int right = left + 1;
		int predecessor = 0; int successor = 0; Pair* temp = nullptr;

		do {

			if (right < size && root[right] != nullptr) {
				successor = right;

				while (successor * 2 < size && root[successor * 2] != nullptr) {
					successor = successor * 2;
				}

				temp = root[index]; root[index] = root[successor];
				root[successor] = temp; index = successor;
			}
			else {
				predecessor = left;

				while ((predecessor * 2) + 1 < size && root[(predecessor * 2) + 1] != nullptr) {
					predecessor = (predecessor * 2) + 1;
				}

				temp = root[index]; root[index] = root[predecessor];
				root[predecessor] = temp; index = predecessor;
			}

			left = index * 2; right = left + 1;

		} while ((left < size && root[left] != nullptr) || (right < size && root[right] != nullptr));

		delete root[index]; root[index] = nullptr; count--;
	}

	int getSize() {
		return size;
	}

	int getCount() {
		return count;
	}

	//void remove(const KeyComparable& key) {
	//	int index = 0;
	//	bool goodToGo = false;
	//	
	//	if (key == 117) {
	//		system("pause");
	//	}

	//	for (int i = 1; i < size; i++) {
	//		if (root[i] != nullptr) {
	//			if (root[i]->key == key) {
	//				index = i; goodToGo = true;
	//				break;
	//			}
	//		}
	//	}

	//	if(goodToGo = true){

	//		int left = index * 2;
	//		int right = (index * 2) + 1;
	//		int move = 0;

	//		if ((left < size && root[left] != nullptr) &&
	//			(right >= size || root[right] == nullptr)) {
	//			delete root[index];
	//			root[index] = root[left];
	//			move = left - index;
	//			orphanRemover(left, move * 2);
	//		}
	//		else if ((left >= size || root[left] == nullptr) &&
	//			(right < size && root[right] != nullptr)) {
	//			delete root[index];
	//			root[index] = root[right];
	//			move = right - index;
	//			orphanRemover(right, move * 2);
	//		}
	//		else if ((left < size && root[left] != nullptr) &&
	//			(right < size && root[right] != nullptr)) {
	//			int successor = successorFinder(right);
	//			delete root[index];
	//			root[index] = root[successor];
	//			move = (((successor * 2) + 1) - successor);

	//			if ((successor * 2) + 1 < size && root[(successor * 2) + 1] != nullptr) {
	//				orphanRemover(successor, move);
	//			}
	//			else {//nothing right
	//				root[successor] = nullptr;
	//			}
	//		}
	//		else {//nothing left or right
	//			delete root[index];
	//			root[index] = nullptr;
	//		}
	//		//count--;
	//	}
	//}

	//void orphanRemover(int index, int move) {

	//	if (root[index]->key == 117) {
	//		system("pause");
	//	}

	//	int left = index * 2;
	//	int right = (index * 2) + 1;

	//	if (((right < size && root[right] == nullptr) && (root[right]->key == 117)) || 
	//		((left < size && root[left] != nullptr) && (root[left]->key == 117))) {
	//		system("pause");
	//	}

	//	if ((left >= size || root[left] == nullptr) &&
	//		(right >= size || root[right] == nullptr)) {
	//		delete root[index];
	//		root[index] = nullptr; return;
	//	}
	//	if ((left < size && root[left] != nullptr) &&
	//		(right >= size || root[right] == nullptr)) {
	//		root[(left - move)] = root[left];
	//		root[index] = nullptr;
	//		orphanRemover(left, move * 2);
	//	}
	//	if ((left >= size || root[left] == nullptr) &&
	//		(right < size && root[right] != nullptr)) {
	//		root[(right - move)] = root[right];
	//		//root[index] = nullptr;
	//		orphanRemover(right, move * 2);
	//	}
	//	else if ((left < size && root[left] != nullptr) &&
	//		(right < size && root[right] != nullptr)) {
	//		int successor = successorFinder(right);
	//		root[index] = root[successor];
	//		if ((successor * 2) + 1 < size && root[(successor * 2) + 1] != nullptr) {
	//			move = ((successor * 2) + 1) - successor;
	//			orphanRemover(successor, move);
	//		}
	//		else {
	//			root[successor] = nullptr;
	//		}
	//	}
	//}

	//int successorFinder(int index) {
	//	
	//	while (index * 2 < size && root[(index * 2)] != nullptr) {
	//		index = index * 2;
	//	}
	//	return index;
	//}

};	// end of BinarySearchTree class