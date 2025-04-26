#include <iostream>
#include <cstdlib>
#include <string.h>
#include<stdio.h>

using namespace std;

class no{
	public:
		int valor;
		no *prox;
		no *ant;
		no();	
};

no::no(){
	valor=0;
	prox=NULL;
	ant=NULL;
}

class lista{
	private:
		int qtd;
		no *ini;
		no *fim;
	public:
		lista();
		~lista();
		void inserir(int x);
		void remover(int x);
		void imprimir();
};

lista::lista(){
	qtd=0;
	ini=NULL;
	fim=NULL;
}
lista::~lista(){
	while(qtd>0){
		remover(ini->valor);
	}
}

void lista::inserir(int x){
	no *novo = new no();
	novo->valor=x;
	if(qtd==0){
		ini=novo;
		fim=novo;
	}
	else{
		if(x<ini->valor){
			novo->prox = ini;
			ini->ant = novo;
			ini = novo;
		}
		else if (x>fim->valor){
			novo->ant = fim;
			fim->prox = novo;
			fim = novo;
		}
		else{
		
			no *aux = ini;
			no *aux2 = NULL;
			while(x>aux->valor){
				aux2=aux;
				aux= aux->prox;
			}
			aux2->prox = novo;
			aux->ant = novo;
			novo->ant = aux2;
			novo->prox = aux;
		}
		
	}
	qtd++;
}

void lista::remover(int x){
	if(qtd>0){
		no *aux = ini;
		no *aux2 = NULL;
		while(aux!=NULL){
			if(x == aux->valor){
				break;
			}
			else{
				aux2 = aux;
				aux = aux->prox;
			}
		}
		if(aux==NULL){
			cout<<"VALOR NAO ENCONTRADO\n";
		}
		else{
			
			if(qtd==1){
			ini=NULL;
			fim=NULL;
			}
			else{
				if(x==ini->valor){
					ini = ini->prox;
					ini->ant =NULL;
				}
				else if(x==fim->valor){
					fim = fim->ant;
					fim->prox = NULL;
				}
				else{
					aux2->prox = aux->prox;
					no *aux3 = aux->prox;
					aux3->ant = aux2;
				}
			}
		}	
		delete aux;
		qtd--;
	}
	else{
		cout<<"LISTA VAZIA\n";
	}
}

void lista::imprimir(){
	if(qtd>0){
		no *aux = ini;
		while(aux!=NULL){
			cout<<aux->valor<<" ";
			aux = aux->prox;
		}
		cout<<endl;
	}
	else{
		cout<<"LISTA VAZIA\n";
	}
}


int main(){
	
	lista x;

	x.inserir(7);
	x.inserir(15);
	x.inserir(8);
	x.inserir(9);
	x.inserir(6);
	x.inserir(5);
	x.imprimir();
	x.remover(8);
	x.imprimir();
	x.remover(15);
	x.imprimir();
	x.remover(5);
	x.imprimir();
	system("pause");

}
