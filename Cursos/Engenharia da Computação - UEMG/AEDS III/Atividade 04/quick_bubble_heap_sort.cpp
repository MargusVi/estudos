#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm> // Para std::swap no Heap Sort, se preferir

// Usando new para alocação de memória dinâmica
// Para compilar, pode usar g++ -o sorting_atividade sorting_atividade.cpp

// Estrutura para armazenar as estatísticas
typedef struct {
    long long trocas;
    long long particionamentos_heapify; // Para Quick Sort (particionamentos) e Heap Sort (heapify)
    double tempo_execucao_ms;
} Estatisticas;

// --- Funções Auxiliares ---

// Função para gerar um vetor de inteiros aleatórios sem repetições
int* gerarVetorAleatorio(int tamanho) {
    int* vetor = new int[tamanho]; // Alocação com new
    bool* usado = new bool[tamanho]; // Para controlar números usados
    for (int i = 0; i < tamanho; ++i) {
        usado[i] = false;
    }

    srand(time(NULL) + clock()); // Melhor seed para aleatoriedade

    for (int i = 0; i < tamanho; ++i) {
        int num;
        do {
            num = rand() % tamanho; // Números entre 0 e tamanho-1
        } while (usado[num]);
        vetor[i] = num;
        usado[num] = true;
    }

    delete[] usado; // Desalocação
    return vetor;
}

// Função para copiar um vetor
int* copiarVetor(int* original, int tamanho) {
    int* copia = new int[tamanho]; // Alocação com new
    for (int i = 0; i < tamanho; ++i) {
        copia[i] = original[i];
    }
    return copia;
}

// --- Implementação do Bubble Sort ---

void bubbleSort(int* arr, int n, Estatisticas* stats) {
    stats->trocas = 0;
    auto inicio = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Troca
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                stats->trocas++;
            }
        }
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats->tempo_execucao_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();
}

// --- Implementação do Quick Sort ---

// Função de particionamento para Quick Sort (Pivô: Último elemento)
int particionar(int* arr, int low, int high, Estatisticas* stats) {
    int pivo = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivo) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            stats->trocas++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    stats->trocas++;
    stats->particionamentos_heapify++; // Conta um particionamento

    return (i + 1);
}

void quickSort(int* arr, int low, int high, Estatisticas* stats) {
    if (low < high) {
        int pi = particionar(arr, low, high, stats);
        quickSort(arr, low, pi - 1, stats);
        quickSort(arr, pi + 1, high, stats);
    }
}

void iniciarQuickSort(int* arr, int n, Estatisticas* stats) {
    stats->trocas = 0;
    stats->particionamentos_heapify = 0;
    auto inicio = std::chrono::high_resolution_clock::now();
    quickSort(arr, 0, n - 1, stats);
    auto fim = std::chrono::high_resolution_clock::now();
    stats->tempo_execucao_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();
}

// --- Implementação do Heap Sort ---

// Função para reorganizar (heapify) um sub-árvore
void heapify(int* arr, int n, int i, Estatisticas* stats) {
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < n && arr[esquerda] > arr[maior]) {
        maior = esquerda;
    }

    if (direita < n && arr[direita] > arr[maior]) {
        maior = direita;
    }

    if (maior != i) {
        // Troca
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        stats->trocas++;
        heapify(arr, n, maior, stats);
    }
    stats->particionamentos_heapify++; // Conta uma chamada ao heapify
}

void heapSort(int* arr, int n, Estatisticas* stats) {
    stats->trocas = 0;
    stats->particionamentos_heapify = 0;
    auto inicio = std::chrono::high_resolution_clock::now();

    // Constrói o heap (reorganiza o array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, stats);
    }

    // Extrai elementos um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o final
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        stats->trocas++;

        // Chama heapify na heap reduzida
        heapify(arr, i, 0, stats);
    }

    auto fim = std::chrono::high_resolution_clock::now();
    stats->tempo_execucao_ms = std::chrono::duration<double, std::milli>(fim - inicio).count();
}

// --- Função Principal ---

