#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*Tempo aleatorio entre 1 e 10 segunds em que uma pessoa demora no banheiro*/
#define TEMPO (rand() % 11)


/* Estrutura criada para gerenciar as características do banheiro */
typedef struct {
	int n;
	int compartimentos;
	int fila;	
}Banheiro;
Banheiro banheiro;
Banheiro fila;
sem_t compartimento;

/* Cada thread representa uma pessoa, essa pessoa pode ser de 2 generos diferentes */
struct args{
	int genero;
};

pthread_mutex_t sexo;

int cont = 0;
int total = 0;

int contador = 0;


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

void *Acesso2(void *input){
	//long int idd = (long int)i;

	sem_wait(&compartimento);

	if (  ((struct args*)input)->genero ==1 ){
		printf(" compartimento ocupado pelo genero 1. %d pessoas esperando.\n",--(banheiro.fila));
		
		sleep(TEMPO);
		printf(" compartimento livre\n");
		sem_post(&compartimento); 
		
	}else{
		printf(" compartimento ocupado pelo genero 2. %d pessoas esperando.\n",(banheiro.fila)--);
		sleep(TEMPO);
		printf(" compartimento livre\n");
		sem_post(&compartimento); 
		
	}
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
		struct args Pessoa1[qtd_pessoas/2];
		struct args Pessoa2[qtd_pessoas/2];

		sem_init(&compartimento, 0, compartimentos);
	
		
		for(int i = 0;i<qtd_pessoas/2;i++){
			Pessoa1[i].genero = 1; 
		}
		for(int i = 0;i<qtd_pessoas/2;i++){
			Pessoa2[i].genero = 2; 
		}

		pthread_t genero1[qtd_pessoas/2];
		pthread_t genero2[qtd_pessoas/2];


		for(long int i=0;i<qtd_pessoas/2;i++){
			pthread_create(&genero1[i],NULL,Acesso2,(void *)Pessoa1);
		}
		for(long int i=0;i<qtd_pessoas/2;i++){
			pthread_create(&genero1[i],NULL,Acesso2,(void *)Pessoa2);
		}


		for(long int i=0;i<qtd_pessoas/2;i++){
			pthread_join(genero1[i],NULL);
		}
		for(long int i=0;i<qtd_pessoas/2;i++){
			pthread_join(genero2[i],NULL);
		}
		sem_destroy(&compartimento);
	}
	
	/*
		printf("banheiros = %d\n", banheiro.n);
		printf("compartimentos = %d\n", banheiro.compartimentos);
		printf("contador = %d\n",contador );
	*/
	return 0;
}