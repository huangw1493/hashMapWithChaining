#ifndef _hashmap__
#define _hashmap__
#include <stdexcept>
#include <functional>
#include <vector>

template <typename TKey, typename TValue>
class HashTable {
private:
	// A simple linked-list node class.
	class Node {
	public:
		TKey key;
		TValue value;
		Node *next;
	};
	std::function<std::size_t(TKey)> mHash;
	std::vector<Node*> mTable;
	std::size_t mCount;

public:
	// Constructs a hashtable with the given size, using the given function for
	// computing h(k).
	HashTable(int size, std::function<std::size_t(TKey)> hash) :
		mTable(size, nullptr), mHash(hash) {
	}

	// Inserts the given key and value into the table, assuming no entry with 
	// an equal key is present. If such an entry is present, override the entry's
	// value.
	void insert(TKey &key, TValue &value) {
		// Use the type std::size_t for working with hash table indices.
		// Invoke the mHash function, passing the key to calculate h(k).
		// Mod down to size.
		// Go to the table at that index and do the insertion routine.
		int k = mHash(key);
		k = k % mTable.size();
		int index = k;	//Checks index of in mTable
		Node *tmp = mTable[k];
		//if table location is empty, add a new node
		if (tmp == nullptr) {
			Node * baby = new Node;
			baby->key = key;
			baby->value = value;
			baby->next = nullptr;
			mTable[k] = baby;
			mCount++;	//Increaes mCount
		}
		//If table location is not empty
		else {
			//iterate thrugh list and check for duplicates
			while (tmp != nullptr) {
				//If duplicate overide values, create Node, otherwise iterate. 
				if (tmp->key == key) {
					////key is already the same, just modify value;
					tmp->value = value;
					return;
				}
				//If end of list, create Node
				else if (tmp->next == nullptr) {
					//create node and add it to end of list
					Node * baby = new Node;
					baby->key = key;
					baby->value = value;
					baby->next = nullptr;
					tmp->next = baby;
					mCount++;
					return;
				}
				//iterate
				else {
					tmp = tmp->next;
				}
			}
		}
		//delete tmp;
	}
			
	// Returns the value associated with the given key, if it is present.
	// Throws std::out_of_range if the key is not found.
	TValue& find(const TKey &key) {
		//These 2 lines converts key into mTable location
		int k = mHash(key);
		k = k % mTable.size();
		//Set tmp to first link of chain at k
		Node *tmp = mTable[k];
		while (tmp != nullptr) {
			//If the first one is the key we seek, return value
			if (tmp->key == key) {return tmp->value;}
			//Otherwise iterate until we hit nothing.
			else {tmp = tmp->next;}
		}
		//Throw error if nothing found;		
		throw std::out_of_range("Out of Range"); 
	}

	//Removes the pair with the given key from the table.
	void remove(const TKey &key) {
		//These 2 lines converts key into mTable location
		int k = mHash(key);
		k = k % mTable.size();

		//This is the placeholder. It will iterate through the list
		Node * tmp = mTable[k];
		//This is a place holder that will iterate one step behind tmp;
		Node * before = mTable[k];

		//If tmp == null, aka node wasnt found, return;
		if (tmp == nullptr) {
			//std::cout << "IT AINT HERE BOSS" << std::endl;
			return;
		}

		//Initial test. If first Node is the one, connect node[k] with tmp's next and delete tmp
		if (tmp->key == key) {
			//delete node from heap
			mTable[k] = tmp->next;
			delete tmp;
			mCount--;
			return;
		}
		//If first node isn't the one we're looking for, move tmp to the next node
		else {
			tmp = tmp->next;
			return;
		}
		//Until we hit the end of the chian...
		while (tmp != nullptr) {
			//If tmp == key were looking for
			if (tmp->key == key) {
				//If tmp has no children, set next to null and then delete tmp
				if (tmp->next == nullptr) {
					before->next = nullptr;
					delete tmp;
					mCount--;
					return;
				}
				//If tmp has children. Steal its child then delete it. This connects the previous node with the next node
				else {
					before->next = tmp->next;
					delete tmp;
					mCount--;
					return;
				}
			}
			//If it isnt the one we're looking for... check next pointer provided
			//Iterate before and tmp. 
			else {
				tmp = tmp->next;
				before = before->next;
			}
		}
	}
	//Returns the number of data elements in the table.	
	//Use mCount to keep track always
	int count() {return mCount;}

	//returns true/false if contains key
	bool containsKey(const TKey &key) {
		if (find(key) != nullptr)
			return true;
		else
			return false;
	}
	

	//Returns vector with all the keys in the table. Neal approved.
	std::vector<int> keySet() {
		std::vector<int> retVec;
		for (int i = 0; i < mTable.size(); i++) {
			//tmp iterates things.
			Node * tmp = mTable[i];
			//Check i for a node. 
			if (mTable[i] != nullptr) {
				//while node->next != nullptr, push things
				while (tmp->next != nullptr) {
					retVec.push_back(tmp->key);
					tmp = tmp->next;
				}
			}
		}
		return retVec;
	}
};

#endif