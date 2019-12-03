#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H

#include <vector>
#include <string>
#include <map>

enum class VertexState
{
    Undetected = 0,
    Detected,
    Visited
};

class simple_graph
{
public:
    simple_graph(std::string fileName,
                 std::string matrixEntity = "Matrix:",
                 std::string vertexEntity = "Vertex:");

    void printUserData() const;
    void printGraph() const;
    void calculateGraph();
private:
    std::vector<std::vector<int>> m_adjMatrix;
    std::vector<std::string> m_vertexes;
    std::map<int, std::string> m_graph;
};

#endif // SIMPLE_GRAPH_H
