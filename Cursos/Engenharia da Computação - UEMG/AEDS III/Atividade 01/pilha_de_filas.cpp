#include <iostream>
#include <cstdlib> // For NULL

using namespace std;

const int TAM_MAX_FILA = 3;

// --- Estrutura e Classe para os Elementos da Fila ---
class no_elemento_fila {
public:
    int valor;
    no_elemento_fila *prox;
    no_elemento_fila *ant;

    no_elemento_fila() {
        valor = 0;
        prox = NULL;
        ant = NULL;
    }
};

class fila {
private:
    int qtd_elementos;
    no_elemento_fila *ini;
    no_elemento_fila *fim;

public:
    fila() {
        qtd_elementos = 0;
        ini = NULL;
        fim = NULL;
    }

    ~fila() {
        // cout << "Destruindo fila interna..." << endl;
        while (!esta_vazia()) {
            remover_elemento();
        }
        // cout << "Fila interna destruida." << endl;
    }

    void inserir_elemento(int x) {
        if (esta_cheia()) {
            // Esta verificação deve ser feita antes de chamar, ou tratada pelo chamador
            // cout << "ERRO INTERNO: Tentativa de inserir em fila cheia!" << endl;
            return;
        }
        no_elemento_fila *novo = new no_elemento_fila();
        novo->valor = x;
        if (esta_vazia()) {
            ini = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        }
        qtd_elementos++;
    }

    int remover_elemento() {
        if (esta_vazia()) {
            // Esta verificação deve ser feita antes de chamar
            // cout << "ERRO INTERNO: Tentativa de remover de fila vazia!" << endl;
            return -1; 
        }
        no_elemento_fila *aux = ini;
        int valor_removido = aux->valor;
        if (qtd_elementos == 1) {
            ini = NULL;
            fim = NULL;
        } else {
            ini = aux->prox;
            ini->ant = NULL;
        }
        delete aux;
        qtd_elementos--;
        return valor_removido;
    }

    void imprimir_elementos() {
        if (esta_vazia()) {
            cout << "Fila vazia";
            return;
        }
        no_elemento_fila *aux = ini;
        cout << "[";
        while (aux != NULL) {
            cout << aux->valor;
            if (aux->prox != NULL) {
                cout << ", ";
            }
            aux = aux->prox;
        }
        cout << "]";
    }

    bool esta_vazia() {
        return qtd_elementos == 0;
    }

    bool esta_cheia() {
        return qtd_elementos >= TAM_MAX_FILA;
    }

    int get_qtd_elementos() {
        return qtd_elementos;
    }
};

// --- Estrutura e Classe para a Pilha de Filas ---
class no_pilha {
public:
    fila dados_fila; 
    no_pilha *prox; // Ponteiro para a fila ABAIXO na pilha
    no_pilha *ant;  // Ponteiro para a fila ACIMA na pilha

    no_pilha() {
        prox = NULL;
        ant = NULL;
    }
};

class pilha_de_filas {
private:
    int qtd_filas_na_pilha;
    no_pilha *topo; 

public:
    pilha_de_filas() {
        qtd_filas_na_pilha = 0;
        topo = NULL;
    }

    ~pilha_de_filas() {
        cout << "Destruindo pilha_de_filas..." << endl;
        no_pilha *atual = topo;
        while (atual != NULL) {
            no_pilha *proximo_abaixo = atual->prox; 
            // O destrutor de 'fila' (membro de no_pilha) será chamado automaticamente
            // e limpará os elementos da fila.
            cout << "Deletando uma fila da pilha (e seus elementos)..." << endl;
            delete atual; 
            atual = proximo_abaixo;
        }
        topo = NULL;
        qtd_filas_na_pilha = 0;
        cout << "Pilha de filas destruida." << endl;
    }

    void push_elemento_na_pilha(int x) {
        if (topo == NULL || topo->dados_fila.esta_cheia()) {
            no_pilha *nova_fila_no_topo = new no_pilha();
            cout << "Criando nova fila no topo da pilha." << endl;
            
            nova_fila_no_topo->prox = topo; 
            if (topo != NULL) {
                topo->ant = nova_fila_no_topo; 
            }
            topo = nova_fila_no_topo; 
            topo->ant = NULL; // Novo topo não tem ninguém acima
            qtd_filas_na_pilha++;
        }
        cout << "Inserindo elemento " << x << " na fila do topo." << endl;
        topo->dados_fila.inserir_elemento(x);
    }

