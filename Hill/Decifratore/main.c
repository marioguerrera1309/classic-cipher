#define MAX 256
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<gsl/gsl_matrix.h>
#include<gsl/gsl_permutation.h>
#include<gsl/gsl_linalg.h>
#include<math.h>

int main() {
	int** k;
	FILE *key=fopen("key.txt", "r");
	int temp, x=0, l, l2;
        while (fscanf(key, "%d", &temp) == 1) {
                x++;
        }
        l=sqrt(x);
        k = (int**)malloc(l * sizeof(int*));
	for (int i = 0; i < l; i++) {
	        k[i] = (int*)malloc(l * sizeof(int));
	}
	rewind(key);
	for (int i = 0; i < l; i++) {
                for (int j = 0; j < l; j++) {
                        fscanf(key, "%d", &k[i][j]);
                }
        }
        /*
        for (int i = 0; i < l; i++) {
                for (int j = 0; j < l; j++) {
                        printf("%d ", k[i][j]);
                }
                printf("\n");
        }*/
        gsl_matrix *matrice=gsl_matrix_alloc(l, l);
	gsl_matrix *inversa=gsl_matrix_alloc(l, l);
	gsl_permutation *permutazioni = gsl_permutation_alloc(l);
	gsl_vector *vettoreC=gsl_vector_alloc(l);
	gsl_vector *vettoreD=gsl_vector_alloc(l);
	for(int i=0 ; i<l ; i++) {
                for(int j=0 ; j<l ; j++) {
                      gsl_matrix_set(matrice, i, j, (double)k[i][j]);  
                }
        }
        int segno;
        gsl_linalg_LU_decomp(matrice, permutazioni, &segno);
        gsl_linalg_LU_invert(matrice, permutazioni, inversa);
        /*printf("La matrice inversa e': \n");
        for(int i=0 ; i<l ; i++) {
                for(int j=0 ; j<l ; j++) {
                      printf("%.1f ", gsl_matrix_get(inversa, i, j));
                }
                printf("\n");
        }*/
        FILE *cipher=fopen("cipher.txt", "r");
        char cipher_[MAX];
        x=0;
        fscanf(cipher, "%s", cipher_);
        l2=strlen(cipher_);
        printf("Ciphertext: %s\n", cipher_);
        if(l!=l2) {
                printf("\nErrore\n");
        }
        int *ciphervet;
        ciphervet=(int*)malloc(l2*sizeof(int));
        for(int i = 0; i < l2; i++) {
                ciphervet[i]=cipher_[i]-'a'+1;
                printf("Cipher_[%d]=%c->%d\n", i, cipher_[i], ciphervet[i]);
                gsl_vector_set(vettoreC, i, (double)ciphervet[i]);
        }
        printf("Ciphervet: ");
        for(int i = 0; i < l2; i++) {
                printf("%d ", ciphervet[i]);
        }
        gsl_blas_dgemv(CblasTrans, 1.0, inversa, vettoreC, 0.0, vettoreD);
        int *deciphervet=(int*)malloc(l2 * sizeof(int*));
        printf("\nDeciphervet: ");
        for(int i = 0; i < l2; i++) {
                deciphervet[i]=(int)(gsl_vector_get(vettoreD, i))%26;
                if(deciphervet[i]<0) {
                        deciphervet[i]+=26;
                }
                printf("%d ", deciphervet[i]);
        }
        char deciphertext[MAX];
        for(int i = 0; i < l2; i++) {
                deciphertext[i]=deciphervet[i]+'a';
        }
        printf("\nDeciphertext: %s\n", deciphertext);
}
