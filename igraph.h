/**
@file
@brief Интерфейс графа
*/

#ifndef IGRAPH_H
#define IGRAPH_H

#include <vector>
#include <utility>

/**
@brief Абстрактный интерфейс для представления взвешенного графа

Интерфейс определяет основные операции для работы с взвешенным графом.
Поддерживает как ориентированные, так и неориентированные графы.
*/
struct IGraph {
    virtual ~IGraph() {} /**< Виртуальный деструктор для корректного удаления производных классов */

    /**
    @brief Добавить ребро в граф
    @param from Начальная вершина ребра
    @param to Конечная вершина ребра
    @param weight Вес ребра
    */
    virtual void AddEdge(int from, int to, int weight) = 0;

    /**
    @brief Получить количество вершин в графе
    @return Количество вершин
    */
    virtual int VerticesCount() const = 0;

    /**
    @brief Получить список следующих вершин
    @param vertex Исходная вершина
    @return Вектор пар (вершина, вес) - следующие вершины и веса рёбер
    */
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const = 0;

    /**
    @brief Получить список предыдущих вершин
    @param vertex Целевая вершина
    @return Вектор пар (вершина, вес) - предыдущие вершины и веса рёбер
    */
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const = 0;
};

#endif // IGRAPH_H