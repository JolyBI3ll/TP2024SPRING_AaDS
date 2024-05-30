//
// Created by asman on 30.05.2024.
//
#include "ArcGraph.h"

ArcGraph::ArcGraph(int vertexCount) {
    assert(vertexCount > 0);
}

ArcGraph::ArcGraph(const IGraph &graph) {
    for (int from = 0; from < graph.VerticesCount(); ++from) {
        for (int to: graph.GetNextVertices(from)) {
            adjArc.emplace_back(from, to);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && to >= 0);
    adjArc.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    std::unordered_set<int> vertices;
    for (const auto &edge: adjArc) {
        vertices.insert(edge.first);
        vertices.insert(edge.second);
    }
    return vertices.size();
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0);
    std::vector<int> nextVertices;
    for (const auto &edge: adjArc) {
        if (edge.first == vertex) {
            nextVertices.push_back(edge.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    assert(vertex >= 0);
    std::vector<int> prevVertices;
    for (const auto &edge: adjArc) {
        if (edge.second == vertex) {
            prevVertices.push_back(edge.first);
        }
    }
    return prevVertices;
}
