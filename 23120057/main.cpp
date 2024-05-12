#pragma warning(disable: 4996)
#include "Stack.h"

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else
        return 0;
}

bool isOperator(char* op) {
    return (op[0] == '+' || op[0] == '-' || op[0] == '*' || op[0] == '/');
}

Stack* infixToPostfix(const char* infix) {
    Stack* postfix = new Stack;
    Init(postfix);

    Stack* operators = new Stack;
    Init(operators);

    int index = 0;

    int start = 0, end = 0;
    while (infix[index] != NULL) {
        // Number
        if (isalnum(infix[index])) {
            if (index > 0 && !isalnum(infix[index - 1]) && isalnum(infix[index])) {
                start = index;

            }

            if ((index < strlen(infix) - 1 && isalnum(infix[index]) && !isalnum(infix[index + 1])) || (index == strlen(infix) - 1) && isalnum(infix[index])) {
                end = index;
                // split value
                char* operand = (char*)malloc((end - start + 1 + 1) * sizeof(char));
                strncpy(operand, infix + start, (end - start + 1));
                operand[end - start + 1] = '\0';
                Push(postfix, operand);
            }
        }
        // (
        else if (infix[index] == '(') {
            char* operand = (char*) malloc(2 * sizeof(char));
            operand[0] = infix[index];
            operand[1] = '\0';
            Push(operators, operand);
        }
        // )
        else if (infix[index] == ')'){
            while (!IsEmpty(operators) && strcmp(Top(operators), "(") != 0) {
                Push(postfix, Top(operators));
                Pop(operators);
            }
            Pop(operators);
        }
        // +=*/
        else {
            while (!IsEmpty(operators) && precedence(infix[index]) <= precedence(Top(operators)[0])) {
                Push(postfix, Top(operators));
                Pop(operators);
            }
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = infix[index];
            operand[1] = '\0';
            Push(operators, operand);
        }
        index++;
    }

    while (!IsEmpty(operators)) {
        Push(postfix, Top(operators));
        Pop(operators);
    }

    Stack* res = new Stack;
    Init(res);
    while (!IsEmpty(postfix)) {
        Push(res, Top(postfix));
        Pop(postfix);
    }
    return res;
}

char* Plus(const char* val1, const char* val2) {
    int len1 = strlen(val1);
    int len2 = strlen(val2);
    int maxLen = std::max(len1, len2);
    int carry = 0;
    char* res = new char[maxLen + 2];
    res[maxLen + 1] = '\0';

    for (int i = 0; i < maxLen; ++i) {
        int digit1 = (i < len1) ? (val1[len1 - i - 1] - '0') : 0;
        int digit2 = (i < len2) ? (val2[len2 - i - 1] - '0') : 0;
        int sum = digit1 + digit2 + carry;
        res[maxLen - i] = '0' + (sum % 10);
        carry = sum / 10;
    }

    if (carry > 0) {
        res[0] = '0' + carry;
        return res;
    }
    else {
        return res + 1;
    }
}

char* Minus(const char* val1, const char* val2) {
    int len1 = strlen(val1);
    int len2 = strlen(val2);

    // Check if val2 is greater than val1
    if (len1 < len2 || (len1 == len2 && strcmp(val1, val2) < 0)) {
        // Swap operands
        std::swap(val1, val2);
        std::swap(len1, len2);
        std::cout << "Result is negative: ";
    }

    int maxLen = std::max(len1, len2);
    int borrow = 0;
    char* res = new char[maxLen + 1];
    res[maxLen] = '\0';

    for (int i = 0; i < maxLen; ++i) {
        int digit1 = (i < len1) ? (val1[len1 - i - 1] - '0') : 0;
        int digit2 = (i < len2) ? (val2[len2 - i - 1] - '0') : 0;
        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        }
        else {
            borrow = 0;
        }
        res[maxLen - i - 1] = '0' + diff;
    }

    // Trim leading zeros
    int start = 0;
    while (res[start] == '0' && start < maxLen - 1) {
        start++;
    }

    if (start > 0) {
        char* trimmedRes = new char[maxLen - start + 1];
        strcpy(trimmedRes, res + start);
        delete[] res;
        return trimmedRes;
    }
    else {
        return res;
    }
}



void Calc(Stack* postfix) {
    Stack* operands = new Stack;
    Init(operands);
    output(postfix);

    while (!IsEmpty(postfix)) {
        char* tmp = new char[strlen(Top(postfix)) + 1];
        tmp = Top(postfix);
        Pop(postfix);

        if (!isOperator(tmp)) {
            Push(operands, tmp);
        }
        else {
            char* operand2 = new char[strlen(Top(operands)) + 1];
            operand2 = Top(operands);
            Pop(operands);

            char* operand1 = new char[strlen(Top(operands)) + 1];
            operand1 = Top(operands);
            Pop(operands);

            switch (tmp[0]) {
            case '+':
                Push(operands, Plus(operand1, operand2));
                break;
            case '-':
                Push(operands, Minus(operand1, operand2));
                break;
            case '*':
                break;
            case '/':
                break;
            }
        }
    }

    cout << "hehe" << endl;
    cout << Top(operands) << endl;
}

int evaluatePostfix(string postfix) {
    stack<int> operands;

    for (char& ch : postfix) {
        if (isalnum(ch)) { // Operand
            operands.push(ch - '0'); // Convert char to int
        }
        else { // Operator
            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();
            switch (ch) {
            case '+':
                operands.push(operand1 + operand2);
                break;
            case '-':
                operands.push(operand1 - operand2);
                break;
            }
        }
    }

    return operands.top();
}

void inputData(char**& data, int& nEquation) {
    char* fileUrl;
    fileUrl = new char[101];
    FILE* file;

    printf("1. Nhap vao duong dan file (vi du: bieuthuc.txt): ");
    scanf("%[^\n]s", fileUrl);
    cin.ignore();
    file = fopen(fileUrl, "r");
    if (file == NULL) {
        printf("Khong the mo file bieu thuc!!! :((\n");
        exit(0);
    }

    int index = 0;
    char tmp[1500];
    // Doc data tu file
    while (fgets(tmp, sizeof(tmp), file) != NULL) {
        printf("%s", tmp);
        index++;
    }

    delete[] fileUrl;
    nEquation = index;
    fclose(file);
}

void clearData(char**& data, int& nEquation) {
    delete[] data;
}

int main() {

    // Doc du lieu tu file
    char** data = new char* [1000];
    int nEquation;
    //inputData(data, nEquation);

    // Xu li tung dong cua file
    Stack* postfix = infixToPostfix("(3-2)+(3+12)");
    output(postfix);
    Calc(postfix);

    // Giai phong bo nho
    clearData(data, nEquation);

	return 0;
}