#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::max
#include <iomanip>   // Para std::setw
#include <limits>    // Para std::numeric_limits
#include <cstdlib>   // Para system("cls") ou system("clear")

using namespace std;

// Estrutura do nó da árvore
class no_arvore {
public:
    int valor;
    no_arvore* esquerda;
    no_arvore* direita;

    no_arvore(int v) {
        valor = v;
        esquerda = NULL;
        direita = NULL;
    }
};

class arvore_binaria {
private:
    no_arvore* raiz;

    // Função auxiliar recursiva para inserir um nó
    no_arvore* inserir_recursivo(no_arvore* no_atual, int valor_inserir) {
        if (no_atual == NULL) {
            return new no_arvore(valor_inserir);
        }

        if (valor_inserir < no_atual->valor) {
            no_atual->esquerda = inserir_recursivo(no_atual->esquerda, valor_inserir);
        } else if (valor_inserir > no_atual->valor) {
            no_atual->direita = inserir_recursivo(no_atual->direita, valor_inserir);
        }
        // Se valor_inserir == no_atual->valor, não faz nada (não permite duplicados)
        return no_atual;
    }

    // Função auxiliar para encontrar o nó com o menor valor em uma subárvore (sucessor em ordem)
    no_arvore* encontrar_min_recursivo(no_arvore* no_atual) {
        while (no_atual && no_atual->esquerda != NULL) {
            no_atual = no_atual->esquerda;
        }
        return no_atual;
    }

    // Função auxiliar recursiva para remover um nó
    no_arvore* remover_recursivo(no_arvore* no_atual, int valor_remover) {
        if (no_atual == NULL) {
            return no_atual; // Valor não encontrado
        }

        if (valor_remover < no_atual->valor) {
            no_atual->esquerda = remover_recursivo(no_atual->esquerda, valor_remover);
        } else if (valor_remover > no_atual->valor) {
            no_atual->direita = remover_recursivo(no_atual->direita, valor_remover);
        } else {
            // Nó encontrado
            // Caso 1: Nó sem filhos ou com um filho
            if (no_atual->esquerda == NULL) {
                no_arvore* temp = no_atual->direita;
                delete no_atual;
                return temp;
            } else if (no_atual->direita == NULL) {
                no_arvore* temp = no_atual->esquerda;
                delete no_atual;
                return temp;
            }

            // Caso 2: Nó com dois filhos
            // Encontra o sucessor em ordem (menor na subárvore direita)
            no_arvore* temp = encontrar_min_recursivo(no_atual->direita);
            no_atual->valor = temp->valor; // Copia o valor do sucessor
            // Remove o sucessor da subárvore direita
            no_atual->direita = remover_recursivo(no_atual->direita, temp->valor);
        }
        return no_atual;
    }

    // Função auxiliar recursiva para destruir a árvore (liberar memória)
    void destruir_recursivo(no_arvore* no_atual) {
        if (no_atual != NULL) {
            destruir_recursivo(no_atual->esquerda);
            destruir_recursivo(no_atual->direita);
            delete no_atual;
        }
    }

    // Função auxiliar para imprimir a árvore (rotação de 90 graus no sentido anti-horário)
    // Imprime a subárvore direita, depois o nó atual, depois a subárvore esquerda
    void imprimir_recursivo(no_arvore* no_atual, int espaco, int incremento_espaco) const {
        if (no_atual == NULL) {
            return;
        }
        espaco += incremento_espaco;

        imprimir_recursivo(no_atual->direita, espaco, incremento_espaco);

        cout << endl;
        for (int i = incremento_espaco; i < espaco; i++) {
            cout << " ";
        }
        cout << no_atual->valor << "";

        imprimir_recursivo(no_atual->esquerda, espaco, incremento_espaco);
    }
    
    // Função auxiliar para verificar se a árvore está vazia
    bool esta_vazia_recursivo(no_arvore* no_atual) const {
        return no_atual == NULL;
    }


public:
    arvore_binaria() {
        raiz = NULL;
    }

    ~arvore_binaria() {
        destruir_recursivo(raiz);
        raiz = NULL;
    }

    void inserir(int valor_inserir) {
        raiz = inserir_recursivo(raiz, valor_inserir);
    }

    void remover(int valor_remover) {
        raiz = remover_recursivo(raiz, valor_remover);
    }
    
    bool esta_vazia() const {
        return esta_vazia_recursivo(raiz);
    }

    void imprimir_arvore() const {
        if (esta_vazia()) {
            cout << "\n--------------------------------------\n";
            cout <<   "|         Arvore esta vazia...       |\n";
            cout <<   "--------------------------------------\n\n";
            return;
        }
        cout << "--- Representacao da Arvore Binaria (girada 90 graus anti-horario) ---\n";
        cout << "----------------------------------------------------------------------\n";
        cout << "(Raiz esta a esquerda, folhas a direita)\n";
        imprimir_recursivo(raiz, 0, 5); // 5 é o incremento de espaço para cada nível
        cout << "\n\n----------------------------------------------------------------------\n\n";
    }
    
