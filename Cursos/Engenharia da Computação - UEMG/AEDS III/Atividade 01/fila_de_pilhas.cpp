#include <iostream>
#include <cstdlib> // Para system("cls") ou system("clear")
#include <limits> // Para std::numeric_limits
#include <vector> // Adicionado para std::vector
#include <string>  // Adicionado para std::string
#include <algorithm> // Adicionado para std::reverse
#include <iomanip> // Adicionado para std::setw e std::left

#define CAPACIDADE_MAX_PILHA 3

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
    // Construtor: inicializa uma pilha vazia
    pilha() {
        topo = NULL;
        qtd = 0;
    }

    // Destrutor: libera todos os elementos da pilha
    ~pilha() {
        int val_removido;
        while (!esta_vazia()) {
            remover(val_removido);
        }
    }

    bool inserir(int x) { // Empilha
        if (esta_cheia()) {
            return false;
        }
        no_elemento_pilha* novo = new no_elemento_pilha(x);
        novo->prox = topo;
        topo = novo;
        qtd++;
        return true;
    }

    bool remover(int& val_removido) { // Desempilha e retorna o valor removido
        if (esta_vazia()) {
            return false;
        }
        no_elemento_pilha* aux = topo;
        val_removido = aux->valor;
        topo = topo->prox;
        delete aux;
        qtd--;
        return true;
    }

    bool esta_cheia() const {
        return qtd >= CAPACIDADE_MAX_PILHA;
    }

    bool esta_vazia() const {
        return qtd == 0;
    }

    no_elemento_pilha* get_topo() const {
        return topo;
    }

    // Gera uma representação visual dos slots da pilha (cheios ou vazios)
    vector<string> obter_representacao_visual() const {
        vector<string> slots_visuais(CAPACIDADE_MAX_PILHA);
        for (int i = 0; i < CAPACIDADE_MAX_PILHA; ++i) {
            slots_visuais[i] = "[ ]"; // Slots vazios são sempre "[ ]"
        }

        if (esta_vazia()) {
            return slots_visuais;
        }

        vector<int> elems_para_impressao;
        no_elemento_pilha* no_atual = topo;
        while (no_atual != NULL) {
            elems_para_impressao.push_back(no_atual->valor);
            no_atual = no_atual->prox;
        }

        int idx_slot_visual = CAPACIDADE_MAX_PILHA - qtd; 
        for (int valor_elem : elems_para_impressao) { 
            if (idx_slot_visual < CAPACIDADE_MAX_PILHA) {
                string s_val = std::to_string(valor_elem);
                slots_visuais[idx_slot_visual] = "[" + s_val + "]";
                idx_slot_visual++;
            }
        }
        return slots_visuais;
    }
};

class no_fila_de_pilhas {
public:
    pilha p_interna;
    no_fila_de_pilhas* prox;

    // Construtor: inicializa um nó da fila de pilhas
    no_fila_de_pilhas() {
        prox = NULL;
    }
};

class fila_de_pilhas {
private:
    no_fila_de_pilhas* ini;
    no_fila_de_pilhas* fim;

    // Calcula o maior número de dígitos em um elemento entre todas as pilhas para formatar a saída da impressão da estrutura
    int calcular_max_digitos_na_fila() const {
        int max_d = 1; // Padrão 1 para "[ ]"
        no_fila_de_pilhas* no_atual_fila = ini;
        while (no_atual_fila != NULL) {
            const pilha& p_const = no_atual_fila->p_interna;
            no_elemento_pilha* elem_atual_pilha = p_const.get_topo();
            while (elem_atual_pilha != NULL) {
                string s = std::to_string(elem_atual_pilha->valor);
                if (s.length() > (unsigned int)max_d) {
                    max_d = s.length();
                }
                elem_atual_pilha = elem_atual_pilha->prox;
            }
            no_atual_fila = no_atual_fila->prox;
        }
        return max_d;
    }

public:
    // Construtor: inicializa uma fila de pilhas vazia
    fila_de_pilhas() {
        ini = NULL;
        fim = NULL;
    }

    // Destrutor: libera todos os nós da fila e as pilhas internas
    ~fila_de_pilhas() {
        while (ini != NULL) {
            no_fila_de_pilhas* temp = ini;
            ini = ini->prox;
            delete temp;
        }
        fim = NULL; // Garante que 'fim' também seja resetado
    }

