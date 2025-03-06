#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>


#define MAX_N 10000 // Número máximo de itens
#define MAX_C 1000 // Capacidade máxima da mochila


typedef struct
{
   int id; // Identificador do item
   int l; // Tamanho do item
   int p; // Prioridade do item
} item_t;


typedef struct
{
   int f; // Prioridade acumulada
   int c; // Capacidade restante
} node_t;


typedef struct
{
   int x[MAX_N]; // Quantidade de cada item
   int f; // Prioridade acumulada
} solution_t;


int compare_items(const void* a, const void* b)
{
   const item_t* item1 = (const item_t*) a;
   const item_t* item2 = (const item_t*) b;
   double priority1 = (double) item1->p / item1->l;
   double priority2 = (double) item2->p / item2->l;
   if (priority1 > priority2)
   {
       return -1;
   } else if (priority1 < priority2)
   {
       return 1;
   } else
   {
       return 0;
   }
}


int calculate_bound(const item_t* items, int n, int c, int i, int f)
{
   int bound = f;
   int remaining_capacity = c;
   while (i < n && remaining_capacity >= items[i].l)
   {
       bound += items[i].p;
       remaining_capacity -= items[i].l;
       i++;
   }
   if (i < n)
   {
       bound += remaining_capacity * items[i].p / items[i].l;
   }
   return bound;
}


solution_t solve_knapsack_MOT(const item_t* items, int n, int c)
{
    solution_t solution;
    solution.f = 0;
    memset(solution.x, 0, sizeof(solution.x));

    item_t sorted_items[MAX_N];
    memcpy(sorted_items, items, n * sizeof(item_t));
    qsort(sorted_items, n, sizeof(item_t), compare_items);

    int remaining_capacity = c;
    for (int i = 0; i < n; i++)
    {
        if (sorted_items[i].l <= remaining_capacity)
        {
            solution.x[sorted_items[i].id] = 1;
            solution.f += sorted_items[i].p;
            remaining_capacity -= sorted_items[i].l;
        }
    }

    return solution;
}



solution_t solve_knapsack_MOP(const item_t* items, int n, int c)
{
    solution_t solution;
    solution.f = 0;
    memset(solution.x, 0, sizeof(solution.x));

    item_t sorted_items[MAX_N];
    memcpy(sorted_items, items, n * sizeof(item_t));
    qsort(sorted_items, n, sizeof(item_t), compare_items);

    int remaining_capacity = c;
    for (int i = 0; i < n; i++)
    {
        if (sorted_items[i].l <= remaining_capacity)
        {
            solution.x[sorted_items[i].id] = 1;
            solution.f += sorted_items[i].p;
            remaining_capacity -= sorted_items[i].l;
        }
    }

    return solution;
}


solution_t solve_knapsack_MOPT(const item_t* items, int n, int c)
{
    solution_t solution;
    solution.f = 0;
    memset(solution.x, 0, sizeof(solution.x));

    item_t sorted_items[MAX_N];
    memcpy(sorted_items, items, n * sizeof(item_t));
    qsort(sorted_items, n, sizeof(item_t), compare_items);

    int remaining_capacity = c;
    for (int i = 0; i < n; i++)
    {
        if (sorted_items[i].l <= remaining_capacity)
        {
            solution.x[sorted_items[i].id] = 1;
            solution.f += sorted_items[i].p;
            remaining_capacity -= sorted_items[i].l;
        }
    }

    return solution;
}




int calcularLimiteSuperior(int pesoAtual, int valorAtual, int c, const item_t* items, int n, int indice)
{
    int limiteSuperior = valorAtual;
    int pesoRestante = c - pesoAtual;
    int i = indice + 1;

    while (i < n && pesoRestante >= items[i].p) {
        pesoRestante -= items[i].p;
        limiteSuperior += items[i].l;
        i++;
    }

    if (i < n) {
        limiteSuperior += round((pesoRestante * items[i].l) / (double)items[i].p);
    }

    return limiteSuperior;
}


