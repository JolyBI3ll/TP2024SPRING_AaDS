#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
};

class ListsGraph : public IGraph {
public:
    ListsGraph(int vertexCount);

    ListsGraph(const IGraph &graph);

    virtual void AddEdge(int from, int to) override;

    virtual int VerticesCount() const override;

    virtual std::vector<int> GetNextVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjLists;
};

ListsGraph::ListsGraph(int vertexCount) {
    assert(vertexCount > 0);
    adjLists.resize(vertexCount);
}

ListsGraph::ListsGraph(const IGraph &graph) {
    adjLists.resize(graph.VerticesCount());
    for (int i = 0; i < VerticesCount(); ++i) {
        adjLists[i] = graph.GetNextVertices(i);
    }
}

void ListsGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjLists.size());
    assert(to >= 0 && to < adjLists.size());
    adjLists[from].push_back(to);
    adjLists[to].push_back(from);
}

int ListsGraph::VerticesCount() const {
    return adjLists.size();
}

std::vector<int> ListsGraph::GetNextVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjLists.size());
    return adjLists[vertex];
}

int CountShortestPaths(const IGraph &graph, int start, int end) {
    std::vector<int> distance(graph.VerticesCount(), -1);
    std::vector<int> pathCount(graph.VerticesCount(), 0);

    std::queue<int> bfsQueue;
    bfsQueue.push(start);
    distance[start] = 0;
    pathCount[start] = 1;

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        for (int next: graph.GetNextVertices(current)) {
            if (distance[next] == -1) {
                distance[next] = distance[current] + 1;
                bfsQueue.push(next);
            }
            if (distance[next] == distance[current] + 1) {
                pathCount[next] += pathCount[current];
            }
        }
    }

    return pathCount[end];
}

int main() {
    int v, n;
    std::cin >> v >> n;
    ListsGraph graph(v);

    for (int i = 0; i < n; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    int u, w;
    std::cin >> u >> w;

    int result = CountShortestPaths(graph, u, w);
    std::cout << result << std::endl;

    return 0;
}