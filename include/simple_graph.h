#ifndef SIMPLE_GRAPH_H
#define SIMPLE_GRAPH_H

#include <vector>
#include <string>
#include <map>

enum class VertexState
{
    NotProcessed = 0,
    Processed,
    Detected
};

struct node
{
    int left_index{-1};
    int right_index{-1};
    std::string name;
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
    void saveGraph(const std::string &filePath);
private:
    std::vector<std::vector<int>> m_adjMatrix;
    std::vector<std::string> m_vertexes;
    std::map<int, std::string> m_graph;
};

#endif // SIMPLE_GRAPH_H