// Função principal do algoritmo Branch and Bound
solution_t branchAndBound(const item_t* items, int n, int c)
{
    int melhorValor = 0;
    int valorAtual = 0;
    int pesoAtual = 0;
    int indice = -1;

    solution_t solution;
    solution.f = 0;
    memset(solution.x, 0, sizeof(solution.x));

    // Vetor para armazenar o estado atual da mochila
    int *solucaoAtual = (int *)malloc(n * sizeof(int));

    // Vetor para armazenar a melhor solução encontrada
    int *melhorSolucao = (int *)malloc(n * sizeof(int));

    // Inicializa a solução atual e a melhor solução encontrada
    for (int i = 0; i < n; i++) {
        solucaoAtual[i] = 0;
        melhorSolucao[i] = 0;
    }

    while (1) {
        // Passo 2: Calcular o limite superior para cada nó
        int limiteSuperior = calcularLimiteSuperior(pesoAtual, valorAtual, c, items, n, indice);

        // Verifica se o limite superior é menor do que o melhor valor encontrado até agora
        // Se for, não há necessidade de explorar esse nó e seus subníveis
        if (limiteSuperior < melhorValor) {
            break;
        }

        // Verifica se chegou ao final da árvore
        if (indice == n - 1) {
            // Atualiza a melhor solução encontrada se necessário
            if (valorAtual > melhorValor) {
                melhorValor = valorAtual;
                for (int i = 0; i < n; i++) {
                    melhorSolucao[i] = solucaoAtual[i];
                }
            }
            break;
        }

        // Passo 3: Selecionar o nó com o maior limite superior e explorá-lo
        indice++;

        // Adiciona o item à mochila
        solucaoAtual[indice] = 1;
        pesoAtual += items[indice].p;
        valorAtual += items[indice].l;

        // Passo 4 (continuação): Adicionar os novos nós à lista de nós a serem explorados
        for (int i = indice + 1; i < n; i++) {
            // Verifica se o item ainda está disponível
            if (pesoAtual + items[i].p <= c) {
                solucaoAtual[i] = 1;
                pesoAtual += items[i].p;
                valorAtual += items[i].l;
            }
        }

        // Passo 5: Repetir os passos 3 e 4

        // Volta para o último item adicionado à mochila
        while (indice >= 0 && solucaoAtual[indice] != 0) {
            solucaoAtual[indice] = 0;
            pesoAtual -= items[indice].p;
            valorAtual -= items[indice].l;
            indice--;
        }

        // Verifica se não há mais nós a serem explorados
        if (indice < 0) {
            break;
        }
    }

    // Preenche a melhor solução encontrada na estrutura solution_t
    for (int i = 0; i < n; i++) {
        solution.x[i] = melhorSolucao[i];
    }
    solution.f = melhorValor;

    // Liberar a memória alocada
    free(solucaoAtual);

    // Imprimir a melhor solução encontrada
    printf("Melhor solucao: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", melhorSolucao[i]);
    }
    printf("\n");

    // Retorna a melhor solução encontrada
    return solution;
}



int main()
{
    srand(time(NULL));

    int min_priority, max_priority;
    int min_size, max_size;
    int n, c;
    double prioridade = 0; 

    printf("Digite o número de itens: ");
    scanf("%d", &n);
    printf("Digite a capacidade da mochila: ");
    scanf("%d", &c);
    printf("Digite o valor mínimo de tamanho: ");
    scanf("%d", &min_size);
    printf("Digite o valor máximo de tamanho: ");
    scanf("%d", &max_size);
    printf("Digite o valor mínimo de prioridade: ");
    scanf("%d", &min_priority);
    printf("Digite o valor máximo de prioridade: ");
    scanf("%d", &max_priority);

    item_t items[MAX_N];
    solution_t solution;

    int option;

    while (1)
    {
        printf("\nSelecione a função a ser testada:\n");
        printf("1. mot()\n");
        printf("2. mopt()\n");
        printf("3. bb()\n");
        printf("4. mop()\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &option);

        clock_t start, end;
        double cpu_time_used;


        if (option == 0)
        {
            printf("Encerrando o programa...\n");
            break;
        }
        else if (option < 1 || option > 4)
        {
            printf("Opção inválida. Tente novamente.\n");
            continue;
        }

        printf("\nTestando a função selecionada:\n");

        for (int k = 0; k < 100; k++)
        {
            for (int i = 0; i < n; i++)
            {
                items[i].id = i;
                items[i].p = min_priority + rand() % (max_priority - min_priority + 1);
                items[i].l = min_size + rand() % (max_size - min_size + 1);
            }

            switch (option)
            {
                case 1:
                    start = clock();
                    solution = solve_knapsack_MOT(items, n, c);
                    end = clock();
                    break;
                case 2:
                    start = clock();
                    solution = solve_knapsack_MOPT(items, n, c);
                    end = clock();
                    break;
                case 3:
                    start = clock();
                    solution = branchAndBound(items, n, c);
                    end = clock();
                    break;
                case 4:
                    start = clock();
                    solution = solve_knapsack_MOP(items, n, c);
                    end = clock();
                    break;
                default:
                    break;
            }
            printf("Solução %d:", k+1);
            printf(" Itens selecionados: ");
            for (int i = 0; i < n; i++)
            {
                if (solution.x[i] == 1)
                {

                    printf("%d, ", items[i].id);
                }
            }
            printf("Prioridade acumulada máxima: %d | ", solution.f);
            prioridade += solution.f; 
        }

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nTempo de execução: %f segundos\nPrioridade Acumulada final: %lf\n", cpu_time_used, prioridade);
        break; 
    }  

   return 0;
}

