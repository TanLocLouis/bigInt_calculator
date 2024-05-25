#pragma warning(disable : 4996)

#include "utils.h"
#include <string.h>

void eliminateSpace(char* s) {
	char* ans = new char[strlen(s) + 1];

	int index = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] != char(32)) {
			ans[index] = s[i];
			index++;
		}
	}
	ans[index] = '\0';

	strcpy(s, ans);
}