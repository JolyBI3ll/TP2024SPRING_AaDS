/**
@file
@brief Реализация методов класса ListsGraph

@see ListsGraph
*/

#include "lists_graph.h"
#include <cassert>

/**
@brief Конструктор графа

Создает граф с заданным количеством вершин и инициализирует списки смежности.

@param vertexCount Количество вершин в графе
*/
ListsGraph::ListsGraph(int vertexCount) {
    adjLists.resize(vertexCount);
    prevAdjLists.resize(vertexCount);
}

/**
@brief Добавить ребро в граф

Добавляет взвешенное ребро между двумя вершинами. Проверяет корректность параметров.

@param from Начальная вершина ребра (должна быть в диапазоне [0, vertexCount-1])
@param to Конечная вершина ребра (должна быть в диапазоне [0, vertexCount-1])
@param weight Вес ребра (должен быть неотрицательным)

@throw std::out_of_range Если вершины вне допустимого диапазона
@throw std::invalid_argument Если вес отрицательный
*/
void ListsGraph::AddEdge(int from, int to, int weight) {
    assert(from >= 0 && from < adjLists.size());
    assert(to >= 0 && to < adjLists.size());
    assert(weight >= 0);

    adjLists[from].emplace_back(std::make_pair(to, weight));
    prevAdjLists[to].emplace_back(std::make_pair(from, weight));
}

/**
@brief Получить количество вершин в графе
@return Количество вершин в графе
*/
int ListsGraph::VerticesCount() const {
    return adjLists.size();
}

/**
@brief Получить список следующих вершин

Возвращает все вершины, в которые можно попасть из данной вершины, вместе с весами рёбер.

@param vertex Исходная вершина (должна быть в диапазоне [0, vertexCount-1])
@return Вектор пар (вершина, вес) - следующие вершины
@throw std::out_of_range Если вершина вне допустимого диапазона
*/
std::vector<std::pair<int, int>> ListsGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return adjLists[vertex];
}

/**
@brief Получить список предыдущих вершин

Возвращает все вершины, из которых можно попасть в данную вершину, вместе с весами рёбер.

@param vertex Целевая вершина (должна быть в диапазоне [0, vertexCount-1])
@return Вектор пар (вершина, вес) - предыдущие вершины
@throw std::out_of_range Если вершина вне допустимого диапазона
*/
std::vector<std::pair<int, int>> ListsGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return prevAdjLists[vertex];
}