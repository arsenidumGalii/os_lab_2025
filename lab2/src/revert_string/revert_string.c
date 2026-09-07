#include <stdlib.h>
#include <string.h>
#include "revert_string.h"

void RevertString(char *str)
{
	int length = strlen(str);
	char* revertString = malloc(sizeof(char) * (length + 1));
	for(int i = 0; i < length; i++){
		revertString[i] = str[length - i - 1];
	}
	for(int i = 0; i < length; i++){
		*(str + i) = revertString[i];
	}
	free(revertString);
}

