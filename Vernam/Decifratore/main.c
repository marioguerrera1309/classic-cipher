#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void StringaToBinario(char stringa[], char risultato[]) {
	int l = strlen(stringa);
	int bit;
	for (int i = 0; i < l; i++) {
		for (int j = 7; j >= 0; j--) {
			bit = (stringa[i] >> j) & 1;
			risultato[(i * 8) + (7 - j)] = bit + '0';
		}
	}
	risultato[l * 8] = '\0';
}
void BinarioToStringa(char stringa[], char risultato[]) {
	int l = strlen(stringa);
	char temp[9];
	for (int i = 0; i < l / 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp[j] = stringa[j + (i * 8)];
		}
		temp[8] = '\0';
		//printf("Segmento di 8 bit: %s\n", temp);
		risultato[i] = (char)strtol(temp, 0, 2);
		//printf("Carattere corrispondente: %c\n", risultato[i]);
	}
	risultato[l / 8] = '\0';
	//printf("%s", risultato);
}
int main() {
	char ciphertext_binario[2048];
	char key[255];
	char key_binario[2048];
	char deciphertext_binario[2048];
	char deciphertext[255];
	FILE* f = fopen("cipher.txt", "r");
	FILE* f2 = fopen("key.txt", "r");
	fgets(ciphertext_binario, 255, f);
	printf("Ciphertext in binario: %s\n", ciphertext_binario);
	fgets(key, 255, f2);
	fclose(f);
	fclose(f2);
	StringaToBinario(key, key_binario);
	int l = strlen(ciphertext_binario);
	int l2 = strlen(key_binario);
	if (l != l2) {
		printf("\n\nErrore\n\n");
	}
	int x, y;
	for (int i = 0; i < l; i++) {
		x = (ciphertext_binario[i] - '0');
		y = (key_binario[i] - '0');
		deciphertext_binario[i] = ( x ^ y) + '0';
	}
	deciphertext_binario[l] = '\0';
	printf("Deciphertext in binario: %s\n", deciphertext_binario);
	BinarioToStringa(deciphertext_binario, deciphertext);
	FILE* f3 = fopen("deciphertext.txt", "w");
	fprintf(f3, "%s", deciphertext);
	fclose(f3);
	printf("Deciphertext: %s\n", deciphertext);
	return 0;
}
