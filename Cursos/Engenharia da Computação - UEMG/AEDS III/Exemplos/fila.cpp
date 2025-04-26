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

class fila{
	private:
		int qtd;
		no *ini;
		no *fim;
	public:
		fila();
		~fila();
		void inserir(int x);
		void remover();
		void imprimir();
};

fila::fila(){
	qtd=0;
	ini=NULL;
	fim=NULL;
}
fila::~fila(){
	while(qtd>0){
		remover();
	}
}

void fila::inserir(int x){
	no *novo = new no();
	novo->valor=x;
	if(qtd==0){
		ini=novo;
		fim=novo;
	}
	else{
		fim->prox=novo;
		novo->ant = fim;
		fim = novo;
	}
	qtd++;
}

void fila::remover(){
	if(qtd>0){
		no *aux = ini;
		if(qtd==1){
			ini=NULL;
			fim=NULL;
		}
		else{
			ini = aux->prox;
			ini->ant = NULL;
		}
		qtd--;
		delete aux;
	}
	else{
		cout<<"FILA VAZIA\n";
	}
}

void fila::imprimir(){
	if(qtd>0){
		no *aux = ini;
		while(aux!=NULL){
			cout<<aux->valor<<" ";
			aux = aux->prox;
		}
		cout<<endl;
	}
	else{
		cout<<"FILA VAZIA\n";
	}
}

using namespace std;


int main(){
	
	fila x;
	x.inserir(7);
	x.inserir(8);
	x.inserir(9);
	x.inserir(6);
	x.remover();
	x.remover();
	x.imprimir();

}
