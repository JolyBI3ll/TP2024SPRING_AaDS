//
// Created by asman on 30.05.2024.
//

#ifndef TPSPRING2024_MODULE3_TASK1_LISTGRAPH_H
#define TPSPRING2024_MODULE3_TASK1_LISTGRAPH_H
#pragma once

#include "IGraph.h"

class ListsGraph : public IGraph {
public:
    ListsGraph(int vertexCount);

    ListsGraph(const IGraph &graph);

    // IGraph
    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

    virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjLists;
    std::vector<std::vector<int>> prevAdjLists;
};

#endif //TPSPRING2024_MODULE3_TASK1_LISTGRAPH_H
