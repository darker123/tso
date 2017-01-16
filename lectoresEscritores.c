#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define TRUE 1
#define FALSE 0
#define CANTIDAD_ESCRITORES 2
#define CANTIDAD_LECTORES 3
#define TIEMPO_DE_LLEGADA_LECTOR 1
#define TIEMPO_DE_LLEGADA_ESCRITOR 2

typedef sem_t semaforo;
semaforo db, mutex;
int rc=0;

void *lector (){
while(TRUE){
sem_wait(&mutex);
rc=rc+1;
if(rc==1)sem_wait(&db);
sem_post(&mutex);
leer_base_datos();
sem_wait(&mutex);
rc=rc-1;
if(rc==0)sem_post(&db);
sem_post(&mutex);
usar_datos_leidos();
}
}
void *escritor (){
while(TRUE){
inventar_datos();
sem_wait(&db);
escribir_base_datos();
sem_post(&db);
}
}
int numero_aleatorio(int limite_superior, int limite_inferior){
return (int)(((rand()%10)*0.1)*(limite_superior-limite_inferior+1)+limite_inferior);
}

leer_base_datos(){
printf("Lector: Comenzando a leer base de datos...\n");
sleep(numero_aleatorio(3,1));
printf("Lector: Terminando de leer base de datos...\n");
}
usar_datos_leidos(){
printf("Lector: Usando datos leidos...\n");
sleep(numero_aleatorio(2,1));
}
inventar_datos(){
printf("Escritor: Inventando Datos...\n");
sleep(1);
}
escribir_base_datos(){
printf("Escritor: Comenzando a escribir Base de Datos...\n");
sleep(numero_aleatorio(4,1));
printf("Escritor: Terminando de escribir Base de Datos...\n");
}
int main (void){
sem_init(&mutex,1,1);
sem_init(&db,1,1);
pthread_t escritores_t[CANTIDAD_ESCRITORES],lectores_t[CANTIDAD_LECTORES];
int j;
for (j=0;j<CANTIDAD_LECTORES;j++){
sleep(TIEMPO_DE_LLEGADA_LECTOR);
pthread_create(&lectores_t[j],NULL,lector,NULL);
}
int i;
for (i=0;i<CANTIDAD_ESCRITORES;i++){
sleep(TIEMPO_DE_LLEGADA_ESCRITOR);
pthread_create(&escritores_t[i],NULL,escritor,NULL);
pthread_join(escritores_t[i],NULL);
}
return(0);
}