    void pop_elemento_da_pilha() {
        if (esta_vazia() || topo == NULL ) {
            cout << "ERRO: Pilha de filas esta vazia! Nao ha elementos para remover." << endl;
            return;
        }
        if (topo->dados_fila.esta_vazia()){
            // Isso não deveria acontecer se a lógica de push/pop estiver correta
            // e uma fila vazia for removida da pilha.
            // Mas como uma proteção:
            cout << "ERRO: Fila do topo esta vazia, mas a pilha nao. Removendo fila vazia do topo..." << endl;
            no_pilha *aux = topo;
            topo = topo->prox; 
            if (topo != NULL) {
                topo->ant = NULL; 
            }
            delete aux;
            qtd_filas_na_pilha--;
            if (esta_vazia() || topo == NULL) {
                 cout << "Pilha de filas agora esta vazia." << endl;
            } else {
                // Tenta remover da nova fila do topo (recursivo ou iterativo)
                // Para simplificar, vamos apenas reportar e o usuário pode chamar pop de novo.
                 cout << "Uma fila vazia foi removida. Tente pop novamente se desejar." << endl;
            }
            return;
        }

        int valor_removido = topo->dados_fila.remover_elemento();
        cout << "Elemento " << valor_removido << " removido da fila do topo." << endl;

        if (topo->dados_fila.esta_vazia()) {
            cout << "Fila do topo ficou vazia. Removendo-a da pilha..." << endl;
            no_pilha *aux = topo;
            topo = topo->prox; 
            if (topo != NULL) {
                topo->ant = NULL; 
            }
            delete aux;
            qtd_filas_na_pilha--;
            if (esta_vazia() || topo == NULL) {
                 cout << "Pilha de filas agora esta vazia." << endl;
            }
        }
    }

    void imprimir_pilha_de_filas() {
        if (esta_vazia() || topo == NULL) {
            cout << "--- Pilha de Filas VAZIA ---" << endl;
            return;
        }
        cout << "--- Conteudo da Pilha de Filas (Topo para Base) ---" << endl;
        no_pilha *aux = topo;
        int i = qtd_filas_na_pilha - 1; // Ou contar do topo para baixo
        int j = 0;
        while (aux != NULL) {
            cout << "Pilha No." << j++ << " (Fila no Topo): ";
            aux->dados_fila.imprimir_elementos();
            cout << " (Qtd: " << aux->dados_fila.get_qtd_elementos() << "/" << TAM_MAX_FILA << ")" << endl;
            aux = aux->prox; 
        }
        cout << "Total de filas na pilha: " << qtd_filas_na_pilha << endl;
        cout << "--- Fim da Pilha de Filas ---" << endl;
    }

    bool esta_vazia() {
        return qtd_filas_na_pilha == 0 || topo == NULL;
    }
};

int main() {
    pilha_de_filas pdf;

    pdf.imprimir_pilha_de_filas(); 

    pdf.push_elemento_na_pilha(10); // Fila 0 criada, [10]
    pdf.imprimir_pilha_de_filas();
    pdf.push_elemento_na_pilha(20); // Fila 0, [10, 20]
    pdf.imprimir_pilha_de_filas();
    pdf.push_elemento_na_pilha(30); // Fila 0, [10, 20, 30] (cheia)
    pdf.imprimir_pilha_de_filas();

    pdf.push_elemento_na_pilha(40); // Fila 1 criada, [40] | Fila 0 [10,20,30]
    pdf.imprimir_pilha_de_filas();
    pdf.push_elemento_na_pilha(50); // Fila 1, [40, 50] | Fila 0 [10,20,30]
    pdf.imprimir_pilha_de_filas();

    pdf.pop_elemento_da_pilha(); // Remove 40 da Fila 1. Fila 1: [50]
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 50 da Fila 1. Fila 1 vazia e removida. Topo é Fila 0.
    pdf.imprimir_pilha_de_filas();

    pdf.push_elemento_na_pilha(60); // Fila 0 ainda está cheia [10,20,30]. Nova Fila 1 criada [60].
    pdf.imprimir_pilha_de_filas();
    pdf.push_elemento_na_pilha(70); // Fila 1 [60,70]
    pdf.push_elemento_na_pilha(80); // Fila 1 [60,70,80] (cheia)
    pdf.imprimir_pilha_de_filas();
    pdf.push_elemento_na_pilha(90); // Nova Fila 2 criada [90]
    pdf.imprimir_pilha_de_filas();


    pdf.pop_elemento_da_pilha(); // Remove 90 (Fila 2). Fila 2 vazia e removida. Topo é Fila 1.
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 60 (Fila 1). Fila 1: [70,80]
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 70 (Fila 1). Fila 1: [80]
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 80 (Fila 1). Fila 1 vazia e removida. Topo é Fila 0.
    pdf.imprimir_pilha_de_filas();

    pdf.pop_elemento_da_pilha(); // Remove 10 (Fila 0). Fila 0: [20,30]
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 20 (Fila 0). Fila 0: [30]
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha(); // Remove 30 (Fila 0). Fila 0 vazia e removida. Pilha vazia.
    pdf.imprimir_pilha_de_filas(); 

    pdf.pop_elemento_da_pilha(); // Tenta remover de pilha vazia
    pdf.push_elemento_na_pilha(100); // Recomeça
    pdf.imprimir_pilha_de_filas();
    pdf.pop_elemento_da_pilha();
    pdf.imprimir_pilha_de_filas();


    return 0;
}

