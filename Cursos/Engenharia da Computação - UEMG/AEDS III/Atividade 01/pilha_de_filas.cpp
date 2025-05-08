#include <iostream>
#include <cstdlib> // Para system("cls") ou system("clear")
#include <limits> // Para std::numeric_limits
#include <vector> // Adicionado para std::vector
#include <string>  // Adicionado para std::string
#include <algorithm> // Adicionado para std::reverse
#include <iomanip> // Adicionado para std::setw e std::left

#define CAPACIDADE_MAX_FILA 3

using namespace std;

// Função auxiliar para unir um vetor de strings com um separador
string JuntarStrings(const vector<string>& elementos, const string& separador) {
    string resultado = "";
    for (size_t i = 0; i < elementos.size(); ++i) {
        resultado += elementos[i];
        if (i < elementos.size() - 1) {
            resultado += separador;
        }
    }
    return resultado;
}

class no_elemento_fila {
public:
    int valor;
    no_elemento_fila *prox;
    no_elemento_fila *ant;

    // Construtor: inicializa um nó da fila com um valor
    no_elemento_fila(int v) {
        valor = v;
        prox = NULL;
        ant = NULL;
    }
};

class fila {
private:
    int qtd;
    no_elemento_fila *ini;
    no_elemento_fila *fim;

public:
    // Construtor: inicializa uma fila vazia
    fila() {
        qtd = 0;
        ini = NULL;
        fim = NULL;
    }

    // Destrutor: libera todos os elementos da fila
    ~fila() {
        int temp_val_removido;
        while (!esta_vazia()) {
            remover(temp_val_removido);
        }
    }

    // Insere um elemento no fim da fila
    bool inserir(int x) { 
        if (esta_cheia()) {
            return false;
        }
        no_elemento_fila *novo = new no_elemento_fila(x);
        if (esta_vazia()) {
            ini = novo;
            fim = novo;
        } else {
            fim->prox = novo;
            novo->ant = fim;
            fim = novo;
        }
        qtd++;
        return true;
    }

    // Remove um elemento do início da fila e retorna o valor removido
    bool remover(int& val_removido) { 
        if (esta_vazia()) {
            return false;
        }
        no_elemento_fila *aux = ini;
        val_removido = aux->valor;
        if (qtd == 1) {
            ini = NULL;
            fim = NULL;
        } else {
            ini = aux->prox;
            ini->ant = NULL;
        }
        delete aux;
        qtd--;
        return true;
    }

    void imprimir_elementos() const { 
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

    bool esta_vazia() const { 
        return qtd == 0;
    }

    bool esta_cheia() const { 
        return qtd >= CAPACIDADE_MAX_FILA;
    }

    // Retorna a quantidade de elementos na fila
    int get_qtd() const { 
        return qtd;
    }

    // Retorna um ponteiro constante para o início da fila (para cálculos de impressão)
    const no_elemento_fila* get_ini() const {
        return ini;
    }
};

class no_pilha {
public:
    fila f_interna;
    no_pilha *prox;
    no_pilha *ant;

    // Construtor: inicializa um nó da pilha (a fila interna é construída por padrão)
    no_pilha() {
        prox = NULL;
        ant = NULL;
    }
};

class pilha_de_filas {
private:
    int qtd_filas;
    no_pilha *topo;

public:
    // Construtor: inicializa uma pilha de filas vazia
    pilha_de_filas() {
        qtd_filas = 0;
        topo = NULL;
    }

    // Destrutor: libera todos os nós da pilha e as filas internas
    ~pilha_de_filas() {
        limpar_estrutura_completa();
    }

    // Remove todas as filas da pilha, limpando completamente a estrutura.
    void limpar_estrutura_completa() {
        no_pilha *atual = topo;
        while (atual != NULL) {
            no_pilha *proximo_abaixo = atual->prox;
            delete atual;
            atual = proximo_abaixo;
        }
        topo = NULL;
        qtd_filas = 0;
    }

