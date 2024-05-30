//
// Created by asman on 30.05.2024.
//
#include "SetGraph.h"

SetGraph::SetGraph(int vertexCount) {
    assert(vertexCount > 0);
    adjSet.resize(vertexCount);
}

SetGraph::SetGraph(const IGraph &graph) {
    adjSet.resize(graph.VerticesCount());
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (int to: graph.GetNextVertices(from)) {
            adjSet[from].insert(to);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjSet.size());
    assert(to >= 0 && to < adjSet.size());
    adjSet[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return adjSet.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    std::vector<int> nextVertices(adjSet[vertex].begin(), adjSet[vertex].end());
    return nextVertices;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjSet.size());
    std::vector<int> prevVertices;
    for (int from = 0; from < adjSet.size(); ++from) {
        if (adjSet[from].find(vertex) != adjSet[from].end()) {
            prevVertices.push_back(from);
        }
    }
    return prevVertices;
}
