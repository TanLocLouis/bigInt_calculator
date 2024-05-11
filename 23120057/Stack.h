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

Node* createNode(char* value);

void Init(Stack* st);

bool IsEmpty(Stack* st);

void Push(Stack* st, char* value);

int GetSize(Stack* st);

char* Top(Stack* st);

char* Pop(Stack* st);

void output(Stack* st);