    // Insere um elemento na pilha de filas. Se a fila do topo estiver cheia ou não existir, uma nova fila é criada no topo.
    void inserir_elemento(int x) { 
        if (topo == NULL || topo->f_interna.esta_cheia()) {
            no_pilha *nova_fila_no_topo = new no_pilha();
            nova_fila_no_topo->prox = topo; 
            if (topo != NULL) {
                topo->ant = nova_fila_no_topo; 
            }
            topo = nova_fila_no_topo; 
            topo->ant = NULL; 
            qtd_filas++;
        }
        if (!topo->f_interna.inserir(x)) {
            cout << "Erro ao inserir elemento na fila.\n";
        }
    }

    // Remove um elemento da pilha de filas (do início da fila do topo). Se uma fila ficar vazia após a remoção, ela é removida da pilha.
    bool remover_elemento(int& val_removido) { 
        if (esta_vazia() || topo == NULL) {
            return false;
        }

        // Remove filas vazias do topo antes de tentar remover um elemento
        while (topo != NULL && topo->f_interna.esta_vazia()) {
            no_pilha *aux = topo;
            topo = topo->prox;
            if (topo != NULL) {
                topo->ant = NULL;
            }
            delete aux;
            qtd_filas--;
            if (topo == NULL) {
                return false;
            }
        }
        
        if (topo == NULL) {
            return false;
        }

        if (topo->f_interna.remover(val_removido)) {
            if (topo->f_interna.esta_vazia()) {
                no_pilha *aux = topo;
                topo = topo->prox;
                if (topo != NULL) {
                    topo->ant = NULL;
                }
                delete aux;
                qtd_filas--;
            }
            return true;
        } else {
            return false;
        }
    }

