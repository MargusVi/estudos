#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define TAM_BARALHO 40

typedef struct carta
{
	char num;
	int naipe; //1- copas, 2- ouros, 3- espadas, 4- paus
	int valor;
}Carta;

typedef struct baralho
{
	int topo;
	Carta baralho[40];
}Baralho;


Baralho* criaBaralho() //Aloca a memória para o baralho
{
	Baralho *b;
	b = (Baralho*)malloc(sizeof(Baralho));
	b->topo = 0;
	return b;
}

void pegarBaralho(Baralho* b) //Insere todas as 40 cartas usadas no jogo no baralho
{
	int i;
	char num = '1';
	for(i = 0; i < 40; i++)
	{
		if(i < 7 || i >= 10 && i < 17 || i >= 20 && i < 27 || i >= 30 && i < 37)
		{
			b->baralho[i].num = num;
			num++;
			if(num == '8')
			{
				num = '1';
			}
		}
		else if(i == 7 || i == 17 || i == 27 || i == 37)
		{
			b->baralho[i].num = 'J';
		}
		else if(i == 8 || i == 18 || i == 28 || i == 38)
		{
			b->baralho[i].num = 'Q';
		}
		else if(i == 9 || i == 19 || i == 29 || i == 39)
		{
			b->baralho[i].num = 'K';
		}
		
		if(i <= 9)
		{
			b->baralho[i].naipe = 1;
		}
		else if(i <= 19)
		{
			b->baralho[i].naipe = 2;
		}
		else if(i <= 29)
		{
			b->baralho[i].naipe = 3;
		}
		else if(i <= 39)
		{
			b->baralho[i].naipe = 4;
		}
		
		b->topo = b->topo + 1;
	}
	
	int array[40] = {27, 31, 35, 3, 6, 10, 39, 16, 20, 24, 26, 29, 33, 1, 4, 8, 37, 14, 18, 22, 38, 30, 34, 2, 5, 9, 12, 15, 19, 23, 28, 32, 36, 40, 7, 11, 13, 17, 21, 25};
	int i2;
	for(i2 = 0; i2 < 40; i2++)
	{
		b->baralho[i2].valor = array[i2];
	}
}

void embaralhar(Baralho* b) //Embaralha o baralho
{
	srand(time(NULL));
	int i;
	for (i = 0; i < TAM_BARALHO; i++)
	{
		char swap_index = rand() % TAM_BARALHO;
    
    	char temp = b->baralho[i].num;
    	b->baralho[i].num = b->baralho[swap_index].num;
    	b->baralho[swap_index].num = temp;
    
    	char temp2 = b->baralho[i].naipe;
    	b->baralho[i].naipe = b->baralho[swap_index].naipe;
    	b->baralho[swap_index].naipe = temp2;
    
    	char temp3 = b->baralho[i].valor;
    	b->baralho[i].valor = b->baralho[swap_index].valor;
    	b->baralho[swap_index].valor = temp3;
	}
}

int main(void)
{
	Baralho *b;
		
	b = criaBaralho();
	
	pegarBaralho(b);
	
	int i;
	for(i = 0; i < 40; i++)
	{
		printf("%c%d - valor: %d\n", b->baralho[i].num, b->baralho[i].naipe, b->baralho[i].valor);
	}
	
	embaralhar(b);
	printf("\n\n\n");
	
	for(i = 0; i < 40; i++)
	{
		printf("%c%d - valor: %d\n", b->baralho[i].num, b->baralho[i].naipe, b->baralho[i].valor);
	}
}

