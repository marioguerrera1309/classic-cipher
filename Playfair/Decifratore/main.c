#define _CRT_SECURE_NO_WARNINGS
#define MAX 256
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void generaTabellaPlayfair(char chiave[], char tabella[5][5]) {
	char alfabeto[] = "abcdefghiklmnopqrstuvwxyz";
	int k = 0, i, j;
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
	int i, j;
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
void decifraPlayfair(char tabella[5][5], char* decipheredtext, char* ciphertext) {
	int i, j;
	char a, b;
	int* xa, * xb;
	int l;
	xa = (int*)malloc(2 * sizeof(int));
	xb = (int*)malloc(2 * sizeof(int));
	for (i = 0; i < strlen(ciphertext); i += 2) {
		a = ciphertext[i];
		b = ciphertext[i + 1];
		cerca(tabella, a, b, xa, xb);
		l = strlen(decipheredtext);
		if (xa[0] == xb[0]) {
			if ((xa[1] - 1) < 0) {
				xa[1] = 5;
			}
			else if ((xb[1] - 1) < 0) {
				xb[1] = 5;
			}
			decipheredtext[l] = tabella[xa[0]][xa[1] - 1];
			decipheredtext[l + 1] = tabella[xb[0]][xb[1] - 1];
			decipheredtext[l + 2] = '\0';
		}
		else if (xa[1] == xb[1]) {
			if ((xa[0] - 1) < 0) {
				xa[0] = 5;
			}
			else if ((xb[0] - 1) < 0) {
				xb[0] = 5;
			}
			decipheredtext[l] = tabella[xa[0] - 1][xa[1]];
			decipheredtext[l + 1] = tabella[xb[0] - 1][xb[1]];
			decipheredtext[l + 2] = '\0';
		}
		else {
			decipheredtext[l] = tabella[xa[0]][xb[1]];
			decipheredtext[l + 1] = tabella[xb[0]][xa[1]];
			decipheredtext[l + 2] = '\0';

		}
	}

}
void CorreggiChiave(char chiave[], int cont) {
	int j = 0, k = 0, flag = 0;
	char temp[MAX];
	for (int i = 0; i < cont; i++) {
		strcpy(temp, "");
		j = 0;
		for (int z = 0; z < strlen(chiave); z++) {
			flag = 0;
			k = 0;
			while (k < j && flag == 0) {
				if (chiave[z] == temp[k]) {
					flag = 1;
				}
				k++;
			}
			if (flag == 0) {
				temp[j] = chiave[z];
				j++;
			}
		}
		temp[j] = '\0';
		for (int i = 0; i < strlen(temp); i++) {
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				temp[i] = temp[i] + 32;
			}
		}
		strcpy(chiave, temp);
	}
}
int main() {
	FILE* key, * cipher, * decipheredtext;
	char tabella[5][5];
	int e = 0;
	int j = 0, k = 0, flag = 0;
	char temp[MAX];
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tabella[i][j] = ' ';
		}
	}
	char chiave[MAX];
	char plaintext_[MAX];
	key = fopen("key.txt", "r");
	fscanf(key, "%s", chiave);
	for (int z = 0; z < strlen(chiave); z++) {
		flag = 0;
		k = 0;
		while (k < j && flag == 0) {
			if (chiave[z] == temp[k]) {
				flag = 1;
			}
			k++;
		}
		if (flag == 0) {
			temp[j] = chiave[z];
			j++;
		}
	}
	temp[j] = '\0';
	for (int i = 0; i < strlen(temp); i++) {
		if (temp[i] >= 'A' && temp[i] <= 'Z') {
			temp[i] = temp[i] + 32;
		}
	}
	strcpy(chiave, temp);
	fclose(key);
	cipher = fopen("cipher.txt", "r");
	char ciphertext[MAX] = "";
	char decipheredtext_[MAX] = "";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			tabella[i][j] = ' ';
		}
	}
	generaTabellaPlayfair(chiave, tabella);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			printf("%c ", tabella[i][j]);
		}
		printf("\n");
	}
	fscanf(cipher, "%s", ciphertext);
	fclose(cipher);
	decifraPlayfair(tabella, decipheredtext_, ciphertext);
	decipheredtext = fopen("decipheredtext.txt", "w");
	fprintf(decipheredtext, "%s", decipheredtext_);
	fclose(decipheredtext);
	printf("%s\nDecifrazione completata\n", decipheredtext_);
	return 0;
}
