#include <iostream>
#include <chrono>

// Estrutura para armazenar as estatísticas
typedef struct {
    long long trocas;
    long long particionamentos_heapify; // Para Quick Sort (particionamentos) e Heap Sort (heapify)
    double tempo_execucao_ms;
} Estatisticas;

// Função para gerar um vetor de inteiros aleatórios sem repetições
int* gerarVetorAleatorio(int tamanho) {
    int* vetor = new int[tamanho];
    bool* usado = new bool[tamanho];
    for (int i = 0; i < tamanho; ++i) {
        usado[i] = false;
    }

    srand(time(NULL) + clock());

    for (int i = 0; i < tamanho; ++i) {
        int num;
        do {
            num = rand() % tamanho;
        } while (usado[num]);
        vetor[i] = num;
        usado[num] = true;
    }

    delete[] usado;
    return vetor;
}

// Função para copiar um vetor
int* copiarVetor(int* original, int tamanho) {
    int* copia = new int[tamanho];
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

// Função de particionamento para Quick Sort (pivô: último elemento)
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
    stats->particionamentos_heapify++;

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

// Função para reorganizar (heapify) uma sub-árvore
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
    stats->particionamentos_heapify++;
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
        delete[] bubble_vetor;

        // Quick Sort
        int* quick_vetor = copiarVetor(original_vetor, tamanho_atual);
        Estatisticas quick_stats;
        iniciarQuickSort(quick_vetor, tamanho_atual, &quick_stats);
        std::cout << "Quick Sort:\n";
        std::cout << "  Numero de trocas: " << quick_stats.trocas << "\n";
        std::cout << "  Numero de particionamentos: " << quick_stats.particionamentos_heapify << "\n";
        std::cout << "  Tempo de execucao: " << quick_stats.tempo_execucao_ms << " ms\n";
        delete[] quick_vetor;

        // Heap Sort
        int* heap_vetor = copiarVetor(original_vetor, tamanho_atual);
        Estatisticas heap_stats;
        heapSort(heap_vetor, tamanho_atual, &heap_stats);
        std::cout << "Heap Sort:\n";
        std::cout << "  Numero de trocas: " << heap_stats.trocas << "\n";
        std::cout << "  Numero de chamadas para 'heapify': " << heap_stats.particionamentos_heapify << "\n";
        std::cout << "  Tempo de execucao: " << heap_stats.tempo_execucao_ms << " ms\n";
        delete[] heap_vetor;

        delete[] original_vetor;
    }

    return 0;
}
