/**
@file
@brief Реализация алгоритма Крускала

@see KruskalAlgorithm
*/

#include "kruskal_algorithm.h"
#include <algorithm>
#include <vector>
#include <utility>

/**
@brief Реализация алгоритма Крускала

Алгоритм работает в несколько этапов:
1. Сбор всех рёбер графа в список
2. Сортировка рёбер по весу по возрастанию
3. Последовательное добавление рёбер в MST с проверкой на циклы через DSU

@param graph Взвешенный неориентированный граф
@return Суммарный вес минимального остовного дерева

@throw std::runtime_error Если граф не связный

@code
// Пример использования:
ListsGraph graph(4);
graph.AddEdge(0, 1, 1);
graph.AddEdge(1, 2, 2);
graph.AddEdge(2, 3, 3);
graph.AddEdge(0, 3, 4);

int mstWeight = KruskalAlgorithm(graph); // Вернет 6
@endcode
*/
int KruskalAlgorithm(const IGraph &graph) {
    std::vector<std::pair<int, std::pair<int, int>>> edgesList;
    
    // Сбор всех рёбер графа
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        for (auto nextVertex: graph.GetNextVertices(i)) {
            edgesList.emplace_back(nextVertex.second,
                                   std::make_pair(i, nextVertex.first));
        }
    }
    
    // Сортировка рёбер по весу
    std::sort(edgesList.begin(), edgesList.end());

    int minWeight = 0;
    DSU dsu(graph.VerticesCount());
    
    // Построение MST
    for (const auto &edge: edgesList) {
        int firstNeighbour = edge.second.first;
        int secondNeighbour = edge.second.second;
        if (dsu.FindParent(firstNeighbour) != dsu.FindParent(secondNeighbour)) {
            dsu.Union(firstNeighbour, secondNeighbour);
            minWeight += edge.first;
        }
    }
    
    return minWeight;
}