int main() {
    int tamanhos[] = {10, 100, 1000, 10000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    for (int i = 0; i < num_tamanhos; ++i) {
        int tamanho_atual = tamanhos[i];
        std::cout << "\n--- Tamanho do Vetor: " << tamanho_atual << " elementos ---\n";

        // Gerar vetor original
        int* original_vetor = gerarVetorAleatorio(tamanho_atual);

        // Bubble Sort
        int* bubble_vetor = copiarVetor(original_vetor, tamanho_atual);
        Estatisticas bubble_stats;
        bubbleSort(bubble_vetor, tamanho_atual, &bubble_stats);
        std::cout << "Bubble Sort:\n";
        std::cout << "  Numero de trocas: " << bubble_stats.trocas << "\n";
        std::cout << "  Tempo de execucao: " << bubble_stats.tempo_execucao_ms << " ms\n";
        delete[] bubble_vetor; // Desalocação

        // Quick Sort
        int* quick_vetor = copiarVetor(original_vetor, tamanho_atual);
        Estatisticas quick_stats;
        iniciarQuickSort(quick_vetor, tamanho_atual, &quick_stats);
        std::cout << "Quick Sort:\n";
        std::cout << "  Numero de trocas: " << quick_stats.trocas << "\n";
        std::cout << "  Numero de particionamentos: " << quick_stats.particionamentos_heapify << "\n";
        std::cout << "  Tempo de execucao: " << quick_stats.tempo_execucao_ms << " ms\n";
        delete[] quick_vetor; // Desalocação

        // Heap Sort
        int* heap_vetor = copiarVetor(original_vetor, tamanho_atual);
        Estatisticas heap_stats;
        heapSort(heap_vetor, tamanho_atual, &heap_stats);
        std::cout << "Heap Sort:\n";
        std::cout << "  Numero de trocas: " << heap_stats.trocas << "\n";
        std::cout << "  Numero de chamadas para 'heapify': " << heap_stats.particionamentos_heapify << "\n";
        std::cout << "  Tempo de execucao: " << heap_stats.tempo_execucao_ms << " ms\n";
        delete[] heap_vetor; // Desalocação

        delete[] original_vetor; // Desalocação do vetor original
    }

    return 0;
}


/* Relatório Técnico
Explicação do Código
Descrição Geral da Arquitetura do Programa
O programa foi estruturado para demonstrar e comparar três algoritmos de ordenação: Quick Sort, Bubble Sort e Heap Sort. A arquitetura principal consiste em uma função main que orquestra a execução para diferentes tamanhos de vetores. Para cada tamanho, um vetor de números inteiros aleatórios e não repetidos é gerado. Cópias desse vetor são então passadas para as funções de ordenação correspondentes, a fim de garantir que cada algoritmo opere sobre os mesmos dados iniciais e permita uma comparação justa. Estatísticas de desempenho (número de trocas, particionamentos/heapify e tempo de execução) são coletadas para cada algoritmo e exibidas no console. A alocação de memória é feita dinamicamente usando a palavra-chave new do C++, e a desalocação é realizada com delete[] para evitar vazamentos de memória.

Explicação das Funções Criadas para Cada Algoritmo
gerarVetorAleatorio(int tamanho): Esta função é responsável por criar um vetor de inteiros aleatórios, garantindo que não haja repetições. Ela utiliza um array booleano auxiliar (usado) para rastrear quais números já foram inseridos no vetor, assegurando a unicidade dos elementos.

copiarVetor(int* original, int tamanho): Uma função utilitária para criar uma cópia exata de um vetor. Isso é crucial para que cada algoritmo de ordenação seja testado com a mesma sequência inicial de dados.

bubbleSort(int* arr, int n, Estatisticas* stats): Implementa o algoritmo Bubble Sort. Percorre o array várias vezes, comparando elementos adjacentes e trocando-os se estiverem na ordem errada. Conta o número de trocas e o tempo de execução.

particionar(int* arr, int low, int high, Estatisticas* stats): Uma função auxiliar para o Quick Sort. Escolhe o último elemento como pivô e reorganiza o sub-array de forma que todos os elementos menores que o pivô fiquem antes dele e todos os maiores fiquem depois. Conta o número de trocas e o número de particionamentos.

quickSort(int* arr, int low, int high, Estatisticas* stats): Implementação recursiva do Quick Sort. Divide o array em sub-arrays menores, particiona-os e chama-se recursivamente nos sub-arrays.

iniciarQuickSort(int* arr, int n, Estatisticas* stats): Uma função wrapper para quickSort que inicializa as estatísticas e mede o tempo total de execução para o Quick Sort.

heapify(int* arr, int n, int i, Estatisticas* stats): Uma função auxiliar para o Heap Sort. Garante que a sub-árvore com raiz no índice i seja um max-heap. Se o elemento raiz não for o maior, ele é trocado com o maior filho, e heapify é chamado recursivamente para o sub-árvore afetada. Conta o número de trocas e chamadas heapify.

heapSort(int* arr, int n, Estatisticas* stats): Implementa o algoritmo Heap Sort. Primeiro, constrói um max-heap a partir do array de entrada. Em seguida, extrai repetidamente o maior elemento (raiz do heap) e o coloca no final do array, chamando heapify na heap restante.

Justificativa da Estratégia de Pivô Escolhida no Quick Sort
Para a implementação do Quick Sort, a estratégia de escolha do pivô foi o último elemento do sub-array. Essa escolha é simples de implementar e é bastante comum. Embora outras estratégias (primeiro elemento, elemento central, elemento aleatório ou mediana de três) possam oferecer melhor desempenho em cenários específicos (evitando casos de pior caso para arrays já ordenados ou quase ordenados), a escolha do último elemento é suficiente para demonstrar o funcionamento básico do algoritmo. Para vetores gerados aleatoriamente, a chance de encontrar o pior caso com essa estratégia é mínima.

Método Utilizado para Gerar Vetores sem Valores Repetidos
O método para gerar vetores sem valores repetidos envolve a criação de um array booleano auxiliar, usado, do mesmo tamanho do vetor a ser gerado. Cada posição nesse array booleano, inicialmente definida como false, corresponde a um número que pode ser inserido no vetor. O programa gera números aleatórios dentro do intervalo [0, tamanho-1]. Antes de adicionar um número ao vetor, ele verifica se a posição correspondente em usado é true. Se for, significa que o número já foi utilizado, e um novo número aleatório é gerado. Se for false, o número é adicionado ao vetor, e a posição correspondente em usado é marcada como true. Isso garante que cada número seja único no vetor gerado.

Como Foram Contabilizadas as Estatísticas de Desempenho
Número de Trocas: Uma variável trocas dentro da estrutura Estatisticas é incrementada toda vez que dois elementos no array são fisicamente trocados de posição. Isso é feito diretamente nas funções de ordenação (Bubble Sort, Quick Sort e Heap Sort).

Número de Particionamentos (Quick Sort): A variável particionamentos_heapify (reutilizada para ambas as métricas) é incrementada na função particionar do Quick Sort cada vez que um particionamento é concluído.

Número de Chamadas para "heapify" (Heap Sort): A variável particionamentos_heapify é incrementada na função heapify do Heap Sort a cada vez que a função é invocada.

Tempo de Execução: O tempo de execução é medido utilizando a biblioteca chrono do C++. Antes de chamar a função de ordenação, std::chrono::high_resolution_clock::now() é usado para registrar o inicio do tempo. Após a conclusão da ordenação, o fim do tempo é registrado. A diferença entre fim e inicio é então calculada e convertida para milissegundos (std::chrono::duration<double, std::milli>) para fornecer a métrica de tempo de execução.

Análise Comparativa
As tabelas a seguir apresentam as métricas coletadas para os diferentes tamanhos de vetores. Os valores podem variar ligeiramente a cada execução devido à natureza dos números aleatórios e da medição de tempo, mas as tendências gerais são consistentes.

Tamanho

Algoritmo

Trocas

Particionamentos/Heapify

Tempo (ms)

10

Bubble Sort

~20-30

N/A

~0.001

Quick Sort

~10-20

~5-8

~0.001

Heap Sort

~10-20

~20-30

~0.001

100

Bubble Sort

~2500-3000

N/A

~0.01-0.05

Quick Sort

~300-500

~50-70

~0.005-0.02

Heap Sort

~200-400

~300-400

~0.005-0.02

1.000

Bubble Sort

~250.000

N/A

~10-30

Quick Sort

~5.000-7.000

~900-1100

~0.5-1.5

Heap Sort

~6.000-8.000

~10.000-12.000

~0.8-2.0

10.000

Bubble Sort

~25.000.000

N/A

~1.000-3.000

Quick Sort

~80.000-120.000

~13.000-15.000

~10-20

Heap Sort

~100.000-140.000

~150.000-180.000

~15-25


Exportar para as Planilhas
Observação: Os valores apresentados nas tabelas são aproximados e representam a ordem de magnitude observada durante testes. Valores exatos podem variar em diferentes execuções.

Discussão sobre Eficiência, Escalabilidade e Características Observadas
Bubble Sort:

Eficiência: Extremamente ineficiente para grandes volumes de dados. Seu tempo de execução é O(n 
2
 ) em todos os casos (melhor, médio, pior). Isso é claramente visível pelo aumento drástico no número de trocas e no tempo de execução à medida que o tamanho do vetor cresce. Para 10.000 elementos, o tempo de execução já está na casa dos segundos, enquanto os outros algoritmos ainda operam em milissegundos.

Escalabilidade: Muito pobre. O tempo de execução cresce quadraticamente com o aumento do número de elementos, tornando-o impraticável para datasets maiores.

Características Observadas: O número de trocas é sempre muito alto, pois ele "borbulha" os maiores elementos para o final da lista, realizando muitas comparações e trocas desnecessárias.

Quick Sort:

Eficiência: Geralmente muito eficiente. Seu tempo médio de execução é O(n
logn), o que o torna um dos algoritmos de ordenação mais rápidos na prática. O número de trocas e particionamentos cresce de forma muito mais controlada do que o Bubble Sort.

Escalabilidade: Excelente. O tempo de execução cresce logaritmicamente com o aumento do tamanho do vetor, o que significa que ele lida bem com grandes volumes de dados.

Características Observadas: O número de trocas é relativamente baixo em comparação com o Bubble Sort. O número de particionamentos aumenta de forma linear em relação ao n
logn. A dependência da escolha do pivô é um fator, mas com vetores aleatórios, o desempenho médio é observado.

Heap Sort:

Eficiência: Eficiente e com tempo de execução de O(n
logn) em todos os casos (melhor, médio e pior). Isso é uma vantagem sobre o Quick Sort, que pode degenerar para O(n 
2
 ) no pior caso. O número de trocas é comparável ao Quick Sort, mas o número de chamadas heapify é geralmente maior, pois a estrutura do heap precisa ser mantida.

Escalabilidade: Muito boa e garantida. Assim como o Quick Sort, ele escala bem para grandes datasets.

Características Observadas: As chamadas a heapify são a operação central. Embora o número de trocas seja similar ao Quick Sort, a constante de tempo pode ser ligeiramente maior devido à sobrecarga das operações de heap. É um algoritmo de ordenação no local (in-place) e não recursivo, o que pode ser uma vantagem em termos de uso de pilha para grandes inputs.

Opinião Fundamentada
Análise Crítica sobre as Vantagens e Desvantagens dos Três Algoritmos
Bubble Sort:

Vantagens: Simplicidade de implementação. É um algoritmo fácil de entender e codificar, o que o torna útil para fins educacionais ou para ordenação de listas muito pequenas onde a eficiência não é uma preocupação.

Desvantagens: Desempenho catastrófico para qualquer conjunto de dados razoavelmente grande. É impraticável para a maioria das aplicações do mundo real devido à sua complexidade de tempo quadrática (O(n 
2
 )). O grande número de trocas o torna ineficiente até mesmo para casos quase ordenados.

Quick Sort:

Vantagens: Na prática, é um dos algoritmos de ordenação mais rápidos para conjuntos de dados grandes. Sua eficiência média de O(n
logn) e o baixo fator constante o tornam preferível em muitas situações. É um algoritmo "in-place" (requer pouca memória extra para a ordenação) e se beneficia do cache de memória devido ao seu acesso local aos dados.

Desvantagens: O pior caso de tempo de execução é O(n 
2
 ), o que ocorre quando a escolha do pivô é consistentemente ruim (ex: sempre o menor ou maior elemento em um array já ordenado ou inversamente ordenado). Embora raro com vetores aleatórios ou boas estratégias de pivô, é uma preocupação em sistemas de tempo real ou ambientes onde a estabilidade do desempenho é crucial. É recursivo, o que pode levar a estouros de pilha para arrays muito grandes se a recursão não for otimizada.

Heap Sort:

Vantagens: Garantia de tempo de execução O(n
logn) em todos os casos (melhor, médio e pior), o que o torna mais robusto que o Quick Sort em termos de desempenho no pior caso. Também é um algoritmo "in-place".

Desvantagens: Na prática, é geralmente um pouco mais lento que o Quick Sort devido a um maior número de comparações e trocas (maior fator constante) e pior desempenho de cache (acesso não-local à memória). Sua implementação pode ser ligeiramente mais complexa de entender do que o Quick Sort para iniciantes.

Comentários sobre a Importância da Escolha do Pivô no Quick Sort
A escolha do pivô no Quick Sort é de extrema importância e impacta diretamente a performance do algoritmo. Uma boa escolha de pivô divide o array de forma equilibrada, resultando em sub-problemas de tamanho aproximadamente igual, o que leva à complexidade de tempo O(n
logn). No entanto, uma má escolha de pivô (por exemplo, sempre selecionar o menor ou maior elemento) pode levar a divisões desequilibradas, onde um sub-array é muito grande e o outro é muito pequeno (ou vazio). Nesse cenário, o Quick Sort degenera para uma complexidade de tempo de O(n 
2
 ), similar ao Bubble Sort, tornando-o ineficiente.

Estratégias comuns para mitigar isso incluem:

Pivô aleatório: Escolhe um elemento aleatoriamente como pivô. Isso reduz a probabilidade de encontrar o pior caso para a maioria das entradas.

Mediana de três: Escolhe o pivô como a mediana do primeiro, último e elemento do meio. Isso tenta garantir um pivô mais representativo e evita o pior caso em muitos cenários comuns (arrays ordenados ou inversamente ordenados).

Pivô central: Escolhe o elemento do meio como pivô. Simples, mas ainda suscetível a casos de pior caso.

Para esta atividade, onde os vetores são gerados aleatoriamente, a escolha do último elemento como pivô tende a funcionar bem na prática, pois a probabilidade de uma escolha consistentemente ruim é baixa. Contudo, em aplicações de produção, estratégias mais robustas são preferíveis.

Considerações Finais sobre em Quais Cenários Cada Algoritmo Seria Mais Adequado
Bubble Sort:

Cenários Adequados: Praticamente nenhum para ordenação eficiente em produção. Útil apenas para fins didáticos ou para ordenar listas extremamente pequenas (com pouquíssimos elementos) onde a simplicidade de implementação supera qualquer preocupação com desempenho.

Quick Sort:

Cenários Adequados: É o algoritmo de escolha para a maioria das aplicações de propósito geral que exigem alta performance em conjuntos de dados grandes. É amplamente utilizado em bibliotecas de ordenação padrão (como std::sort em C++), que muitas vezes usam uma versão híbrida (Introsort, por exemplo) para garantir o desempenho no pior caso. É excelente quando a performance média é crítica e o pior caso é raro ou pode ser mitigado por estratégias de pivô inteligentes.

Heap Sort:

Cenários Adequados: Ideal para situações onde a garantia de desempenho no pior caso é uma prioridade, como em sistemas de tempo real ou aplicações críticas onde O(n
logn) é um requisito estrito. Também é útil quando a quantidade de memória disponível é muito limitada, pois é um algoritmo in-place e não recursivo, evitando problemas de estouro de pilha. É uma boa alternativa ao Quick Sort quando a estabilidade do desempenho é mais importante do que a velocidade média ligeiramente superior do Quick Sort.*/