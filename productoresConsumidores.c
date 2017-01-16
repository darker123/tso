#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define TRUE 1
#define FALSE 0
#define N 5

typedef sem_t semaforo;
semaforo mutex;
semaforo vacias;
semaforo llenas;

void *productor ()
{
while(TRUE)
{
producir_elemento();
sem_wait(&vacias);
sem_wait(&mutex);
insertar_elemento();
sem_post(&mutex);
sem_post(&llenas);
}
}

void *consumidor ()
{
while(TRUE)
{
sem_wait(&llenas);
sem_wait(&mutex);
sacar_elemento();
sem_post(&mutex);
sem_post(&vacias);
consumir_elemto();
}
}

producir_elemento()
{
printf("Produciendo elemento\n");
sleep(1);
}
insertar_elemento()
{
printf("Elemento incertado\n");
sleep(1);
}
sacar_elemento()
{
printf("Elemento sacado\n");
sleep(1);
}
consumir_elemto(elemento)
{
printf("Elemento consumido\n");
sleep(1);
}

int numero_aleatorio(int limite_superior, int limite_inferior){
return (int)(((rand()%10)*0.1)*(limite_superior-limite_inferior+1)+limite_inferior);
}

int main (void)
{
sem_init(&mutex,1,1);
sem_init(&vacias,1,N);
sem_init(&llenas,1,0);
pthread_t productor_t, consumidor_t;
pthread_create(&productor_t,NULL,productor,NULL);
pthread_create(&consumidor_t,NULL,consumidor,NULL);
pthread_join(productor_t,NULL);
return(0);
}
