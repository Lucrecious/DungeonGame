#ifndef STACK_H
#define STACK_H

template <class T>
class Node {
public:
	Node* below;
	T value;
};

template <class T>
class Stack {
public:	
	Stack<T>() : top(0) {
	}

	~Stack<T>() {
		while(this->top) {
			this->pop();
		}
	}

	T pop() {
		T value = this->top->value;
		Node<T>* tmp = this->top;
		this->top = this->top->below;
		delete tmp;
		return value;
	}

	T peek() {
		return this->top->value;
	}

	void push(T value) {
		Node<T>* node = new Node<T>();
		node->below = this->top;
		this->top = node;
		node->value = value;
	}

	bool isEmpty() {
		return this->top == 0;
	}

private:
	Node<T>* top;
};

#endif
