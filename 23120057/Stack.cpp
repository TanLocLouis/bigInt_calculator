#pragma warning(disable: 4996)
#include "Stack.h"

Node* createNode(char* value) {
	Node* newNode = new Node;
	newNode->data = value;
	newNode->pNext = NULL;
	return newNode;
}

void Init(Stack& st) {
	st.pHead = NULL;
	st.size = 0;
}

bool isEmpty(Stack st) {
	return st.pHead == NULL;
}

void push(Stack& st, char* value) {
	if (isEmpty(st)) {
		st.pHead = createNode(value);
	}
	else {
		Node* newNode = createNode(value);
		newNode->pNext = st.pHead;
		st.pHead = newNode;
	}
	st.size++;
}

int getSize(Stack& st) {
	return st.size;
}

char* topS(Stack& st) {
	return st.pHead->data;
}

char* popS(Stack& st) {
	char* res = NULL;
	if (!isEmpty(st)) {
		Node* tmp = st.pHead;
		st.pHead = st.pHead->pNext;
		res = tmp->data;
		delete tmp;
		st.size--;
	}
	return res;
}

void output(Stack st) {
	Node* head = st.pHead;
	while (head) {
		printf("%d ", head->data);
		head = head->pNext;
	}
	printf("\n");
}