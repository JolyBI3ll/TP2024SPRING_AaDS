/**
@file
@brief Главная исполняемая программа

Программа для демонстрации работы алгоритма Крускала.
Читает входные данные из стандартного ввода и выводит результат.
*/

#include <iostream>
#include "lists_graph.h"
#include "kruskal_algorithm.h"

/**
@brief Точка входа в программу

Читает данные о графе и вычисляет вес минимального остовного дерева.

@return 0 в случае успешного выполнения

@code
// Пример входных данных:
4 4
1 2 1
2 3 2
3 4 3
1 4 4
// Результат: 6
@endcode
*/
int main() {
    int n, m;
    std::cin >> n >> m;

    int from, to, time;
    ListsGraph graph(n);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> from >> to >> time;
        graph.AddEdge(from - 1, to - 1, time);
    }

    std::cout << KruskalAlgorithm(graph) << std::endl;
    return 0;
}