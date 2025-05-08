#include <iostream>

#define CAPACIDADE_MAX 3

using namespace std;

class no_elemento_pilha {
public:
    int valor;
    no_elemento_pilha* prox;

    no_elemento_pilha(int v) {
        valor = v;
        prox = NULL;
    }
};

class pilha {
private:
    no_elemento_pilha* topo;
    int qtd;

public:
    pilha() {
        topo = NULL;
        qtd = 0;
    }

    ~pilha() {
        int val_removido;
        while (!esta_vazia()) {
            remover(val_removido);
        }
    }

    bool inserir(int x) { // Push
        if (esta_cheia()) {
            // cout << "Erro: Pilha cheia! Nao foi possivel inserir " << x << endl;
            return false;
        }
        no_elemento_pilha* novo = new no_elemento_pilha(x);
        novo->prox = topo;
        topo = novo;
        qtd++;
        return true;
    }

    bool remover(int& valor_removido) { // Pop
        if (esta_vazia()) {
            // cout << "Erro: Pilha vazia! Nao foi possivel remover." << endl;
            return false;
        }
        no_elemento_pilha* aux = topo;
        valor_removido = aux->valor;
        topo = topo->prox;
        delete aux;
        qtd--;
        return true;
    }

    bool esta_cheia() const {
        return qtd >= CAPACIDADE_MAX;
    }

    bool esta_vazia() const {
        return qtd == 0;
    }

    void imprimir() const {
        if (esta_vazia()) {
            cout << "[Pilha Vazia]";
            return;
        }
        cout << "[Topo] ";
        no_elemento_pilha* aux = topo;
        while (aux != NULL) {
            cout << aux->valor << " ";
            aux = aux->prox;
        }
        cout << "[Base]";
    }
};

class no_fila_de_pilhas {
public:
    pilha p_interna; // Each node in the queue contains a stack object
    no_fila_de_pilhas* prox;

    no_fila_de_pilhas() {
        prox = NULL;
    }
};

// Queue of stacks class
class fila_de_pilhas {
private:
    no_fila_de_pilhas* ini;
    no_fila_de_pilhas* fim;

public:
    fila_de_pilhas() {
        ini = NULL;
        fim = NULL;
    }

    ~fila_de_pilhas() {
        while (ini != NULL) {
            no_fila_de_pilhas* temp = ini;
            ini = ini->prox;
            delete temp; // p_interna's destructor is called automatically
        }
        fim = NULL;
    }

    void enfileirar_elemento(int x) {
        if (fim == NULL || fim->p_interna.esta_cheia()) {
            no_fila_de_pilhas* novo_no_de_fila = new no_fila_de_pilhas();
            novo_no_de_fila->p_interna.inserir(x); // Element is inserted into the new stack

            if (fim == NULL) { // Queue was empty
                ini = fim = novo_no_de_fila;
            } else { // Queue not empty, append new stack node
                fim->prox = novo_no_de_fila;
                fim = novo_no_de_fila;
            }
        } else {
            // Last stack in queue is not full, insert element there
            fim->p_interna.inserir(x);
        }
    }

    bool desenfileirar_elemento(int& valor_removido) {
        if (ini == NULL) {
            // cout << "Fila de pilhas esta vazia. Nada para remover." << endl;
            return false;
        }

        // Try to remove from the front stack
        bool sucesso_remocao = ini->p_interna.remover(valor_removido);

        if (sucesso_remocao) {
            // Element was successfully removed from the front stack
            if (ini->p_interna.esta_vazia()) {
                // The front stack is now empty, so dequeue this stack node
                no_fila_de_pilhas* temp = ini;
                ini = ini->prox;
                delete temp;
                if (ini == NULL) { // Queue became empty after removing the stack node
                    fim = NULL;
                }
            }
            return true;
        } else {
            // This case (front stack was empty when `remover` was called) should ideally not be reached
            // if enqueuing logic is correct and empty stacks are immediately dequeued after last element removal.
            // However, as a safeguard, if we find an empty stack at the front:
            // cout << "Info: Removendo uma pilha vazia da frente da fila." << endl;
            no_fila_de_pilhas* temp = ini;
            ini = ini->prox;
            delete temp;
            if (ini == NULL) { // Queue became empty
                fim = NULL;
                // cout << "Fila de pilhas esvaziou apos remover pilha vazia." << endl;
                return false; // No element was actually retrieved for the user
            }
            // Try to dequeue from the new front stack
            return desenfileirar_elemento(valor_removido);
        }
    }

    void imprimir_fila_completa() const {
        if (ini == NULL) {
            cout << "Fila de pilhas esta vazia." << endl;
            return;
        }
        cout << "Conteudo da Fila de Pilhas (Frente para Tras):" << endl;
        no_fila_de_pilhas* atual = ini;
        int contador_pilha = 1;
        while (atual != NULL) {
            cout << "  Pilha " << contador_pilha++ << ": ";
            atual->p_interna.imprimir();
            cout << endl;
            atual = atual->prox;
        }
    }
};

int main() {
    fila_de_pilhas fdp;

    cout << "Estado Inicial:" << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Enfileirando 1, 2, 3 (Pilha 1 deve encher)" << endl;
    fdp.enfileirar_elemento(1);
    fdp.enfileirar_elemento(2);
    fdp.enfileirar_elemento(3); 
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Enfileirando 4 (Deve criar Pilha 2)" << endl;
    fdp.enfileirar_elemento(4);
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Enfileirando 5, 6 (Pilha 2 deve encher)" << endl;
    fdp.enfileirar_elemento(5);
    fdp.enfileirar_elemento(6); 
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Enfileirando 7 (Deve criar Pilha 3)" << endl;
    fdp.enfileirar_elemento(7);
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    int valor;
    cout << "Desenfileirando elementos:" << endl;
    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 3
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "--" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 2
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "--" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 1 (Pilha 1 esvazia e é removida)
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 6
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "--" << endl;

    cout << "Enfileirando 8 (Deve ir para Pilha 2, que tem espaco [4,5])" << endl;
    fdp.enfileirar_elemento(8); 
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 8
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "--" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 5
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "--" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 4 (Pilha 2 esvazia e é removida)
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    if (fdp.desenfileirar_elemento(valor)) cout << "Desenfileirado: " << valor << endl; // Esperado: 7 (Pilha 3 esvazia e é removida)
    else cout << "Falha ao desenfileirar." << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Tentando desenfileirar de fila vazia:" << endl;
    if (!fdp.desenfileirar_elemento(valor)) cout << "Falha ao desenfileirar (esperado, fila vazia)." << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;
    
    cout << "Enfileirando 10, 11, 12, 13 apos esvaziar completamente" << endl;
    fdp.enfileirar_elemento(10);
    fdp.enfileirar_elemento(11);
    fdp.enfileirar_elemento(12); // Pilha 1 (nova) cheia
    fdp.enfileirar_elemento(13); // Pilha 2 (nova) com um elemento
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;

    cout << "Desenfileirando tudo para testar destrutor implicitamente ao sair do main." << endl;
    int count = 0;
    while(fdp.desenfileirar_elemento(valor)) {
        cout << "Desenfileirado: " << valor << endl;
        count++;
    }
    cout << "Total de elementos desenfileirados no loop final: " << count << endl;
    cout << "Fila final (deve estar vazia):" << endl;
    fdp.imprimir_fila_completa();
    cout << "------------------------------------" << endl;
    cout << "Programa encerrando. Destrutores serao chamados." << endl;

    return 0;
}
