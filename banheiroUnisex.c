#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*Tempo aleatorio entre 1 e 10 segunds em que uma pessoa demora no banheiro*/
#define TEMPO (rand() % 11)

typedef struct {
	int n;
	int compartimentos;
	int fila;	
}Banheiro;

Banheiro banheiro;
Banheiro fila;
sem_t compartimento;
int cont = 0;
int total = 0;

void *AcessoBanheiro (void *i){
	long int id = (long int)i;
	sem_wait(&compartimento);
	total++;

	if (total % banheiro.compartimentos == 0) {
        printf(" %d compartimento(s) ocupado(s). %d pessoas esperando.\n", banheiro.compartimentos, banheiro.fila -= banheiro.compartimentos);
        
    }
    //printf(" %d compartimento(s) ocupado(s)\n",banheiro.compartimentos);
	sleep(TEMPO);
	sem_post(&compartimento);
	
}
int main(){
	
	int qtd_pessoas;
	int banheiros,compartimentos,genero;

	printf("Quantas pessoas: ");
	scanf("%d",&qtd_pessoas);

	printf("Escolha quantos gêneros (entre 1 e 2): ");
	scanf("%d", &genero);
	while( genero != 1 && genero != 2){
		printf("Erro!\n");
		printf("Escolha quantos gêneros (entre 1 e 2): ");
		scanf("%d", &genero);
	}
	
	printf("Quantos banheiros: ");
	scanf("%d", &banheiros);
	
	printf("Quantos compartimetos: ");
	scanf("%d",&compartimentos);

	banheiro.n = banheiros;
	banheiro.compartimentos = compartimentos;
	banheiro.fila = qtd_pessoas;	

	
	if(genero == 1){
		/* pessoas de um genero soh */
		pthread_t pessoas[qtd_pessoas];
		sem_init(&compartimento, 0, compartimentos);

		for(long int i=0;i<qtd_pessoas;i++){
			pthread_create(&pessoas[i],NULL,AcessoBanheiro,(void *)i);
		}
		for(long int i=0;i<qtd_pessoas;i++){
			pthread_join(pessoas[i],NULL);
		}
		sem_destroy(&compartimento);

	}else{
		/* caso 2 generos diferentes sejao criados, dois tipo de threads serao criadas
			representando os dois generos diferentes
		*/
		pthread_t pessoa1[qtd_pessoas/2];
		pthread_t pessoa2[qtd_pessoas/2];
	}
	
	printf("banheiros = %d\n", banheiro.n);
	printf("compartimentos = %d\n", banheiro.compartimentos);
	
	return 0;
}