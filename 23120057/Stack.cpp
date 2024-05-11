#pragma warning(disable: 4996)
#include "Stack.h"

Node* createNode(char* value) {
	Node* newNode = new Node;
	if (newNode != NULL) {
		newNode->data = value;
		newNode->pNext = NULL;
	}
	return newNode;
}

void Init(Stack* st) {
	st->pHead = NULL;
	st->size = 0;
}

bool IsEmpty(Stack* st) {
	return st->pHead == NULL;
}

void Push(Stack* st, char* value) {
	if (IsEmpty(st)) {
		st->pHead = createNode(value);
	}
	else {
		Node* newNode = createNode(value);
		newNode->pNext = st->pHead;
		st->pHead = newNode;
	}
	st->size++;
}

int GetSize(Stack* st) {
	return st->size;
}

char* Top(Stack* st) {
	return st->pHead->data;
}

char* Pop(Stack* st) {
	char* res = NULL;
	if (!IsEmpty(st)) {
		Node* tmp = st->pHead;
		st->pHead = st->pHead->pNext;
		res = tmp->data;
		delete tmp;
		st->size--;
	}
	return res;
}

void output(Stack* st) {
	Node* head = st->pHead;
	while (head) {
		printf("%s ", head->data);
		head = head->pNext;
	}
	printf("\n");
}