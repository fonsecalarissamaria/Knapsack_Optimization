# 🎒 Algoritmo de Mochila (Knapsack Problem) com Métodos de Otimização

Este programa implementa diferentes abordagens para resolver o problema da mochila, incluindo métodos baseados em otimização, Branch and Bound (BB) e técnicas heurísticas.

## Descrição

O problema da mochila envolve selecionar itens de uma lista, cada um com um valor (prioridade) e peso (tamanho), de forma que a capacidade total da mochila seja respeitada e o valor total dos itens seja maximizado.

Este código oferece as seguintes implementações para resolver o problema:

- **MOT (Método de Ordenação por Tamanho)**: Resolve o problema ordenando os itens com base na relação entre prioridade e tamanho.
- **MOPT (Método de Ordenação por Prioridade)**: Resolve o problema utilizando uma ordenação prioritária, sem considerar o tamanho.
- **Branch and Bound (BB)**: Método baseado em explorar a árvore de soluções e usar limites superiores para podar caminhos não promissores.
- **MOP (Método de Ordenação por Prioridade)**: Uma variação da abordagem MOT com foco na otimização da prioridade total.

## Estrutura de Dados

### item_t
- **id**: Identificador único do item.
- **l**: Tamanho do item (peso).
- **p**: Prioridade do item (valor).

### node_t
- **f**: Prioridade acumulada.
- **c**: Capacidade restante da mochila.

### solution_t
- **x**: Vetor de soluções representando a quantidade de cada item na mochila.
- **f**: Prioridade acumulada da solução.

## Funções

- **compare_items**: Função de comparação para ordenar os itens com base na relação prioridade/tamanho.
- **calculate_bound**: Calcula o limite superior para uma dada solução.
- **solve_knapsack_MOT, solve_knapsack_MOP, solve_knapsack_MOPT**: Implementações de métodos de solução baseados em otimização e heurísticas.
- **calcularLimiteSuperior**: Calcula o limite superior utilizado no algoritmo Branch and Bound.
- **branchAndBound**: Implementação do algoritmo Branch and Bound para resolver o problema da mochila.
