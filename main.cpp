//Дан базовый интерфейс для представления ориентированного графа:
//struct IGraph {
//virtual ~IGraph() {}
//
//	// Добавление ребра от from к to.
//virtual void AddEdge(int from, int to) = 0;
//
//	virtual int VerticesCount() const  = 0;
//
//virtual std::vector<int> GetNextVertices(int vertex) const = 0;
//virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
//};
//
//Необходимо написать несколько реализаций интерфейса:
//ListGraph, хранящий граф в виде массива списков смежности,
//MatrixGraph, хранящий граф в виде матрицы смежности,
//SetGraph, хранящий граф в виде массива хэш-таблиц/сбалансированных деревьев поиска,
//ArcGraph, хранящий граф в виде одного массива пар {from, to}.
//Также необходимо реализовать конструктор, принимающий const IGraph&. Такой конструктор должен скопировать переданный граф в создаваемый объект.
//Для каждого класса создавайте отдельные h и cpp файлы.
//Число вершин графа задается в конструкторе каждой реализации.

#include <iostream>
#include "MatrixGraph.h"
#include "ListGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"

void BFS(const IGraph &graph, int vertex, void(*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> bfsQ;
    bfsQ.push(vertex);
    visited[vertex] = true;
    while (!bfsQ.empty()) {
        int current = bfsQ.front();
        bfsQ.pop();
        visit(current);
        std::vector<int> adjList = graph.GetNextVertices(current);
        for (int nextVertex: adjList) {
            if (!visited[nextVertex]) {
                bfsQ.push(nextVertex);
                visited[nextVertex] = true;
            }
        }
    }
}

void DFS(const IGraph &graph, int vertex, void (*visit)(int)) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::stack<int> dfsStack;
    dfsStack.push(vertex);

    while (!dfsStack.empty()) {
        int current = dfsStack.top();
        dfsStack.pop();

        if (!visited[current]) {
            visit(current);
            visited[current] = true;

            std::vector<int> adjList = graph.GetNextVertices(current);

            for (auto it = adjList.rbegin(); it != adjList.rend(); ++it) {
                if (!visited[*it]) {
                    dfsStack.push(*it);
                }
            }
        }
    }
}

int main() {
    ListsGraph listGraph(8);

    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 4);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(2, 5);
    listGraph.AddEdge(3, 0);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(4, 6);
    listGraph.AddEdge(5, 3);
    listGraph.AddEdge(6, 3);
    listGraph.AddEdge(6, 5);
    listGraph.AddEdge(6, 7);
    listGraph.AddEdge(7, 5);

    std::cout << "BFS LIST GRAPH:   ";
    BFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS LIST GRAPH:   ";
    DFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;
    MatrixGraph matrixGraph(listGraph);
    std::cout << "BFS MATRIX GRAPH: ";
    BFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS MATRIX GRAPH: ";
    DFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;
    SetGraph setGraph(matrixGraph);
    std::cout << "BFS SET GRAPH:    ";
    BFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS SET GRAPH:    ";
    DFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    std::cout << std::endl;
    ArcGraph arcGraph(matrixGraph);
    std::cout << "BFS ARC GRAPH:    ";
    BFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;
    std::cout << "DFS ARC GRAPH:    ";
    DFS(listGraph, 0, [](int vertex) { std::cout << vertex << " "; });
    std::cout << std::endl;

    return 0;
}
