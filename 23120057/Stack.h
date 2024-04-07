#pragma warning(disable: 4996)

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

typedef struct Node {
	char* data;
	Node* pNext;
};

typedef struct Stack {
	Node* pHead;
	int size;
};

Node* createNode(int value);

void Init(Stack& st);

bool isEmpty(Stack st);

void push(Stack& st, int value);

int getSize(Stack& st);

int top(Stack& st);

int pop(Stack& st);

void output(Stack st);