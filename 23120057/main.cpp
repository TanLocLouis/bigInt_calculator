#pragma warning(disable: 4996)
#include "Stack.h"
#include "utils.h"

const int MAX_DIGIT = 1000;
const int MAX_ROW = 1000;

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
        // Xu li so am
        if (infix[index] == '(' && infix[index + 1] == '-') {
            start = index + 1;
            while (true) {
                if (infix[index] == ')') {
                    index++;
                    break;
                }
                index++;
            }

            end = index - 2;
            // split value
            char* operand = (char*)malloc((end - start + 1 + 1) * sizeof(char));
            strncpy(operand, infix + start, (end - start + 1));
            operand[end - start + 1] = '\0';

            BigInt tmp = tmp.chartoBigInt(operand);
            Push(postfix, tmp);

            continue;
        }

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

                BigInt tmp = tmp.chartoBigInt(operand);
                Push(postfix, tmp);
            }
        }
        // (
        else if (infix[index] == '(') {
            char* operand = (char*) malloc(2 * sizeof(char));
            operand[0] = infix[index];
            operand[1] = '\0';

            BigInt tmp = tmp.chartoBigInt(operand);
            Push(operators, tmp);
        }
        // )
        else if (infix[index] == ')'){
            while (!IsEmpty(operators) && strcmp(Top(operators).value, "(") != 0) {
                Push(postfix, Top(operators));
                Pop(operators);
            }
            Pop(operators);
        }
        // +=*/
        else {
            while (!IsEmpty(operators) && precedence(infix[index]) <= precedence(Top(operators).value[0])) {
                Push(postfix, Top(operators));
                Pop(operators);
            }
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = infix[index];
            operand[1] = '\0';

            BigInt tmp = tmp.chartoBigInt(operand);
            Push(operators, tmp);
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

void Calc(Stack* postfix, BigInt* result, int& nResult) {
    Stack* operands = new Stack;
    Init(operands);

    while (!IsEmpty(postfix)) {
        char* tmp = new char[strlen(Top(postfix).value) + 1];
        tmp = Top(postfix).value;
        char tmp_sign = Top(postfix).sign;
        Pop(postfix);

        if (!isOperator(tmp)) {
            BigInt tmp1 = tmp1.chartoBigInt(tmp);
            tmp1.sign = tmp_sign;
            Push(operands, tmp1);
        }
        else {
            BigInt operand1 = Top(operands);
            Pop(operands);

            BigInt operand2 = Top(operands);
            Pop(operands);

            switch (tmp[0]) {
            case '+':
                Push(operands, operand2 + operand1);
                break;
            case '-':
                Push(operands, operand2 - operand1);
                break;
            case '*':
                Push(operands, operand2 * operand1);
                break;
            case '/':
                BigInt tmp = operand2 / operand1;
                Push(operands, tmp);
                break;
            }
        }
    }

    result[nResult] = Top(operands);
    nResult++;

    printf("%c%s\n", Top(operands).sign, Top(operands).value);
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
    char tmp[MAX_DIGIT];
    // Doc data tu file
    while (fgets(tmp, sizeof(tmp), file) != NULL) {
        data[index] = new char[strlen(tmp) + 1];

        // fgets se lay ki tu \n
        // nen phai loai bo
        if (tmp[strlen(tmp) - 1] == '\n')
            tmp[strlen(tmp) - 1] = '\0';

        eliminateSpace(tmp);

        strcpy(data[index], tmp);
        index++;
    }

    delete[] fileUrl;
    nEquation = index;
    fclose(file);
}

void outputData(BigInt* result, int nResult) {
    FILE* file;
    char fileUrl[101];
    printf("2. Nhap vao duong dan ketqua (vi du: ketqua.txt): ");
    scanf("%[^\n]s", fileUrl);
    cin.ignore();
    file = fopen(fileUrl, "w");

    if (file == NULL) {
        printf("Khong the mo file bieu thuc!!! :((\n");
        exit(0);
    }

    for (int i = 0; i < nResult; i++) {
        fprintf(file, "%c%s\n", result[i].sign, result[i].value);
    }

    fclose(file);
}

void clearData(char**& data, int& nEquation, BigInt*& result, int& nResult) {
    delete[] data;
    delete[] result;
}


int main() {

    // Doc du lieu tu file
    char** data = new char* [MAX_DIGIT];
    int nEquation = 0;
    inputData(data, nEquation);

    // Xu li tung dong cua file
    BigInt* result = new BigInt[MAX_ROW];
    int nResult = 0;

    for (int i = 0; i < nEquation; i++) {
        Stack* postfix = infixToPostfix(data[i]);
        Calc(postfix, result, nResult);
    }

    // Ghi du lieu ra file
    outputData(result, nResult);

    // Giai phong bo nho
    clearData(data, nEquation, result, nResult);

	return 0;
}