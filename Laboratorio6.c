#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

// tamanho do buffer
#define B 16

// número de threads
#define P 4
#define C 4

int BUFFER[B];
int cont = 0;

sem_t bufferCheio, bufferVazio;
sem_t mutexProd, mutexCons;

// inicializa o buffer
void iniciaBUFFER(int n) {
  int i;
  for (i = 0; i < n; i++)
    BUFFER[i] = 0;
}

// imprime o buffer
void imprimeBUFFER(int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d ", BUFFER[i]);
  printf("\n");
}

void insere(int item, int id) {
  static int in = 0;

  sem_wait(&bufferVazio);
  sem_wait(&mutexProd);
  printf("P[%d] pegou o wait do BUFFER e de produtor.\n", id);

  BUFFER[in] = item;
  in = (in + 1) % B;
  cont++;
  printf("P[%d] inseriu o item %d no BUFFER e modificou in.\n", id, item);

  imprimeBUFFER(B);
  printf("P[%d] imprimiu o BUFFER.\n\n", id);

  sem_post(&mutexProd);
  if (cont == B) {
    int i;
    printf("P[%d] Deu post bufferCheio para os consumidores.\n\n", id);
    for (i = 0; i < B; i++) {
      sem_post(&bufferCheio);
    }
  }
}

int retira(int id) {
  static int out = 0;
  int item;

  sem_wait(&bufferCheio);
  sem_wait(&mutexCons);
  printf("C[%d] pegou o wait do BUFFER e de consumidor.\n", id);

  item = BUFFER[out];
  BUFFER[out] = 0;
  out = (out + 1) % B;
  cont--;
  printf("C[%d] removeu o item %d do BUFFER e modificou out.\n", id, item);

  imprimeBUFFER(B);
  printf("C[%d] imprimiu o BUFFER.\n\n", id);

  sem_post(&mutexCons);
  if (cont == 0) {
    int i;
    printf("C[%d] Deu post em bufferVazio para os produtores.\n\n", id);
    for (i = 0; i < B; i++) {
      sem_post(&bufferVazio);
    }
  }
  return item;
}

void *produtor(void *arg) {
  int *id = (int *)arg;
  // printf("Sou a thread produtora %d\n", *id);
  while (1) {
    // produzindo o item
    insere(*id, *id);
    sleep(1);
  }
  pthread_exit(NULL);
}

void *consumidor(void *arg) {
  int *id = (int *)arg;
  int item;
  // printf("Sou a thread consumidora %d\n", *id);
  while (1) {
    item = retira(*id);
    sleep(1);
  }
  pthread_exit(NULL);
}

int main(void) {
  int i;
  pthread_t threads[P + C];
  int ids[P + C];

  printf("Iniciando os semáforos\n\n");
  sem_init(&mutexCons, 0, 1);
  sem_init(&mutexProd, 0, 1);
  sem_init(&bufferCheio, 0, 0);
  sem_init(&bufferVazio, 0, B);

  for (i = 0; i < P; i++) {
    ids[i] = i + 1;
    printf("Criando a thread produtora [%d]\n\n", i + 1);
    pthread_create(&threads[i], NULL, produtor, (void *)&ids[i]);
  }

  for (i = 0; i < C; i++) {
    ids[i + P] = i + 1;
    printf("Criando a thread consumidora [%d]\n\n", i + 1);
    pthread_create(&threads[i + P], NULL, consumidor, (void *)&ids[i + P]);
  }

  pthread_exit(NULL);
  return 0;
}