    // Insere um elemento na fila de pilhas. Se a última pilha estiver cheia ou não existir, uma nova pilha é criada.
    void inserir_elemento(int x) {
        if (fim == NULL || fim->p_interna.esta_cheia()) {
            no_fila_de_pilhas* novo_no_fila = new no_fila_de_pilhas();
            novo_no_fila->p_interna.inserir(x);

            if (fim == NULL) {
                ini = fim = novo_no_fila;
            } else {
                fim->prox = novo_no_fila;
                fim = novo_no_fila;
            }
        } else {
            fim->p_interna.inserir(x);
        }
    }

    // Remove um elemento da fila de pilhas (do início da primeira pilha não vazia). Se uma pilha ficar vazia após a remoção, ela é removida da fila e o valor removido é retornado.
    bool remover_elemento(int& val_removido) {
        if (ini == NULL) {
            return false;
        }

        bool sucesso_remocao = ini->p_interna.remover(val_removido);

        if (sucesso_remocao) {
            if (ini->p_interna.esta_vazia()) {
                no_fila_de_pilhas* temp = ini;
                ini = ini->prox;
                delete temp;
                if (ini == NULL) {
                    fim = NULL;
                }
            }
            return true;
        } else {
            no_fila_de_pilhas* temp = ini;
            ini = ini->prox;
            delete temp;
            if (ini == NULL) {
                fim = NULL;
                return false;
            }
            return remover_elemento(val_removido);
        }
    }

    // Remove todas as pilhas da fila, limpando completamente a estrutura.
    void limpar_estrutura_completa() {
        while (ini != NULL) {
            no_fila_de_pilhas* temp = ini;
            ini = ini->prox;
            delete temp;
        }
        fim = NULL;
    }

