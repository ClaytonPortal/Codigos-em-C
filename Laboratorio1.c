#include <stdio.h>
#include <pthread.h>

#define TAM 10000

// declarando vetores
long vetor[TAM];
long copiaVetor[TAM];

// funcao das threads
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
    
    // inicializando os vetores (original e copia)
    for (long i = 0; i < TAM; i++){
        vetor[i] = i+1;
        copiaVetor[i] = vetor[i];
    }
    
    // declarando threads e ids
    pthread_t T[2];
    long idthreads[2];
    
    // criando as threads
    for(long i = 0; i < 2; i++){
        idthreads[i] = i;
        pthread_create(&T[i], NULL, multiVetor, (void *) &idthreads[i]);
    }

    // join das threads
    for(long i = 0; i < 2; i++){
        pthread_join(T[i], NULL);
    }
    
    // testando se o vetor foi corretamente multiplicado
    for (long i = 0; i < TAM; i++){
        if (copiaVetor[i] != (vetor[i]/2)){
            printf("ERRO!"); // mensagem de erro
            return 1;
        }
    }
    
    printf("Vetor funcionando!"); // mensagem funcionando
    pthread_exit(NULL);
    
    return 0;
}
