#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct element
{
	int num;
	struct element *next;
}Element;

typedef struct list
{
	Element *start;
}List;

List* create_list()
{
	List *l;
	l = (List*)malloc(sizeof(List));
	l->start = NULL;
	return l;
}

void insert(List *l, int num)
{
	Element *aux, *aux2;
	aux = (Element*)malloc(sizeof(Element));
	aux2 = (Element*)malloc(sizeof(Element));
	aux = l->start;
	while(aux->next != NULL)
	{
		aux = aux->next;
	}
	aux2->num = num;
	aux2->next = NULL;
	aux->next = aux2;
	printf("a%d\n\n", aux->num);
}

void print(List *l, Element *aux)
{
	aux = l->start;
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("a%d ", aux->num);
		aux = aux->next;
	}
}

int main()
{
	List* l;
	Element* aux;
	l = create_list();
	
	int i;
	srand(time(NULL));
	for(i = 0; i < 100; i++)
	{
		int index = rand() % 100;
		insert(l, index);
	}
	
	print(l, aux);
	
	return 0;
}
