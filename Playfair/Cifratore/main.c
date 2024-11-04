#define _CRT_SECURE_NO_WARNINGS
#define MAX 256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void generaTabellaPlayfair(char chiave[], char tabella[5][5]) {
	char alfabeto[] = "abcdefghiklmnopqrstuvwxyz";
	int k = 0;
	int flag = 0;
	int x = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (k < strlen(chiave)) {
				tabella[i][j] = chiave[k];
				k++;
			}
			else {
				flag = 0;
				while (flag == 0) {
					for (int z = 0; z < strlen(chiave); z++) {
						if (alfabeto[x] == chiave[z]) {
							flag = 1;
						}
					}
					if (flag == 0) {
						tabella[i][j] = alfabeto[x];
						flag = 1;
						x++;
					}
					else {
						flag = 0;
						x++;
					}
				}
			}
		}

	}
}
void cerca(char tabella[5][5], char a, char b, int* xa, int* xb) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (tabella[i][j] == a) {
				xa[0] = i;
				xa[1] = j;
			}
			if (tabella[i][j] == b) {
				xb[0] = i;
				xb[1] = j;
			}
		}
	}
}
void cifraPlayfair(char tabella[5][5], char* plaintext, char* ciphertext) {
	char a, b;
	int* xa, * xb;
	int l;
	xa = (int*)malloc(2 * sizeof(int));
	xb = (int*)malloc(2 * sizeof(int));
	for (int i = 0; i < strlen(plaintext); i += 2) {
		a = plaintext[i];
		b = plaintext[i + 1];
		cerca(tabella, a, b, xa, xb);
		l = strlen(ciphertext);
		if (xa[0] == xb[0]) {
			if ((xa[1] + 1) > 4) {
				xa[1] = -1;
			}
			else if ((xb[1] + 1) > 4) {
				xb[1] = -1;
			}
			ciphertext[l] = tabella[xa[0]][xa[1] + 1];
			ciphertext[l + 1] = tabella[xb[0]][xb[1] + 1];
			ciphertext[l + 2] = '\0';
		}
		else if (xa[1] == xb[1]) {
			if ((xa[0] + 1) > 4) {
				xa[0] = -1;
			}
			else if ((xb[0] + 1) > 4) {
				xb[0] = -1;
			}
			ciphertext[l] = tabella[xa[0] + 1][xa[1]];
			ciphertext[l + 1] = tabella[xb[0] + 1][xb[1]];
			ciphertext[l + 2] = '\0';
		}
		else {
			ciphertext[l] = tabella[xa[0]][xb[1]];
			ciphertext[l + 1] = tabella[xb[0]][xa[1]];
			ciphertext[l + 2] = '\0';

		}
	}
	free(xa);
	free(xb);
}
void CorreggiPlaintext(char plaintext[]) {
	int lunghezza = strlen(plaintext);
	char risultato[256];
	int j = 0, i = 0;
	while(i < lunghezza) {
		if (plaintext[i] == ' ') {
			i++;
		}
		else {
			risultato[j++] = plaintext[i];
			if (plaintext[i] == plaintext[i + 1]) {
				risultato[j++] = 'x';
			}
			i++;
		}
	}
	risultato[j] = '\0';
	for (int i = 0; i < strlen(risultato); i++) {
		if (risultato[i]>='A' && risultato[i]<='Z') {
			risultato[i] = risultato[i] + 32;
		}
	}
	strcpy(plaintext, risultato);
}
void CorreggiChiave(char chiave[MAX][MAX], int cont) {
	int j = 0, k = 0, flag = 0;
	char temp[MAX];
	for (int i = 0; i < cont; i++) {
		strcpy(temp, "");
		j = 0;
		for (int z = 0; z < strlen(chiave[i]); z++) {
			flag = 0;
			k = 0;
			while(k < j && flag == 0) {
				if (chiave[i][z] == temp[k]) {
					flag = 1;
				}
				k++;
			}
			if (flag == 0) {
				temp[j] = chiave[i][z];
				j++;
			}
		}
		temp[j] = '\0';
		for (int i = 0; i < strlen(temp); i++) {
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				temp[i] = temp[i] + 32;
			}
		}
		strcpy(chiave[i], temp);
	}
}
int main() {
	FILE* plaintext, * keys, * cipher_xx;
	char tabella[5][5];
	int e = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tabella[i][j] = ' ';
		}
	}
	char chiave[MAX][MAX];
	char plaintext_[MAX];
	char ciphertext[MAX];
	keys = fopen("keys.txt", "r");
	int cont = 0;
	while (fscanf(keys, "%s", chiave[cont]) != EOF) {
		cont++;
	}
	fclose(keys);
	CorreggiChiave(chiave, cont);
	plaintext = fopen("plaintext.txt", "r");
	fgets(plaintext_, MAX, plaintext);
	CorreggiPlaintext(plaintext_);
	fclose(plaintext);
	printf("Plaintext: %s\n\n", plaintext_);
	for (int x = 0; x < cont; x++) {
		strcpy(ciphertext, "");
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				tabella[i][j] = ' ';
			}
		}
		generaTabellaPlayfair(chiave[x], tabella);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				printf("%c ", tabella[i][j]);
			}
			printf("\n");
		}
		cifraPlayfair(tabella, plaintext_, ciphertext);
		char nome[MAX];
		if (x < 9) {
			sprintf(nome, "cipher_0%d.txt", x + 1);
		}
		else {
			sprintf(nome, "cipher_%d.txt", x + 1);
		}
		cipher_xx = fopen(nome, "w");
		fprintf(cipher_xx, "%s", ciphertext);
		fclose(cipher_xx);
		printf("Ciphertext: %s\n", ciphertext);
		printf("Cifratura %d con chiave %s completata\n\n", x + 1, chiave[x]);
	}
	return 0;
}