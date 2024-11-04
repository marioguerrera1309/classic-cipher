#define MAX 256
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_permutation.h>
#include<gsl/gsl_linalg.h>
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
	risultato[j-1] = '\0';
	for (int i = 0; i < strlen(risultato); i++) {
		if (risultato[i] >= 'A' && risultato[i] <= 'Z') {
			risultato[i] = risultato[i] + 32;
		}
	}
	strcpy(plaintext, risultato);
}
int main() {
	char plaintext_[MAX];
	FILE* plaintext = fopen("plaintext.txt", "r");
	fgets(plaintext_, MAX*sizeof(char), plaintext);
	CorreggiPlaintext(plaintext_);
	printf("Plaintext corretto: %s\n", plaintext_);
	int l = strlen(plaintext_);
	fclose(plaintext);
	int* p;
	p = (int*)malloc(l * sizeof(int*));
	gsl_vector *vettoreP=gsl_vector_alloc(l);
	for (int i = 0; i < l; i++) {
		p[i] = plaintext_[i] - 'a';
		//printf("%c %d\n",plaintext_[i], p[i]);
		gsl_vector_set(vettoreP, i, (double)p[i]);
	}	
	//printf("ciao: %c, l=%d\n", plaintext_[l-1], l);
	int** k;
	double det=1;
	k = (int**)malloc(l * sizeof(int*));
	for (int i = 0; i < l; i++) {
	        k[i] = (int*)malloc(l * sizeof(int));
	}
	srand(time(0));
	gsl_matrix *matrice=gsl_matrix_alloc(l, l);
	gsl_matrix *inversa=gsl_matrix_alloc(l, l);
	gsl_permutation *permutazioni = gsl_permutation_alloc(l);
	gsl_vector *vettoreR=gsl_vector_alloc(l);
	FILE *keys=fopen("keys.txt", "w");
	for(int x = 0; x < 5; x++) {
	        do {
                        for (int i = 0; i < l; i++) {
	                        for (int j = 0; j < l; j++) {
		                        k[i][j] = (int)rand() % 10;
	                                //printf("%d ", k[i][j]);
	                        }
	                        //printf("\n");
                        }
                        for(int i=0 ; i<l ; i++) {
                                for(int j=0 ; j<l ; j++) {
                                      gsl_matrix_set(matrice, i, j, (double)k[i][j]);  
                                }
                        }
                        int segno;
                        gsl_linalg_LU_decomp(matrice, permutazioni, &segno);
                        det = gsl_linalg_LU_det(matrice, segno);
	        } while(det == 0);
	        printf("Chiave_0%d:\n", x+1);
	        fprintf(keys, "Chiave_0%d\n", x+1);
	        for (int i = 0; i < l; i++) {
		        for (int j = 0; j < l; j++) {
		                printf("%d ", k[i][j]);
		                fprintf(keys, "%d ", k[i][j]);
		        }
		        printf("\n");
		        fprintf(keys, "\n");
	        }
	        fprintf(keys, "\n");
	        //printf("Determinante: %.2f\n", det);
	        /*
	        gsl_linalg_LU_invert(matrice, permutazioni, inversa);
	        printf("La matrice inversa e': ");
	        for(int i=0 ; i<l ; i++) {
                        for(int j=0 ; j<l ; j++) {
                              printf("%.1f ", gsl_matrix_get(inversa, i, j));
                        }
                        printf("\n");
                }
                */
                gsl_blas_dgemv(CblasNoTrans, 1.0, matrice, vettoreP, 0.0, vettoreR);
                int *ciphervet=(int*)malloc(l * sizeof(int*));
                //printf("Vettore risultato:\n");
                for(int i = 0; i < l; i++) {
                        ciphervet[i]=(int)(gsl_vector_get(vettoreR, i))%26;
                        if(ciphervet[i]<0) {
                                ciphervet[i]+=26;
                        }
                        //printf("%d ", ciphervet[i]);
                }
                //printf("\n");
                char cipher_[MAX];
                FILE *cipher;
                char nome[25];
                sprintf(nome, "cipher_0%d.txt", x+1);
                cipher=fopen(nome, "w");
                for(int i = 0; i < l; i++) {
                        cipher_[i]=ciphervet[i]+'a';
                }
                printf("Ciphertext 0%d: %s", x+1, cipher_);
                fprintf(cipher, "%s", cipher_);
                printf("\n");
        }
	return 0;
}
