#include <stdio.h>
#include <pthread.h>
#define TAM 6

long vetor[TAM];
long copiaVetor[TAM];

void *multiVetor(void *id) {
    long threadID = *(long *) id;
    
    if (threadID == 0){
        for (long i = 0; i < TAM; i+=2){
            long temp = 2*vetor[i];
            vetor[i] = temp;
        }
    }
    if (threadID == 1){
        for (long i = 1; i < TAM; i+=2){
            long temp = 2*vetor[i];
            vetor[i] = temp;
        }
    }
    pthread_exit(NULL);
}

int main(void) {
    for (long i = 0; i < TAM; i++){
        vetor[i] = i+1;
    }
    for (long i = 0; i < TAM; i++){
        copiaVetor[i] = vetor[i];
    }
    
    pthread_t t1;
    pthread_t t2;
    
    pthread_create(&t1, NULL, multiVetor, (void *) 0);
    pthread_create(&t2, NULL, multiVetor, (void *) 1);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    for (long i = 0; i < TAM; i++){
        if (copiaVetor[i] != vetor[i]/2){
            printf("ERRO!");
            break;
        }
        else{
            printf("[%d]", vetor[i]);
        }
    }
    printf("%d", vetor[0]);
    return 0;
}