    // Imprime uma representação visual completa da fila de pilhas no console.
    void imprimir_estrutura_completa() const {
        no_fila_de_pilhas* aux_temp = ini;
        int total_pilhas = 0;
        while (aux_temp != NULL) {
            total_pilhas++;
            aux_temp = aux_temp->prox;
        }
 
        int linha_central_pilha = CAPACIDADE_MAX_PILHA / 2; 

        if (total_pilhas == 0) {
            cout << "\n--------------------------------------\n";
            cout <<   "|    Fila de pilhas esta vazia...    |\n";
            cout <<   "--------------------------------------\n";
            return;
        }

        int max_d_geral = calcular_max_digitos_na_fila();
        int tamanho_representacao = max_d_geral + 2; // Tamanho do número com mais dígitos somando os colchetes

        vector<vector<string>> todas_pilhas_str(total_pilhas);
        no_fila_de_pilhas* no_dados_temp = ini;
        for (int i = 0; i < total_pilhas; ++i) {
            todas_pilhas_str[i] = no_dados_temp->p_interna.obter_representacao_visual();
            no_dados_temp = no_dados_temp->prox;
        }

        if (total_pilhas == 1) {
            string border = string(33 + tamanho_representacao, '-');
            string linha_vazia = "|" + string(31 + tamanho_representacao, ' ') + "|";

            cout << "\n" << border << "\n";
            cout << linha_vazia << "\n";

            vector<string>& rep_pilha_atual = todas_pilhas_str[0];
            for (int i = 0; i < CAPACIDADE_MAX_PILHA; ++i) {
                cout << "|";  
                if (i == linha_central_pilha) {
                    cout << "   Fila -- Pilha 1 --"; 
                } else {
                    cout << string(21, ' '); 
                } 

                if (i == 0) cout << " / -->"; 
                else if (i == CAPACIDADE_MAX_PILHA - 1) cout << " \\ -->"; 
                else cout << " | -->"; 
                
                cout << " "; 
                cout << std::left << std::setw(tamanho_representacao) << rep_pilha_atual[i]; 
                cout << "   |\n"; 
            }
            cout << linha_vazia << "\n";
            cout << border << "\n";
            return;
        }

        string borda_multi = string(39 + tamanho_representacao + 2, '-');
        string linha_vazia_multi = "|" + string(39 + tamanho_representacao, ' ') + "|";

        cout << "\n" << borda_multi << "\n";
        cout << linha_vazia_multi<< "\n";

        if (total_pilhas % 2 == 0) { 
            int idx_separador_fila = total_pilhas / 2 - 1; 

            for (int k = 0; k < total_pilhas; ++k) { 
                vector<string>& rep_pilha_atual = todas_pilhas_str[k];
                for (int i = 0; i < CAPACIDADE_MAX_PILHA; ++i) { 
                    cout << "|";  

                    cout << string(10, ' '); 

                    if (i == linha_central_pilha) { 
                        if (k <= idx_separador_fila) {
                            cout << " / ";
                        } else {
                            cout << " \\ "; 
                        }
                    } else { 
                        if (k == 0 && i == 0) { 
                            cout << "   ";
                        } else if (k == total_pilhas - 1 && i == CAPACIDADE_MAX_PILHA - 1) { 
                            cout << "   ";
                        } else {
                            cout << " | "; 
                        }
                    }

                    if (i == linha_central_pilha) {
                        string pilha_cont = "-- Pilha " + std::to_string(k + 1) + " --";
                        cout << std::left << std::setw(13) << pilha_cont.substr(0, 13);
                    } else {
                        cout << string(13, ' ');
                    }

                    if (i == 0) cout << " / -----> ";
                    else if (i == CAPACIDADE_MAX_PILHA - 1) cout << " \\ -----> "; 
                    else cout << " | -----> "; 
                    
                    cout << std::left << std::setw(tamanho_representacao) << rep_pilha_atual[i];
                    cout << "   |\n"; 
                }

                if (k < total_pilhas - 1) {
                    cout << "|";  
                    if (k == idx_separador_fila) {
                        cout << "   Fila --"; 
                    } else {
                        cout << string(10, ' '); 
                    }
                    cout << " | "; 
                    cout << string(26 + tamanho_representacao, ' '); 
                    cout << "|\n"; 
                }
            }
        } else { 
            int central_pilha_idx = total_pilhas / 2; 

            for (int k = 0; k < total_pilhas; ++k) { 
                vector<string>& rep_pilha_atual = todas_pilhas_str[k];
                for (int i = 0; i < CAPACIDADE_MAX_PILHA; ++i) { 
                    cout << "|";  

                    if (k == central_pilha_idx && i == linha_central_pilha) {
                        cout << "   Fila --";
                    } else {
                        cout << string(10, ' ');
                    }

                    if (i == linha_central_pilha) { 
                        if (k == central_pilha_idx) cout << " | ";
                        else if (k < central_pilha_idx) cout << " / ";
                        else cout << " \\ "; 
                    } else { 
                        if (k == 0 && i == 0) { 
                            cout << "   ";
                        } else if (k == total_pilhas - 1 && i == CAPACIDADE_MAX_PILHA - 1) { 
                            cout << "   ";
                        } else {
                            cout << " | "; 
                        }
                    }
                    
                    if (i == linha_central_pilha) {
                        string pilha_cont = "-- Pilha " + std::to_string(k + 1) + " --";
                        cout << std::left << std::setw(13) << pilha_cont.substr(0, 13);
                    } else {
                        cout << string(13, ' ');
                    }

                    if (i == 0) cout << " / -----> ";
                    else if (i == CAPACIDADE_MAX_PILHA - 1) cout << " \\ -----> "; 
                    else cout << " | -----> "; 

                    cout << std::left << std::setw(tamanho_representacao) << rep_pilha_atual[i];

                    cout << "   "; 
                    cout << "|\n"; 
                }

                if (k < total_pilhas - 1) {
                    cout << "|";  
                    cout << string(10, ' '); 
                    cout << " | ";      
                    cout << string(26 + tamanho_representacao, ' '); 
                    cout << "|\n"; 
                }
            }
        }
        cout << linha_vazia_multi << "\n";
        cout << borda_multi << "\n";
    }
};

