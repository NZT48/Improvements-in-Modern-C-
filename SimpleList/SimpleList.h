#include <iostream>

using namespace std;

class Node {
public:
	int data;
	Node *next;

	Node(): next(nullptr) {}
	Node(const int& item, Node *ptr = nullptr) :
    data(item), next(ptr) {}

};

class SimpleList {
public:

    SimpleList() {
		head = tail = new Node();
    }

    ~SimpleList() {
		while (head->next != nullptr) {
			Node* tmp = head;
			head = head->next;
			delete tmp;
		}
		delete head;
	}


	class iterator {
		friend class SimpleList;
	private:
		Node *nodePtr;

		iterator(Node *newPtr) : nodePtr(newPtr) {}

	public:
		iterator() : nodePtr(nullptr) {}

		bool operator==(const iterator& itr) const {
	        return nodePtr == itr.nodePtr;
	    }

		bool operator!=(const iterator& itr) const {
	        return nodePtr != itr.nodePtr;
	    }

		int& operator*() const {
			return nodePtr->next->data;
		}

		iterator operator++(){
			iterator temp = *this;
			nodePtr = nodePtr->next;
			return temp;
		}
	};

	iterator begin() const { return iterator(head); }

	iterator end() const { return iterator(tail); }


	iterator add(const int& data) {
        iterator pos = this->end();
		Node* newNd = new Node(data, pos.nodePtr->next);
		if(pos.nodePtr == tail) tail = newNd;
		pos.nodePtr->next = newNd;
		return pos;
	}

    iterator insert(iterator pos, const int& data) {
		Node* newNd = new Node(data, pos.nodePtr->next);
		if(pos.nodePtr == tail) tail = newNd;
		pos.nodePtr->next = newNd;
		return pos;
	}

private:
	Node* head;
	Node* tail;

};
