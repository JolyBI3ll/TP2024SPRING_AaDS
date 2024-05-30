//
// Created by asman on 30.05.2024.
//

#ifndef TPSPRING2024_MODULE3_TASK1_IGRAPH_H
#define TPSPRING2024_MODULE3_TASK1_IGRAPH_H
#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <stack>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //TPSPRING2024_MODULE3_TASK1_IGRAPH_H