    void limpar_arvore_completa() {
        destruir_recursivo(raiz);
        raiz = NULL;
    }
};

// Função auxiliar para limpar a tela do console.
void limpar_tela_menu_arvore() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Função para executar uma série de ações automatizadas para testar a árvore.
void executar_testes_automaticos_arvore() {
    arvore_binaria ab_teste;

    cout << "Estado Inicial:\n";
    ab_teste.imprimir_arvore();

    cout << "Inserindo 50, 30, 70, 20, 40, 60, 80:\n";
    ab_teste.inserir(50);
    ab_teste.inserir(30);
    ab_teste.inserir(70);
    ab_teste.inserir(20);
    ab_teste.inserir(40);
    ab_teste.inserir(60);
    ab_teste.inserir(80);
    ab_teste.imprimir_arvore();

    cout << "Removendo 20 (folha):\n";
    ab_teste.remover(20);
    ab_teste.imprimir_arvore();

    cout << "Removendo 30 (um filho a direita):\n";
    ab_teste.remover(30);
    ab_teste.imprimir_arvore();
    
    cout << "Inserindo 35:\n";
    ab_teste.inserir(35);
    ab_teste.imprimir_arvore();

    cout << "Removendo 70 (dois filhos):\n";
    ab_teste.remover(70); // Sucessor em ordem é 80
    ab_teste.imprimir_arvore();

    cout << "Removendo 50 (raiz com dois filhos):\n";
    ab_teste.remover(50); // Sucessor em ordem é 60
    ab_teste.imprimir_arvore();

    cout << "Limpando a arvore:\n";
    ab_teste.limpar_arvore_completa();
    ab_teste.imprimir_arvore();

    cout << "Inserindo 10, 5, 15 apos limpar:\n";
    ab_teste.inserir(10);
    ab_teste.inserir(5);
    ab_teste.inserir(15);
    ab_teste.imprimir_arvore();
}

int main() {
    arvore_binaria ab;
    int opcao = 0;
    int valor;
    string mensagem_feedback = "";

    do {
        limpar_tela_menu_arvore();
        cout << "---------------- MENU ARVORE BINARIA ----------------\n";
        cout << "|   1. Inserir elemento                             |\n";
        cout << "|   2. Remover elemento                             |\n";
        cout << "|   3. Limpar arvore completa                       |\n";
        cout << "|   4. Executar testes automaticos                  |\n";
        cout << "|   5. Sair                                         |\n";
        cout << "-----------------------------------------------------\n";

        ab.imprimir_arvore();

        if (!mensagem_feedback.empty()) {
            cout << "" << mensagem_feedback << "";
            mensagem_feedback = "";
        }

        cout << "> Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mensagem_feedback = "Opcao invalida. Tente novamente.\n";
            opcao = 0; // Para garantir que o loop continue se a entrada for inválida
        } else {
            switch (opcao) {
            case 1: {
                limpar_tela_menu_arvore();
                cout << "1. Inserir elemento\n\n";
                ab.imprimir_arvore();
                cout << "Digite o valor a inserir: ";
                cin >> valor;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    mensagem_feedback = "Entrada invalida para o valor. Nada foi inserido.\n";
                } else {
                    ab.inserir(valor);
                    mensagem_feedback = "Elemento " + std::to_string(valor) + " inserido (se nao existia).\n";
                }
                break;
            }
            case 2: {
                if (ab.esta_vazia()){
                     mensagem_feedback = "Falha ao remover. A arvore esta vazia.\n";
                } else {
                    limpar_tela_menu_arvore();
                    cout << "2. Remover elemento\n";
                    ab.imprimir_arvore();
                    cout << "Digite o valor a remover: ";
                    cin >> valor;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        mensagem_feedback = "Entrada invalida para o valor. Nada foi removido.\n";
                    } else {
                        // Poderia adicionar uma função de busca para verificar se o elemento existe antes de tentar remover
                        // e dar um feedback mais preciso, mas por simplicidade, apenas tentamos remover.
                        ab.remover(valor);
                        mensagem_feedback = "Tentativa de remocao do elemento " + std::to_string(valor) + " realizada.\n";
                    }
                }
                break;
            }
            case 3: {
                ab.limpar_arvore_completa();
                mensagem_feedback = "Arvore limpa com sucesso.\n";
                break;
            }
            case 4: {
                limpar_tela_menu_arvore();
                cout << "--- Iniciando testes automaticos da Arvore Binaria ---\n\n";
                executar_testes_automaticos_arvore();
                cout << "--- Testes automaticos finalizados ---\n";
                cout << "Pressione Enter para retornar ao menu...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
                cin.get(); // Espera o Enter
                mensagem_feedback = ""; // Limpa qualquer feedback anterior
                break;
            }
            case 5:
                break; // Sai do loop
            default:
                if (opcao != 0) { // Não mostra mensagem de erro se foi erro de cin.fail() já tratado
                    mensagem_feedback = "Opcao invalida. Tente novamente.\n";
                }
                break;
            }
        }
    } while (opcao != 5);

    limpar_tela_menu_arvore();
    cout << "Programa de Arvore Binaria encerrado.\n";
    return 0;
}
