#include <iostream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#define TAM_MAX 3;

using namespace std;

// FILAS DE PILHAS

class no_fila{
	public:
		no_fila *prox_pilha;
		no_fila *ant_pilha;
		no_fila();
};

no_fila::no_fila(){
	prox_pilha=NULL;
	ant_pilha=NULL;
}

class fila_de_pilhas{
	private:
		int qtd_pilhas;
		no_fila *ini_fila;
		no_fila *fim_fila;
	public:
        fila_de_pilhas();
		~fila_de_pilhas();
		void inserir(int x);
		void remover();
		void imprimir();
};

fila_de_pilhas::fila_de_pilhas() {
	qtd_pilhas=0;
	ini_fila=NULL;
	fim_fila=NULL;
}
fila_de_pilhas::~fila_de_pilhas() {
	while(qtd_pilhas>0){
		remover();
	}
}

// PILHAS

class no_pilha{
	public:
		int valor;
		no_pilha *prox;
		no_pilha *ant;
		no_pilha();	
};

no_pilha::no_pilha(){
	valor=0;
	prox=NULL;
	ant=NULL;
}

class pilha{
	private:
		int qtd;
		no_pilha *ini;
		no_pilha *fim;
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

void fila_de_pilhas::inserir(int x) {
	cout<<"Inserindo ";
	cout<<x;
	cout<<"...\n";

    
}

void fila_de_pilhas::remover() {
	
}

void fila_de_pilhas::imprimir() {
	if (qtd_pilhas==0) {
        cout<<"Fila de pilhas vazia...\n";
    }
}

using namespace std;


int main() {
	fila_de_pilhas x; // Iniciando a fila de pilhas vazia

	cout<<"Tamanho máximo das pilhas: ";
    cout<<TAM_MAX;
    cout<<"\n";
    
    x.imprimir();
    x.inserir(1); // Fila está vazia, preciso iniciar a fila e a primeira pilha
}
