#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::max
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

    // Função auxiliar para encontrar o nó com o menor valor em uma subárvore
    no_arvore* encontrar_min_recursivo(no_arvore* no_atual) {
        while (no_atual && no_atual->esquerda != NULL) {
            no_atual = no_atual->esquerda;
        }
        return no_atual;
    }

    // Função auxiliar recursiva para remover um nó
    no_arvore* remover_recursivo(no_arvore* no_atual, int valor_remover) {
        if (no_atual == NULL) {
            return no_atual;
        }

        if (valor_remover < no_atual->valor) {
            no_atual->esquerda = remover_recursivo(no_atual->esquerda, valor_remover);
        } else if (valor_remover > no_atual->valor) {
            no_atual->direita = remover_recursivo(no_atual->direita, valor_remover);
        } else {
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

    // Função auxiliar recursiva para destruir a árvore
    void destruir_recursivo(no_arvore* no_atual) {
        if (no_atual != NULL) {
            destruir_recursivo(no_atual->esquerda);
            destruir_recursivo(no_atual->direita);
            delete no_atual;
        }
    }
    
    // Função auxiliar para verificar se a árvore está vazia
    bool esta_vazia_recursivo(no_arvore* no_atual) const {
        return no_atual == NULL;
    }
    
    // Função auxiliar para calcular a altura da árvore
    int altura_recursivo(no_arvore* no) const {
        if (!no) return 0;
        return 1 + max(altura_recursivo(no->esquerda), altura_recursivo(no->direita));
    }

    void disposicao_recursivo(no_arvore* no, vector<string>& malha, vector<int>& linha, int profundidade, int altura, int limite_esq, int limite_dir, vector<int>& espacamentos) {
        if (!no) return; // Se o nó é nulo, não faz nada

        int pos_x = (limite_esq + limite_dir) / 2; // Centro horizontal do nó entre os limites esquerdo e direito
        int pos_y = linha[profundidade]; // Linha vertical definida para este nível de profundidade
        string valor_str = to_string(no->valor); // Converte valor do nó em string e centraliza sobre pos_x
        int inicio = pos_x - valor_str.size() / 2;

        for (int i = 0; i < (int)valor_str.size(); ++i)
            malha[pos_y][inicio + i] = valor_str[i];

        // Ligações para filhos à esquerda
        if (no->esquerda && profundidade < altura - 1) {
            int limite_esq_novo = limite_esq;
            int limite_dir_novo = pos_x - 1;
            int pos_x_filho = (limite_esq_novo + limite_dir_novo) / 2;
            int espacamento_vertical = espacamentos[profundidade];

            // Desenha linha diagonal até o nó filho, seguindo a razão entre delta X e delta Y
            for (int passo = 1; passo <= espacamento_vertical; ++passo) {
                int pos_x_inter = pos_x - (pos_x - pos_x_filho) * passo / espacamento_vertical;
                malha[pos_y + passo][pos_x_inter] = '/';
            }

            disposicao_recursivo(no->esquerda, malha, linha, profundidade + 1, altura, limite_esq_novo, limite_dir_novo, espacamentos); // Recursa para desenhar subárvore esquerda
        }

        // Ligações para filhos à direita
        if (no->direita && profundidade < altura - 1) {
            int limite_esq_novo = pos_x + 1;
            int limite_dir_novo = limite_dir;
            int pos_x_filho = (limite_esq_novo + limite_dir_novo) / 2;
            int espacamento_vertical = espacamentos[profundidade];

            for (int passo = 1; passo <= espacamento_vertical; ++passo) {
                int pos_x_inter = pos_x + (pos_x_filho - pos_x) * passo / espacamento_vertical;
                malha[pos_y + passo][pos_x_inter] = '\\';
            }

            disposicao_recursivo(no->direita, malha, linha, profundidade + 1, altura, limite_esq_novo, limite_dir_novo, espacamentos);
        }
    };

    void coletar_valores_em_ordem_recursivo(no_arvore* no_atual, vector<int>& valores) {
        if (no_atual != NULL) {
            coletar_valores_em_ordem_recursivo(no_atual->esquerda, valores);
            valores.push_back(no_atual->valor);
            coletar_valores_em_ordem_recursivo(no_atual->direita, valores);
        }
    }

    void criar_balanceada_recursivo(vector<int>& valores) {
        if (valores.empty()) return;

        int meio = valores.size() / 2;
        inserir(valores[meio]);

        vector<int> esquerda(valores.begin(), valores.begin() + meio);
        vector<int> direita(valores.begin() + meio + 1, valores.end());

        criar_balanceada_recursivo(esquerda);
        criar_balanceada_recursivo(direita);
    }

    void impressao_em_ordem_recursivo(no_arvore* no_atual) {
        if (no_atual != NULL) {
            cout << "Verificando o no: " << no_atual->valor << "\n";
            impressao_em_ordem_recursivo(no_atual->esquerda);
            cout << "Impressao em ordem: " << no_atual->valor << "\n";
            impressao_em_ordem_recursivo(no_atual->direita);
        }
    }

    void impressao_pre_ordem_recursivo(no_arvore* no_atual) {
        if (no_atual != NULL) {
            cout << "Verificando o no: " << no_atual->valor << "\n";
            cout << "Impressao pre ordem: " << no_atual->valor << "\n";
            impressao_pre_ordem_recursivo(no_atual->esquerda);
            impressao_pre_ordem_recursivo(no_atual->direita);
        }
    }

    void impressao_pos_ordem_recursivo(no_arvore* no_atual) {
        if (no_atual != NULL) {
            impressao_pos_ordem_recursivo(no_atual->esquerda);
            impressao_pos_ordem_recursivo(no_atual->direita);
            cout << "Impressao pos ordem: " << no_atual->valor << "\n";
        }
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
    
    bool esta_vazia() {
        return esta_vazia_recursivo(raiz);
    }

    // Imprime a árvore binária dentro de uma caixa centralizada
    void imprimir_arvore_binaria() {
        if (esta_vazia()) {
            cout << "\n--------------------------------------\n";
            cout <<   "|    Arvore binaria esta vazia...    |\n";
            cout <<   "--------------------------------------\n\n";
            return;
        }

        cout << "\n";

        int altura = altura_recursivo(raiz);
        if (altura == 0) return;

        // Calcula espaçamento vertical (linhas de intervalo) e posições de cada nível
        vector<int> espacamentos(altura);
        for (int profundidade = 0; profundidade < altura - 1; ++profundidade)
            espacamentos[profundidade] = 1 << (altura - profundidade - 1);
        espacamentos[altura - 1] = 0;  // Última profundidade não precisa de espaçamento abaixo

        // Determina a linha onde cada nível será desenhado
        vector<int> linha(altura);
        linha[0] = 1;  // Reserva uma linha de margem superior
        for (int profundidade = 1; profundidade < altura; ++profundidade)
            linha[profundidade] = linha[profundidade - 1] + espacamentos[profundidade - 1];

        // Define dimensões da malha de caracteres: colunas e linhas necessárias
        int colunas = (1 << altura) * 3 - 1;
        int linhas = linha[altura - 1] + 1;

        // Inicializa espaço vazio para montagem do diagrama
        vector<string> malha(linhas + 1, string(colunas, ' '));

        disposicao_recursivo(raiz, malha, linha, 0, altura, 0, colunas - 1, espacamentos); // Inicia disposição a partir da raiz, cobrindo toda a largura disponível
        string borda(colunas + 2, '-'); // Desenha as bordas superior e inferior da caixa
        cout << borda << "\n";
        for (auto& linha_str : malha)
            cout << "|" << linha_str << "|\n";
        cout << borda << "\n\n";
    }
    
    void limpar_arvore_binaria() {
        destruir_recursivo(raiz);
        raiz = NULL;
    }

    string balancear_arvore_binaria() {
        if (esta_vazia()) {
            return "A arvore binaria esta vazia. Nao ha nada para balancear.\n\n";
        }
        vector<int> valores;
        coletar_valores_em_ordem_recursivo(raiz, valores);
        limpar_arvore_binaria();
        criar_balanceada_recursivo(valores);
        return "A arvore binaria foi balanceada com sucesso.\n\n";
    }

    void impressao_em_ordem() {
        impressao_em_ordem_recursivo(raiz);
        cout << "\nImpressao em ordem concluida. Pressione Enter para continuar...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        cin.get(); // Espera o Enter
    }

    void impressao_pre_ordem() {
        impressao_pre_ordem_recursivo(raiz);
        cout << "\nImpressao pre ordem concluida. Pressione Enter para continuar...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        cin.get(); // Espera o Enter
    }

    void impressao_pos_ordem() {
        impressao_pos_ordem_recursivo(raiz);
        cout << "\nImpressao pos ordem concluida. Pressione Enter para continuar...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa o buffer de entrada
        cin.get(); // Espera o Enter
    }
};

// Função auxiliar para limpar a tela do console.
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para executar uma série de ações automatizadas para testar a árvore binária.
void executar_testes_automaticos_arvore() {
    arvore_binaria ab_teste;

    cout << "Estado Inicial:\n";
    ab_teste.imprimir_arvore_binaria();

    cout << "Inserindo 50, 30, 70, 20, 40, 60, 80:\n";
    ab_teste.inserir(50);
    ab_teste.inserir(30);
    ab_teste.inserir(70);
    ab_teste.inserir(20);
    ab_teste.inserir(40);
    ab_teste.inserir(60);
    ab_teste.inserir(80);
    ab_teste.imprimir_arvore_binaria();

    cout << "Removendo 20 (folha):\n";
    ab_teste.remover(20);
    ab_teste.imprimir_arvore_binaria();

    cout << "Removendo 30 (um filho a direita):\n";
    ab_teste.remover(30);
    ab_teste.imprimir_arvore_binaria();

    cout << "Inserindo 35:\n";
    ab_teste.inserir(35);
    ab_teste.imprimir_arvore_binaria();

    cout << "Removendo 70 (dois filhos):\n";
    ab_teste.remover(70); // Sucessor em ordem é 80
    ab_teste.imprimir_arvore_binaria();

    cout << "Removendo 50 (raiz com dois filhos):\n";
    ab_teste.remover(50); // Sucessor em ordem é 60
    ab_teste.imprimir_arvore_binaria();

    cout << "Limpando a arvore:\n";
    ab_teste.limpar_arvore_binaria();
    ab_teste.imprimir_arvore_binaria();

    cout << "Inserindo 10, 5, 15 apos limpar:\n";
    ab_teste.inserir(10);
    ab_teste.inserir(5);
    ab_teste.inserir(15);
    ab_teste.imprimir_arvore_binaria();
}

int main() {
    arvore_binaria ab;
    int opcao = 0;
    int valor;
    string mensagem_feedback = "";

    do {
        limpar_tela();
        cout << "---------------- MENU ----------------\n";
        cout << "|   1. Inserir elemento              |\n";
        cout << "|   2. Remover elemento              |\n";
        cout << "|   3. Limpar arvore binaria         |\n";
        cout << "|   4. Balancear arvore binaria      |\n";
        cout << "|   5. Impressao in-ordem            |\n";
        cout << "|   6. Impressao pre-ordem           |\n";
        cout << "|   7. Impressao pos-ordem           |\n";
        cout << "|   8. Sair                          |\n";
        cout << "--------------------------------------\n";

        ab.imprimir_arvore_binaria();

        if (!mensagem_feedback.empty()) {
            cout << "" << mensagem_feedback << "";
            mensagem_feedback = "";
        }

        cout << "> Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mensagem_feedback = "Opcao invalida. Tente novamente.\n\n";
            opcao = 0; // Para garantir que o loop continue se a entrada for inválida
        } else {
            switch (opcao) {
            case 1: {
                limpar_tela();
                cout << "1. Inserir elemento\n";
                ab.imprimir_arvore_binaria();
                cout << "Digite o valor a inserir: ";
                cin >> valor;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    mensagem_feedback = "Entrada invalida para o valor. Nada foi inserido.\n\n";
                } else {
                    ab.inserir(valor);
                    mensagem_feedback = "Elemento " + std::to_string(valor) + " inserido (se nao existia).\n\n";
                }
                break;
            }
            case 2: {
                if (ab.esta_vazia()){
                     mensagem_feedback = "Falha ao remover. A arvore esta vazia.\n\n";
                } else {
                    limpar_tela();
                    cout << "2. Remover elemento\n";
                    ab.imprimir_arvore_binaria();
                    cout << "Digite o valor a remover: ";
                    cin >> valor;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        mensagem_feedback = "Entrada invalida para o valor. Nada foi removido.\n\n";
                    } else {
                        ab.remover(valor);
                        mensagem_feedback = "Tentativa de remocao do elemento " + std::to_string(valor) + " realizada.\n\n";
                    }
                }
                break;
            }
            case 3: {
                ab.limpar_arvore_binaria();
                mensagem_feedback = "Arvore binaria limpa com sucesso.\n\n";
                break;
            }
            case 4: {
                limpar_tela();
                mensagem_feedback = ab.balancear_arvore_binaria();
                break;
            }
            case 5: {
                limpar_tela();
                cout << "5. Impressao em ordem\n\n";
                ab.imprimir_arvore_binaria();
                ab.impressao_em_ordem();
                mensagem_feedback = "Impressao em ordem concluida!\n\n";
                break;
            }
            case 6: {
                limpar_tela();
                cout << "6. Impressao pre ordem\n\n";
                ab.imprimir_arvore_binaria();
                ab.impressao_pre_ordem();
                mensagem_feedback = "Impressao pre ordem concluida!\n\n";
                break;
            }
            case 7: {
                limpar_tela();
                cout << "7. Impressao pos ordem\n\n";
                ab.imprimir_arvore_binaria();
                ab.impressao_pos_ordem();
                mensagem_feedback = "Impressao pos ordem concluida!\n\n";
                break;
            }
            case 8:
                break; // Sai do loop
            default:
                if (opcao != 0) { // Não mostra mensagem de erro se foi erro de cin.fail() já tratado
                    mensagem_feedback = "Opcao invalida. Tente novamente.\n\n";
                }
                break;
            }
        }
    } while (opcao != 8);

    limpar_tela();
    cout << "Programa encerrado.\n";
    return 0;
}
