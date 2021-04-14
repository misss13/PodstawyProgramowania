#include <stdio.h>
#include <stdlib.h>

void encrypt(char* text, int len) {
	int key, sp = 0;
	for (key = 0; key < len; key++)
		if (text[key] == ' ' && key == sp)
			sp++;
		else if (text[key] == ' ')
			break;
		
	key -= sp;
	
	for (int i = 0; i < len; i++)
		if (text[i] != ' ') {
			if (text[i] >= 97 && text[i] <= 122)
				text[i] = ((text[i] - 97 + key) % 26) + 97;
			else if (text[i] >= 65 && text[i] <= 90)
				text[i] = ((text[i] - 65 + key) % 26) + 65;
		}
}

char* getEncryptedLine() {
	char *buffer = NULL;
	int len;
	int r = getline(&buffer, &len, stdin);
    
	if (r != -1) {
		encrypt(buffer, r - 1);
		return buffer;
	}
	else {
		free(buffer);
		return NULL;
	}
}

int main() {
	while (1) {
		char *buffer = getEncryptedLine();
		if (buffer == NULL)
			return 0;
		
		printf("%s", buffer);
		free(buffer);
	}
}
