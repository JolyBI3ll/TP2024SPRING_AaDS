//
// Created by asman on 30.05.2024.
//
#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int vertexCount) {
    assert(vertexCount > 0);;
    adjMatrix.resize(vertexCount, std::vector<bool>(vertexCount, false));
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    adjMatrix.resize(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false));
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (int to: graph.GetNextVertices(from)) {
            adjMatrix[from][to] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjMatrix.size());
    assert(to >= 0 && to < adjMatrix.size());
    adjMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const {
    return adjMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    std::vector<int> nextVertices;
    for (int to = 0; to < adjMatrix.size(); ++to) {
        if (adjMatrix[vertex][to]) {
            nextVertices.push_back(to);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjMatrix.size());
    std::vector<int> prevVertices;
    for (int from = 0; from < adjMatrix.size(); ++from) {
        if (adjMatrix[from][vertex]) {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