    // Imprime uma representação visual completa da pilha de filas no console.
    void imprimir_estrutura_completa() const { 
        if (esta_vazia() || topo == NULL) {
            cout << "\n--------------------------------------\n";
            cout <<   "|    Pilha de filas esta vazia...    |\n";
            cout <<   "--------------------------------------\n";
            return;
        }

        int num_filas_local = 0;
        no_pilha* cont_pilha = topo;
        while (cont_pilha != NULL) {
            num_filas_local++;
            cont_pilha = cont_pilha->prox;
        }

        int larg_max_dig_geral = 1; 
        no_pilha* aux_calc_larg = topo;
        while (aux_calc_larg != NULL) {
            const no_elemento_fila* ptr_val_elem = aux_calc_larg->f_interna.get_ini();
            while (ptr_val_elem != NULL) {
                string s_num = std::to_string(ptr_val_elem->valor);
                if (s_num.length() > (unsigned int)larg_max_dig_geral) {
                    larg_max_dig_geral = s_num.length();
                }
                ptr_val_elem = ptr_val_elem->prox;
            }
            aux_calc_larg = aux_calc_larg->prox;
        }

        vector<string> partes_conteudo_linha_local;
        no_pilha* conf_imp_atual = topo;
        int idx_rotulo_fila = num_filas_local; 
        while (conf_imp_atual != NULL) {
            vector<string> str_slots_fila_atual;
            vector<int> elems_em_ordem;
            const no_elemento_fila* elem_temp = conf_imp_atual->f_interna.get_ini();
            while(elem_temp != NULL){
                elems_em_ordem.push_back(elem_temp->valor);
                elem_temp = elem_temp->prox;
            }

            for (int i = 0; i < CAPACIDADE_MAX_FILA; ++i) {
                if (i < (int)elems_em_ordem.size()) {
                    string str_val = std::to_string(elems_em_ordem[i]);
                    string str_val_preench = string(larg_max_dig_geral - str_val.length(), ' ') + str_val;
                    str_slots_fila_atual.push_back("[" + str_val_preench + "]");
                } else {
                    string vazio_preench = string(larg_max_dig_geral, ' ');
                    str_slots_fila_atual.push_back("[" + vazio_preench + "]");
                }
            }
            
            string str_elems_unidos = JuntarStrings(str_slots_fila_atual, ", ");
            string parte_linha = "Fila " + std::to_string(idx_rotulo_fila) + " --> " + str_elems_unidos;
            partes_conteudo_linha_local.push_back(parte_linha);
            
            idx_rotulo_fila--;
            conf_imp_atual = conf_imp_atual->prox;
        }

        size_t max_comp_parte_rot_fila = 0;
        for (const string& parte_str : partes_conteudo_linha_local) {
            if (parte_str.length() > max_comp_parte_rot_fila) {
                max_comp_parte_rot_fila = parte_str.length();
            }
        }

        string haste_pilha = "Pilha -- ";
        size_t comp_haste = haste_pilha.length();
        size_t max_comp_con_det_fila = 6 + max_comp_parte_rot_fila; // 6 para " / --> " ou " | --> " ou " \ --> "

        size_t larg_max_cont_total;
        if (num_filas_local == 1) {
            larg_max_cont_total = comp_haste + partes_conteudo_linha_local[0].length();
        } else {
            size_t comp_haste_com_conector = comp_haste + max_comp_con_det_fila;
            size_t comp_haste_so_com_pipe = comp_haste + 1; // Para "|"
            larg_max_cont_total = std::max(comp_haste_com_conector, comp_haste_so_com_pipe);
        }
        
        size_t comp_total_borda = larg_max_cont_total + 8; // 4 espaços de cada lado + 2 "|"
        string str_borda_horiz = string(comp_total_borda, '-');

        cout << "\n" << str_borda_horiz << endl;
        
        string str_topo = "[TOPO]";
        size_t comp_topo = str_topo.length();
        size_t preench_esq_topo_base = (comp_total_borda - 2 - comp_topo) / 2;
        size_t preench_dir_topo_base = comp_total_borda - 2 - comp_topo - preench_esq_topo_base;
        cout << "|" << string(preench_esq_topo_base, ' ') << str_topo 
             << string(preench_dir_topo_base, ' ') << "|" << endl;

        if (num_filas_local == 1) {
            string conteudo_linha_str = haste_pilha + partes_conteudo_linha_local[0];
            cout << "|   " << std::left << std::setw(larg_max_cont_total) << conteudo_linha_str << "   |" << endl;
        } else {
            if (num_filas_local % 2 != 0) { // Número ímpar de filas
                int idx_fila_anexo_haste = num_filas_local / 2;
                for (int i = 0; i < num_filas_local; ++i) {
                    string char_con;
                    if (i == 0) char_con = "/";
                    else if (i == num_filas_local - 1) char_con = "\\";
                    else char_con = "|";

                    string seg_det_fila = char_con + " --> " + partes_conteudo_linha_local[i];
                    string prefixo_linha_atual;

                    if (i == idx_fila_anexo_haste) {
                        prefixo_linha_atual = haste_pilha;
                    } else {
                        prefixo_linha_atual = string(comp_haste, ' ');
                    }
                    string cont_total_linha_atual = prefixo_linha_atual + seg_det_fila;
                    cout << "|   " << std::left << std::setw(larg_max_cont_total) << cont_total_linha_atual << "   |" << endl;
                }
            } else { // Número par de filas
                int idx_fila_apos_linha_haste = num_filas_local / 2 - 1;

                for (int i = 0; i < num_filas_local; ++i) {
                    string char_con;
                    if (i == 0) char_con = "/";
                    else if (i == num_filas_local - 1) char_con = "\\";
                    else char_con = "|";

                    string seg_det_fila = char_con + " --> " + partes_conteudo_linha_local[i];
                    string prefixo_linha_atual = string(comp_haste, ' ');
                    
                    string cont_total_linha_atual = prefixo_linha_atual + seg_det_fila;
                    cout << "|   " << std::left << std::setw(larg_max_cont_total) << cont_total_linha_atual << "   |" << endl;

                    if (i == idx_fila_apos_linha_haste) { 
                        string cont_haste_continuacao = haste_pilha + "|";
                        cout << "|   " << std::left << std::setw(larg_max_cont_total) << cont_haste_continuacao << "   |" << endl;
                    }
                }
            }
        }
        
        string str_base = "[BASE]";
        size_t comp_base = str_base.length();
        preench_esq_topo_base = (comp_total_borda - 2 - comp_base) / 2;
        preench_dir_topo_base = comp_total_borda - 2 - comp_base - preench_esq_topo_base;
        cout << "|" << string(preench_esq_topo_base, ' ') << str_base 
             << string(preench_dir_topo_base, ' ') << "|" << endl;

        cout << str_borda_horiz << endl;
    }