// Função para executar uma série de ações automatizadas para testar a fila de pilhas.
void executar_testes_automaticos() {
    fila_de_pilhas fp_teste;

    cout << "\nEstado Inicial:\n";
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 1, 2, 3: (pilha 1 deve encher)\n";
    fp_teste.inserir_elemento(1);
    fp_teste.inserir_elemento(2);
    fp_teste.inserir_elemento(3);
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 4: (deve criar pilha 2)\n";
    fp_teste.inserir_elemento(4);
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 5, 6: (pilha 2 deve encher)\n";
    fp_teste.inserir_elemento(5);
    fp_teste.inserir_elemento(6);
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 7: (deve criar pilha 3)\n";
    fp_teste.inserir_elemento(7);
    fp_teste.imprimir_estrutura_completa();

    int valor;
    cout << "\nRemovendo elementos:\n";
    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 8 (deve ir para pilha 2, que tem espaco [4,5])\n";
    fp_teste.inserir_elemento(8);
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();
    cout << "\n";

    if (fp_teste.remover_elemento(valor)) cout << "Removido: " << valor << "\n";
    else cout << "\nFalha ao remover.\n";
    fp_teste.imprimir_estrutura_completa();

    cout << "\nTentando remover de fila vazia:\n";
    if (!fp_teste.remover_elemento(valor)) cout << "Falha ao remover. (esperado, fila vazia)\n";
    fp_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 10, 11, 12, 13 apos esvaziar completamente\n";
    fp_teste.inserir_elemento(10);
    fp_teste.inserir_elemento(11);
    fp_teste.inserir_elemento(12);
    fp_teste.inserir_elemento(13);
    fp_teste.imprimir_estrutura_completa();

    cout << "\nRemovendo tudo para testar destrutor implicitamente ao sair do main.\n";
    int count = 0;
    while (fp_teste.remover_elemento(valor)) {
        cout << "Removido: " << valor << "\n";
        count++;
    }
    cout << "\nTotal de elementos removidos no loop final: " << count << "\n";
    cout << "Fila final (deve estar vazia):\n";
    fp_teste.imprimir_estrutura_completa();
}

// Função auxiliar para limpar a tela do console.
void limpar_tela_menu() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int main() {
    fila_de_pilhas fp;
    int opcao = 0;
    int valor;
    string mensagem_feedback = "";

    cout << "Programa inicia:\n";

    do {
        limpar_tela_menu();
        cout << "\n---------------- MENU ----------------\n";
        cout <<   "|   1. Inserir elemento              |\n";
        cout <<   "|   2. Remover elemento              |\n";
        cout <<   "|   3. Limpar estrutura completa     |\n";
        cout <<   "|   4. Executar testes automaticos   |\n";
        cout <<   "|   5. Sair                          |\n";
        cout <<   "--------------------------------------\n";

        fp.imprimir_estrutura_completa();

        if (!mensagem_feedback.empty()) {
            cout << mensagem_feedback << "\n";
            mensagem_feedback = "";
        }

        cout << "\n> Escolha uma opcao: ";

        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mensagem_feedback = "\nOpcao invalida. Tente novamente.";
            opcao = 0;
        } else {
            switch (opcao) {
                case 1: {
                    limpar_tela_menu();
                    cout << "1. Inserir elemento\n";
                    fp.imprimir_estrutura_completa();
                    cout << "\nDigite o valor a inserir: ";

                    cin >> valor;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        mensagem_feedback = "\nEntrada invalida para o valor. Nada foi inserido.";
                    } else {
                        fp.inserir_elemento(valor);
                        mensagem_feedback = "\nElemento " + std::to_string(valor) + " inserido.";
                    }
                    break;
                }
                case 2: {
                    if (fp.remover_elemento(valor)) {
                        mensagem_feedback = "\nElemento removido: " + std::to_string(valor) + ".";
                    } else {
                        mensagem_feedback = "\nFalha ao remover. A estrutura pode estar vazia.";
                    }
                    break;
                }
                case 3: {
                    fp.limpar_estrutura_completa();
                    mensagem_feedback = "\nEstrutura limpa com sucesso.";
                    break;
                }
                case 4: {
                    limpar_tela_menu();
                    cout << "*\n";
                    cout << "\n--- Iniciando testes automaticos ---\n";
                    executar_testes_automaticos();
                    cout << "\n--- Testes automaticos finalizados ---\n\n";
                    cout << "Pressione Enter para retornar ao menu...";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
                    mensagem_feedback = "";
                    break;
                }
                case 5:
                    break;
                default:
                    if (opcao != 0) {
                        mensagem_feedback = "\nOpcao invalida. Tente novamente.";
                    }
                    break;
            }
        }
    } while (opcao != 5);

    limpar_tela_menu();
    cout << "Programa encerrado.\n";
    return 0;
}
