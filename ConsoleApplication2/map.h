#pragma once

using namespace std;

template<class T>
struct Node {
	Node <T>() {};
	Node <T>(Node* n, T v) : next(n), value(v) {};
	Node* next;
	T value;
};

template <class P, class T>
class Map {
	Node<T>** values;
	size_t _size;
	size_t Elements;
	void arrResize() {
		Node<T>** _Values = new Node<T>*[_size * 2];
		for (int i = 0; i < _size * 2; i++) {
			if (i < _size) {
				_Values[i] = values[i];
			}
			else {
				_Values[i] = nullptr;
			}
		}
		delete[] values;
		values = _Values;
		_size *= 2;
	}
public:
	Map<P, T>() {
		_size = 8;
		values = new Node<T>*[_size];
		for (int i = 0; i < _size; i++) {
			values[i] = nullptr;
		}
		Elements = 0;
	}
	void insert(P key, T value) {
		size_t hashValue = hash<P>{}(key);
		size_t index = hashValue % _size;
		if (values[index] == nullptr) {
			Elements++;
			values[index] = new Node<T>(nullptr, value);
		}
		else {
			Node<T>* currNode = values[index];
			while (currNode->next) {
				currNode = currNode->next;
			}
			Node<T>* nextNode = new Node<T>(nullptr, value);
			currNode->next = nextNode;
		}
		if ((float)Elements / _size >= 0.6) {
			arrResize();
		}
	}
	T& operator [] (P& key) {
		size_t hashValue = hash<P>{}(key);
		size_t index = hashValue % _size;
		return values[index]->value;
	}
	~Map() {
		for (int i = 0; i < _size; i++) {
			Node<T>* curr = values[i];
			while (curr) {
				Node<T>* next = curr->next;
				delete curr;
				curr = next;
			}
		}
	}
};