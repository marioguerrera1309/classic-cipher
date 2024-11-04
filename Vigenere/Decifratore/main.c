#define _CRT_SECURE_NO_WARNINGS
#define DIM 26
#define MAX 256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void generaTabella(char tabella[DIM][DIM]) {
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			tabella[i][j] = 'a' + (i + j) % DIM;
		}
	}
}
void correggiChiave(char chiave[], char ciphertext[]) {
	int l = strlen(ciphertext);
	int lchiave = strlen(chiave);
	if (lchiave < l) {
		for (int i = 0; i < l - lchiave; i++) {
			chiave[lchiave + i] = chiave[i];
		}
		chiave[l] = '\0';
	}
	else {
		chiave[l] = '\0';
	}
}
int main() {
	char tabella[DIM][DIM];
	char chiave[MAX];
	char ciphertext[MAX];
	char nome[25];
	char decipheredtext_[MAX];
	FILE* key = fopen("key.txt", "r");
	fscanf(key, "%s", chiave);
	fclose(key);
	generaTabella(tabella);
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++)
			printf("%c", tabella[i][j]);
		printf("\n");
	}
	FILE* cipher = fopen("cipher.txt", "r");	
	fscanf(cipher, "%s", ciphertext);
	correggiChiave(chiave, ciphertext);
	printf("Chiave corretta: %s\n", chiave);
	fclose(cipher);
	for (int i = 0; i < strlen(ciphertext); i++) {
		decipheredtext_[i] = 'a' + (26 + (ciphertext[i] - chiave[i])) % DIM;
	}
	decipheredtext_[strlen(ciphertext)] = '\0';
	printf("Testo decifrato: %s\n", decipheredtext_);
	FILE* decipheredtext = fopen("decipheredtext.txt", "w");
	fprintf(decipheredtext, "%s", decipheredtext_);
	fclose(decipheredtext);
	return 0;
}