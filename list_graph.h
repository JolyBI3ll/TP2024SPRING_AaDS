/**
@file
@brief Реализация графа на списках смежности
*/

#ifndef LISTS_GRAPH_H
#define LISTS_GRAPH_H

#include "igraph.h"
#include <vector>
#include <utility>

/**
@brief Реализация графа на основе списков смежности

Класс представляет взвешенный граф, используя два массива списков:
- Прямые списки смежности для исходящих рёбер
- Обратные списки смежности для входящих рёбер

@inherits IGraph
*/
class ListsGraph : public IGraph {
public:
    /**
    @brief Конструктор графа
    @param vertexCount Количество вершин в графе
    */
    explicit ListsGraph(int vertexCount);
    
    // Унаследованные методы от IGraph
    virtual void AddEdge(int from, int to, int weight) override;
    virtual int VerticesCount() const override;
    virtual std::vector<std::pair<int, int>> GetNextVertices(int vertex) const override;
    virtual std::vector<std::pair<int, int>> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<std::pair<int, int>>> adjLists;        /**< Прямые списки смежности: исходящие рёбра */
    std::vector<std::vector<std::pair<int, int>>> prevAdjLists;    /**< Обратные списки смежности: входящие рёбра */
};

#endif // LISTS_GRAPH_H