    bool esta_vazia() const { 
        return qtd_filas == 0 || topo == NULL;
    }
};

// Função auxiliar para limpar a tela do console.
void limpar_tela_menu() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

// Função para executar uma série de ações automatizadas para testar a pilha de filas.
void executar_testes_automaticos() {
    pilha_de_filas pdf_teste;
    int valor_removido;

    cout << "\nEstado Inicial:\n";
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 10, 20, 30: (Fila no topo deve encher)\n";
    pdf_teste.inserir_elemento(10); 
    pdf_teste.inserir_elemento(20); 
    pdf_teste.inserir_elemento(30); 
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 40, 50: (Nova fila deve ser criada no topo)\n";
    pdf_teste.inserir_elemento(40); 
    pdf_teste.inserir_elemento(50); 
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nRemovendo elementos:\n";
    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 60, 70, 80, 90: (Novas filas serao criadas conforme necessario)\n";
    pdf_teste.inserir_elemento(60); 
    pdf_teste.inserir_elemento(70); 
    pdf_teste.inserir_elemento(80); 
    pdf_teste.inserir_elemento(90); 
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nRemovendo mais elementos ate esvaziar:\n";
    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();
    
    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();

    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa(); 

    cout << "\nTentando remover de pilha vazia:\n";
    if (!pdf_teste.remover_elemento(valor_removido)) cout << "Falha ao remover (esperado, pilha vazia).\n";
    else cout << "Removido: " << valor_removido << " (inesperado)\n";
    pdf_teste.imprimir_estrutura_completa();

    cout << "\nInserindo 100 apos esvaziar:\n";
    pdf_teste.inserir_elemento(100); 
    pdf_teste.imprimir_estrutura_completa();
    cout << "\nRemovendo o elemento 100:\n";
    if (pdf_teste.remover_elemento(valor_removido)) cout << "Removido: " << valor_removido << "\n"; 
    else cout << "Falha ao remover.\n";
    pdf_teste.imprimir_estrutura_completa();
    cout << "\nTestes com estrutura vazia apos remocao final:\n";
    pdf_teste.imprimir_estrutura_completa();
}

int main() {
    pilha_de_filas pdf;
    int opcao = 0;
    int valor;
    string mensagem_feedback = "";

    do {
        limpar_tela_menu();
        cout << "\n---------------- MENU ----------------\n";
        cout <<   "|   1. Inserir elemento              |\n";
        cout <<   "|   2. Remover elemento              |\n";
        cout <<   "|   3. Limpar estrutura completa     |\n";
        cout <<   "|   4. Executar testes automaticos   |\n";
        cout <<   "|   5. Sair                          |\n";
        cout <<   "--------------------------------------\n";

        pdf.imprimir_estrutura_completa();

        if (!mensagem_feedback.empty()) {
            cout << mensagem_feedback << "\n";
            mensagem_feedback = "";
        }

        cout << "\n> Escolha uma opcao: ";
        cin >> opcao;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            mensagem_feedback = "\nOpcao invalida. Por favor, insira um numero.";
            opcao = 0; 
        } else {
            switch (opcao) {
                case 1: {
                    limpar_tela_menu();
                    cout << "1. Inserir elemento\n";
                    pdf.imprimir_estrutura_completa();
                    cout << "\nDigite o valor a inserir: ";
                    cin >> valor;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        mensagem_feedback = "\nEntrada invalida para o valor. Nada foi inserido.";
                    } else {
                        pdf.inserir_elemento(valor);
                        mensagem_feedback = "\nElemento " + std::to_string(valor) + " inserido.";
                    }
                    break;
                }
                case 2: {
                    int valor_removido;
                    if (pdf.remover_elemento(valor_removido)) {
                        mensagem_feedback = "\nElemento removido: " + std::to_string(valor_removido) + ".";
                    } else {
                        mensagem_feedback = "\nFalha ao remover. A estrutura pode estar vazia.";
                    }
                    break;
                }
                case 3: {
                    pdf.limpar_estrutura_completa();
                    mensagem_feedback = "\nEstrutura limpa com sucesso.";
                    break;
                }
                case 4: {
                    limpar_tela_menu();
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

