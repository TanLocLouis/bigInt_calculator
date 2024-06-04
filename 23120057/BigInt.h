#pragma warning (disable : 4996)

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

inline char* concatCharBeforeString(char character, const char* str) {
    size_t newLength = strlen(str) + 1;

    char* newStr = (char*)malloc((newLength + 1) * sizeof(char));
    if (newStr == NULL) {
        exit(EXIT_FAILURE);
    }
    newStr[0] = character;
    strcpy(newStr + 1, str);

    return newStr;
}

inline char* concatCharAfterString(char character, const char* str) {
    size_t newLength = strlen(str) + 1;

    char* newStr = (char*)malloc((newLength + 1) * sizeof(char));
    if (newStr == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(newStr, str);
    newStr[newLength - 1] = character;
    newStr[newLength] = '\0';
    return newStr;
}

inline char* concatStrings(const char* first, const char* second) {
    size_t newLength = strlen(first) + strlen(second) + 1;

    char* newStr = (char*)malloc(newLength * sizeof(char));
    strcpy(newStr, first);
    strcat(newStr, second);

    return newStr;
}

inline void swapCharPointers(char*& ptr1, char*& ptr2) {
    char* temp = ptr1;
    ptr1 = ptr2;
    ptr2 = temp;
}

inline bool isOperator(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}

struct BigInt {
    char* value;
    char sign;

    BigInt operator-() const {
        BigInt temp;

        temp.value = value;
        if (value != "0") {
            if (sign == '+')
                temp.sign = '-';
            else
                temp.sign = '+';
        }

        return temp;
    }

    BigInt chartoBigInt(const char* num) {
        BigInt res;

        if (strlen(num) == 1 && isOperator(num[0])) {
            res.sign = NULL;
            res.value = new char[2];
            res.value[0] = num[0];
            res.value[1] = '\0';

            return res;
        }

        if (num[0] == '-') {
            res.sign = '-';
            res.value = new char[strlen(num) + 1];
            strcpy(res.value, num + 1);
        }
        else {
            res.sign = '+';
            res.value = new char[strlen(num) + 1];
            strcpy(res.value, num);
        }

        return res;
    }

    BigInt lltoBigInt(const long long& num) {
        BigInt res;
        res.sign = (num < 0) ? '-' : '+';
        // Bo dau - phia truoc
        itoa(abs(num), res.value, 10);

        return res;
    }

    BigInt& operator=(const long long& num) {
        BigInt temp = lltoBigInt(num);
        value = temp.value;
        sign = temp.sign;

        return *this;
    }


    bool operator==(const BigInt& num) const {
        return (sign == num.sign) && (value == num.value);
    }

    BigInt operator+(const BigInt& num) const {
        // Neu 2 so trai dau thi tru nhau
        if (this->sign == '+' && num.sign == '-') {
            BigInt rhs = num;
            rhs.sign = '+';
            return *this - rhs;
        }
        else if (this->sign == '-' && num.sign == '+') {
            BigInt lhs = *this;
            lhs.sign = '+';

            BigInt res = -(lhs - num);
            // neu ket qua la -0 thi doi thanh +0
            if (strlen(res.value) == 1 && res.value[0] == '0') res.sign = '+';
            return res;
        }

        // Khoi tao hai gia tri
        int len = max(strlen(this->value), strlen(num.value));
        char* val1 = new char[len + 1];
        strcpy(val1, this->value);
        char* val2 = new char[len + 1];
        strcpy(val2, num.value);

        // Them so 0 vao so nho hon
        if (strlen(this->value) < strlen(num.value)) {
            char* tmp = new char[strlen(num.value) + 1];
            for (int i = 0; i < (strlen(num.value) - strlen(this->value)); i++) {
                tmp[i] = '0';
            }
            tmp[strlen(num.value) - strlen(this->value)] = '\0';
            strcat(tmp, this->value);
            strcpy(val1, tmp);
            delete[] tmp;
        }
        else {
            char* tmp = new char[strlen(this->value) + 1];
            for (int i = 0; i < (strlen(this->value) - strlen(num.value)); i++) {
                tmp[i] = '0';
            }
            tmp[strlen(this->value) - strlen(num.value)] = '\0';
            strcat(tmp, num.value);
            strcpy(val2, tmp);
            delete[] tmp;
        }

        // Cong hai gia tri
        BigInt result;
        result.value = new char[1];
        result.value[0] = '\0';

        short sum = 0, carry = 0;
        for (int i = strlen(val1) - 1; i >= 0; i--) {
            sum = (val1[i] - '0') + (val2[i] - '0') + carry;

            result.value = concatCharBeforeString((char)((sum % 10) + 48), result.value);
            carry = sum / 10;
        }
        // Neu so du cuoi cung lon hon 1
        if (carry == 1) {
            result.value = concatCharBeforeString('1', result.value);
        }

        // Neu dau cung la - thi ket qua la so am mang dau -
        if (this->sign == '-' && strcmp(result.value, "0") != 0) {
            result.sign = '-';
        }
        else {
            result.sign = '+';
        }

        delete[] val1;
        delete[] val2;

        return result;
    }

    BigInt operator-(const BigInt& num) const {
        // Neu khac dau thi thuc hien phep cong
        if (this->sign == '+' && num.sign == '-') {
            BigInt rhs = num;
            rhs.sign = '+';
            return *this + rhs;
        }
        else if (this->sign == '-' && num.sign == '+') {
            BigInt lhs = *this;
            lhs.sign = '+';
            return -(lhs + num);
        }

        int len = max(strlen(this->value), strlen(num.value));
        char* val1 = new char[len + 1];
        strcpy(val1, this->value);
        char* val2 = new char[len + 1];
        strcpy(val2, num.value);


        BigInt result;
        result.sign = '+';

        // Them so 0 vao so nho hon
        if (strlen(val1) < strlen(val2)) {
            char* tmp = new char[strlen(val2) + 1];
            for (int i = 0; i < (strlen(val2) - strlen(val1)); i++) {
                tmp[i] = '0';
            }
            tmp[strlen(val2) - strlen(val1)] = '\0';
            strcat(tmp, val1);
            strcpy(val1, tmp);
        }
        else {
            char* tmp = new char[strlen(val1) + 1];
            for (int i = 0; i < (strlen(val1) - strlen(val2)); i++) {
                tmp[i] = '0';
            }
            tmp[strlen(val1) - strlen(val2)] = '\0';
            strcat(tmp, val2);
            strcpy(val2, tmp);
        }

        // Cung dau + va so dau nho hon thi result -
        if (this->sign == '+' && strcmp(val1, val2) < 0) {
            result.sign = '-';
        }
        // Cung dau - va abs so dau lon hon abs so sau thi result -
        if (this->sign == '-' && strcmp(val1, val2) < 0) {
            result.sign = '-';
        }


        // So lon nhat phai la so dau tien
        if (strcmp(val1, val2) < 0) {
            swapCharPointers(val1, val2);
        }

        // Tru hai gia tri
        result.value = new char[1];
        result.value[0] = '\0';

        int m = strlen(this->value);
        int n = strlen(num.value);

        int diff = 0;
        int i, j;
        for (i = max(m, n) - 1; i >= 0; i--) {
            diff = val1[i] - val2[i];
            if (diff < 0) {
                // Tim mot so khac 0 de muon
                for (j = i - 1; j >= 0; j--) {
                    if (val1[j] != '0') {
                        val1[j]--;
                        break;
                    }
                }
                j++;
                // Lay so muon
                while (j != i) {
                    val1[j] = '9';
                    j++;
                }
                diff += 10;
            }
            result.value = concatCharBeforeString((diff + 48), result.value);
        }

        // Loai bo so 0 o dau
        while (result.value[0] == '0') {
            result.value = result.value + 1;
        }
        // Neu khong con so nao thi ket qua la 0
        if (strlen(result.value) == 0) {
            result.value = concatCharAfterString('0', result.value);
        }

        return result;
    }

    BigInt operator*(const BigInt& num) const {
        BigInt res;
        res.value = new char[2];
        strcpy(res.value, "0");
        res.sign = '+';

        int n = strlen(num.value);

        for (int i = n - 1; i >= 0; i--) {
            int carry = 0;

            int digit = num.value[i] - '0';
            BigInt tmp;
            tmp.value = new char[strlen(value) + n - i + 1];
            strcpy(tmp.value, value);

            for (int j = strlen(value) - 1; j >= 0; j--) {
                int product = (tmp.value[j] - '0') * digit + carry;
                tmp.value[j] = product % 10 + '0';
                carry = product / 10;
            }

            if (carry > 0) {
                char* newTmp = new char[strlen(tmp.value) + 2];
                newTmp[0] = carry + '0';
                strcpy(newTmp + 1, tmp.value);
                delete[] tmp.value;
                tmp.value = newTmp;
            }

            for (int k = n - i - 1; k > 0; k--) {
                tmp.value = concatCharAfterString('0', tmp.value);
            }

            res = res + tmp;
        }

        // Xet dau
        if (sign == num.sign)
            res.sign = '+';
        else
            res.sign = '-';

        return res;
    }

    BigInt operator/(const BigInt& num) const {
        BigInt abs_num = num;
        abs_num.sign = '+';

        BigInt res;
        res.value = new char[1];
        res.value[0] = '\0';
        res.sign = '+';

        // Cac truong hop dac biet
        // So nho chia so lon
        if (strlen(this->value) < strlen(num.value)) {
            BigInt tmp = tmp.chartoBigInt("0");
            return tmp;
        }
        if (strlen(this->value) == strlen(num.value)) {
            if (strcmp(this->value, num.value) < 0) {
                BigInt tmp = tmp.chartoBigInt("0");
                return tmp;
            }
        }

        char* val1 = new char[strlen(this->value) + 1];
        strcpy(val1, this->value);
        char* val2 = new char[strlen(num.value) + 1];
        strcpy(val2, num.value);

        int m = strlen(this->value);
        int n = strlen(num.value);

        int i = 0;
        BigInt remain;
        remain.value = new char[1];
        remain.value[0] = '\0';
        remain.sign = '+';

        // Them so vao so du cho du
        while (strlen(remain.value) < n) {
            remain.value = concatCharAfterString(val1[i], remain.value);
            i++;
        }
        // Neu van nho hon thi lay them 1
        if (strcmp(remain.value, val2) < 0) {
            remain.value = concatCharAfterString(val1[i], remain.value);
            i++;
        }
        bool notFirst = false;
        while (i < m || !notFirst) {
            // Lan dau tien thi khong can lay them so tu so bi chia vao so du
            if (notFirst) {
                remain.value = concatCharAfterString(val1[i], remain.value);
                i++;
            }
            notFirst = true;

            // Them so 0 vao ket qua neu so du van nho hon so chia
            if (strlen(remain.value) < n) {
                res.value = concatCharAfterString('0', res.value);
                continue;
            }
            if (strlen(remain.value) == n && strcmp(remain.value, val2) < 0) {
                res.value = concatCharAfterString('0', res.value);
                continue;
            }
            // Tinh so don
            int count = 0;
            while (remain.sign == '+') {
                remain = remain - abs_num;
                count++;
            }
            // Bu lai phan bi am
            // This damm shit is so complicated :v
            remain = remain + abs_num;
            res.value = concatCharAfterString((char)(count - 1 + 48), res.value);
        }

        // Xet dau
        if (sign == num.sign)
            res.sign = '+';
        else
            res.sign = '-';

        return res;
    }
};
