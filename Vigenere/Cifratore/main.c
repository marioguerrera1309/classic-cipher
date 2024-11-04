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
void correggiChiave(char chiave[], char plaintext[]) {
	int l = strlen(plaintext);
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
void CorreggiPlaintext(char plaintext[]) {
	int lunghezza = strlen(plaintext);
	char risultato[256];
	int j = 0, i = 0;
	while (i < lunghezza) {
		if (plaintext[i] == ' ') {
			i++;
		}
		else {
			risultato[j++] = plaintext[i];
			i++;
		}
	}
	risultato[j] = '\0';
	for (int i = 0; i < strlen(risultato); i++) {
		if (risultato[i] >= 'A' && risultato[i] <= 'Z') {
			risultato[i] = risultato[i] + 32;
		}
	}
	strcpy(plaintext, risultato);
}
int main() {
	char tabella[DIM][DIM];
	char chiave[MAX][MAX];
	char plaintext_[MAX];
	char ciphertext[MAX];
	char nome[25];
	int cont = 0, i = 0;
	FILE* keys = fopen("keys.txt", "r");
	while(fscanf(keys, "%s", chiave[i]) != EOF) {
		i++;
	}
	fclose(keys);
	cont = i;
	generaTabella(tabella);
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++)
			printf("%c", tabella[i][j]);
		printf("\n");
	}
	FILE* plaintext = fopen("plaintext.txt", "r");
	fgets(plaintext_, MAX, plaintext);
	fclose(plaintext);
	printf("Plaintext originale: %s\n", plaintext_);
	CorreggiPlaintext(plaintext_);
	printf("Plaintext corretto: %s\n", plaintext_);
	for (int j = 0; j < cont; j++) {
		correggiChiave(chiave[j], plaintext_);
		printf("Chiave corretta: %s\n", chiave[j]);
		for (int i = 0; i < strlen(plaintext_); i++) {
			ciphertext[i] = tabella[plaintext_[i] - 'a'][chiave[j][i] - 'a'];
		}
		ciphertext[strlen(plaintext_)] = '\0';
		if (j < 9) {
			sprintf(nome, "cipher_0%d.txt", j + 1);
		}
		else {
			sprintf(nome, "cipher_%d.txt", j + 1);
		}
		printf("Cipher_0%d: %s\n", j+1, ciphertext);
		FILE* cipher = fopen(nome, "w");
		fprintf(cipher, "%s", ciphertext);
		fclose(cipher);
	}
	return 0;
}