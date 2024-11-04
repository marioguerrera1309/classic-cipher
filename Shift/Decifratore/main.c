#define _CRT_SECURE_NO_WARNINGS
#define MAX 256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	int chiave;
	int x;
	char ciphertext[MAX];
	char decipheredtext[MAX];
	char nome[25];
	FILE* key = fopen("key.txt", "r");
	fscanf(key, "%d", &chiave);
	fclose(key);
	FILE* ciphertext_ = fopen("cipher.txt", "r");
	fscanf(ciphertext_, "%s", ciphertext);
	fclose(ciphertext_);
	for (int i = 0; i < strlen(ciphertext); i++) {
		x = (ciphertext[i] - 'a' - chiave);
		if(x<0)
			decipheredtext[i] = (x % 26 +26) + 'a';
		else
			decipheredtext[i] = (x % 26) + 'a';
	}
	decipheredtext[strlen(ciphertext)] = '\0';
	FILE* decipheredtext_ = fopen("decipheredtext.txt", "w");
	printf("%s\n", decipheredtext);
	fprintf(decipheredtext_, "%s", decipheredtext);
	fclose(decipheredtext_);
	return 0;
}