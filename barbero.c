#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define FALSE 0
#define SILLAS 3
#define CANTIDAD_CLIENTES 5 
#define TIEMPO_LLEGADA_DE_CLIENTES 1
#define TIEMPO_DE_CORTE 3 
typedef sem_t semaforo;

semaforo clientes, barberos, mutex;
int espera = 0;

cortar_pelo()
{
printf ("Barbero:Comienzo el corte de pelo de un cliente quedan %d esperando.\n",espera);
sleep (TIEMPO_DE_CORTE);
printf ("Barbero:Termine de cortar el pelo de un cliente quedan %d esperando.\n",espera);
}
recibir_corte()
{
printf("Cliente:Me estan cortando el pelo.\n");
}

void *barbero ()
{
printf ("Barbero:Despierto\nBarbero:Empiezo a trabajar\n"); 
while(TRUE)
{
sem_wait(&clientes);
sem_wait(&mutex);
espera=espera-1;
sem_post(&barberos);
sem_post(&mutex);
cortar_pelo(); 
}
}

void *cliente ()
{
printf ("Cliente:entrando hay %d esperando\n",espera);
sem_wait(&mutex);
if(espera<SILLAS)
{
espera=espera+1;
sem_post(&clientes);
sem_post(&mutex);
sem_wait(&barberos);
recibir_corte();
}else
{
sem_post(&mutex);
printf ("Cliente:Me fui no hay lugar.\n");
}
}

int main (void)
{
sem_init(&mutex,1,1);
sem_init(&clientes,1,0);
sem_init(&barberos,1,0);

pthread_t barbero_t,clientes_t[CANTIDAD_CLIENTES];
pthread_create(&barbero_t,NULL,barbero,NULL);

int i;
for (i=0;i<CANTIDAD_CLIENTES;i++)
{
sleep(TIEMPO_LLEGADA_DE_CLIENTES);
pthread_create(&clientes_t[i],NULL,cliente,NULL);
}
pthread_join(barbero_t,NULL);
return(0);
}
