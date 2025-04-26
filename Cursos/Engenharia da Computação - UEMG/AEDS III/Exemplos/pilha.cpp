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

class pilha{
	private:
		int qtd;
		no *ini;
		no *fim;
	public:
		pilha();
		~pilha();
		void inserir(int x);
		void remover();
		void imprimir();
};

pilha::pilha(){
	qtd=0;
	ini=NULL;
	fim=NULL;
}
pilha::~pilha(){
	while(qtd>0){
		remover();
	}
}

void pilha::inserir(int x){
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

void pilha::remover(){
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

void pilha::imprimir(){
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



int main(){
	
	pilha x;
	x.inserir(7);
	x.inserir(8);
	x.inserir(9);
	x.inserir(6);
	x.remover();
	x.imprimir();

}
