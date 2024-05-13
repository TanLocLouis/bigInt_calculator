#pragma once
#pragma warning(disable: 4996)

#include <iostream>
#include <string.h>
#include <math.h>
#include "BigInt.h"

using namespace std;

typedef struct Node {
	BigInt data;
	Node* pNext;
};

typedef struct Stack {
	Node* pHead;
	int size;
};

Node* createNode(BigInt value);
void Init(Stack* st);

bool IsEmpty(Stack* st);

void Push(Stack* st, BigInt value);

int GetSize(Stack* st);

BigInt Top(Stack* st);

BigInt Pop(Stack* st);

void output(Stack* st);

