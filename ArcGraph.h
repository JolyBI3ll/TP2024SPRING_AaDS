//
// Created by asman on 30.05.2024.
//

#ifndef TPSPRING2024_MODULE3_TASK1_ARCGRAPH_H
#define TPSPRING2024_MODULE3_TASK1_ARCGRAPH_H
#pragma once

#include "IGraph.h"

class ArcGraph : public IGraph {
public:
    ArcGraph(int vertexCount);

    ArcGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> adjArc;
};

#endif //TPSPRING2024_MODULE3_TASK1_ARCGRAPH_H

