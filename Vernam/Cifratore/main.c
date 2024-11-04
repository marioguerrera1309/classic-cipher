#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

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
void StringaToBinario(char stringa[]) {
	int l = strlen(stringa);
	char *risultato;
	risultato = (char*)malloc(l * 8 + 1);
	int bit;
	for (int i = 0; i < l; i++) {
		for (int j = 7; j >= 0; j--) {
			bit = (stringa[i] >> j) & 1;
			risultato[(i * 8) + (7 - j)] = bit + '0';
		}
	}
	risultato[l * 8] = '\0';
	strcpy(stringa, risultato);
}
int main() {
	char plaintext[255];
	char ciphertext_binario[2048];
	char nome[25];
	FILE* f = fopen("plaintext.txt", "r");
	fgets(plaintext, 255, f);
	fclose(f);
	CorreggiPlaintext(plaintext);
	printf("Plaintext corretto: %s\n", plaintext);
	int l = strlen(plaintext);
	StringaToBinario(plaintext);
	printf("Plaintext convertito: %s\n", plaintext);
	printf("Quante chiavi casuali vuoi creare di %d caratteri? ", l);
	int n;
	scanf("%d", &n);
	FILE* keys = fopen("keys.txt", "w");
	char chiave[2048];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < l; j++) {
			chiave[j] = rand() % 26 + 'a';
		}
		chiave[l] = '\0';
		printf("Chiave %d: %s\n", i + 1, chiave);
		fprintf(keys, "%s\n", chiave);
		StringaToBinario(chiave);
		for (int j = 0; j < strlen(plaintext); j++) {
			ciphertext_binario[j] = (plaintext[j] - '0') ^ (chiave[j] - '0') + '0';
		}
		ciphertext_binario[strlen(plaintext)] = '\0';
		printf("Ciphertext binario %d: %s\n", i + 1, ciphertext_binario);
		if (i < 9) {
			sprintf(nome, "cipher_0%d.txt", i + 1);
		}
		else {
			sprintf(nome, "cipher_%d.txt", i + 1);
		}
		f = fopen(nome, "w");
		fprintf(f, "%s", ciphertext_binario);
		fclose(f);
	}
	return 0;
}