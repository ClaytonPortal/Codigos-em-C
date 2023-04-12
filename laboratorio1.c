#include <stdio.h>
#include <pthread.h>

#define TAM 10000

long vetor[TAM];
long copiaVetor[TAM];

void *multiVetor(void *id) {
    long threadID = *(long *) id;
    
    if (threadID == 0){
        for (long i = 0; i < TAM; i+=2){
            vetor[i] =  2*vetor[i];
        }
    }
    if (threadID == 1){
        for (long i = 1; i < TAM; i+=2){
            vetor[i] =  2*vetor[i];
        }
    }
    
    pthread_exit(NULL);
}

int main(void) {
    for (long i = 0; i < TAM; i++){
        vetor[i] = i+1;
        copiaVetor[i] = vetor[i];
    }
    
    pthread_t T[2];
    long idthreads[2];

    for(long i = 0; i < 2; i++){
        idthreads[i] = i;
        pthread_create(&T[i], NULL, multiVetor, (void *) &idthreads[i]);
    }

    for(long i = 0; i < 2; i++){
        pthread_join(T[i], NULL);
    }
    
    for (long i = 0; i < TAM; i++){
        if (copiaVetor[i] != (vetor[i]/2)){
            printf("ERRO");
            return 1;
        }
    }
    
    printf("Vetor funcionando!");
    pthread_exit(NULL);
    
    return 0;
}
