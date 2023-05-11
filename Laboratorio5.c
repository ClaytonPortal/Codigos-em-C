#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  5

// Variaveis globais
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond1;
pthread_cond_t x_cond2;

// Thread Oi Jose/Maria
void *oi (void *t) {
    int idThread = (int) t;

    //printf("Thread %d: Comecei\n", idThread);

    if (idThread == 1){
        printf("Thread %d: Oi Maria!\n", idThread);
  }

    if (idThread == 2){
        printf("Thread %d: Oi Jose!\n", idThread);
  }

    pthread_mutex_lock(&x_mutex);
    x++;
    if (x==2) {
        //printf("Thread %d: x = %d, vou enviar um signal \n", idThread, x);
        pthread_cond_signal(&x_cond1);
  }
    pthread_mutex_unlock(&x_mutex);

    pthread_exit(NULL);
}

// Thread SenteSe
void *senteSe (void *t) {
    int idThread = (int) t;
    //printf("%d: Comecei\n", idThread);

    pthread_mutex_lock(&x_mutex);
    if (x < 2) { 
        //printf("Thread 3 momentaneamente bloqueada, pois x = %d\n", x);
        pthread_cond_wait(&x_cond1, &x_mutex);
        //printf("Thread 3 libearda, x = %d\n", x);
  }

    printf("Thread 3: Sente-se, por favor.\n");
    x++;

    if (x == 3){
        //printf("Thread 3: x = 3, vou enviar um signal\n");
        pthread_cond_broadcast(&x_cond2);
    }

    pthread_mutex_unlock(&x_mutex); 
    pthread_exit(NULL);
}

// Thread até Mais
void *ateMais (void *t) {
    int idThread = (int) t;

    //printf("Thread %d: Comecei\n", idThread);

    pthread_mutex_lock(&x_mutex);
    if (x<3) {
        //printf("Thread %d momentaneamente bloqueada, pois x = %d \n", idThread, x);
    		pthread_cond_wait(&x_cond2, &x_mutex);
				//printf("Thread %d liberada!\n", idThread);
  }
    pthread_mutex_unlock(&x_mutex);

    if (idThread == 4){
        printf("Thread %d: Até mais, Maria!\n", idThread);
  }

    if (idThread == 5){
        printf("Thread %d: Até mais, José!\n", idThread);
  }
    pthread_exit(NULL);
}

// Funcao principal
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  // Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao
    pthread_mutex_init(&x_mutex, NULL);
    pthread_cond_init (&x_cond1, NULL);
    pthread_cond_init (&x_cond2, NULL);

  // Cria as threads
    pthread_create(&threads[0], NULL, oi, (void *) 1);
    pthread_create(&threads[1], NULL, oi, (void *) 2);
    pthread_create(&threads[2], NULL, senteSe, (void *) 3);
    pthread_create(&threads[3], NULL, ateMais, (void *) 4);
    pthread_create(&threads[4], NULL, ateMais, (void *) 5);

  // Espera todas as threads completarem
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
  }
    printf ("\nFIM\n");

  // Desaloca variaveis e termina
    pthread_mutex_destroy(&x_mutex);
    pthread_cond_destroy(&x_cond1);
    pthread_cond_destroy(&x_cond2);
}