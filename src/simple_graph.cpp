#include <fstream>
#include <iostream>
#include <queue>
#include "../include/simple_graph.h"

simple_graph::simple_graph(std::string fileName, std::string matrixEntity, std::string vertexEntity)
{

    std::ifstream file(fileName);
    if (!file.is_open())
        throw std::runtime_error("file not open");

    std::string now_string;
    std::getline(file, now_string);

    if (now_string != matrixEntity)
        throw std::runtime_error("not correct file");

    std::getline(file, now_string);

    auto matrix_size = now_string.length();
    std::cout << "Matrix dimension: " << matrix_size
              << "x" << matrix_size
              << std::endl;

    m_adjMatrix = std::vector<std::vector<int>>(matrix_size, std::vector<int>(matrix_size, 0));

    for (auto &v:m_adjMatrix)
    {
        for (size_t i = 0; i < now_string.length(); ++i)
        {
            v[i] = std::stoi(now_string.substr(i, 1));
        }

        std::getline(file, now_string);

        if (!file.good())
            throw std::runtime_error("not correct file");

        if (now_string == vertexEntity)
            break;
    }

    m_vertexes = std::vector<std::string>(matrix_size);

    for (auto &v:m_vertexes)
    {
        std::getline(file, now_string);

        v = now_string;

        if (!file.good())
            throw std::runtime_error("not correct file");
    }
}

void simple_graph::printUserData() const
{
    std::cout << "Your matrix:" << std::endl;
    for (const auto &v:m_adjMatrix)
    {
        for(const auto &ve:v)
            std::cout << ve << " ";
        std::cout << std::endl;
    }

    std::cout << "Your vertexes:" << std::endl;
    for (const auto &v:m_vertexes)
        std::cout << v << std::endl;
}

void simple_graph::printGraph() const
{
    for (const auto &v:m_graph)
        std::cout << v.second << " : " << v.first << std::endl;
}

void simple_graph::calculateGraph()
{

    std::queue<size_t> queue;
    auto matrix_size = m_adjMatrix.size();

    std::vector<VertexState> nodes(matrix_size, VertexState::Undetected);

    queue.push(0);
    auto vertex_index = 0u;
    while(!queue.empty())
    {
        size_t node = queue.front();

        queue.pop();
        nodes[node] = VertexState::Visited;

        for(size_t j = 0; j < matrix_size; ++j)
        {
            if (m_adjMatrix.at(node).at(j) == 1 && nodes.at(j) == VertexState::Undetected)
            {
                queue.push(j);
                nodes[j] = VertexState::Detected;
            }
        }

        m_graph.insert({(node + 1), m_vertexes.at(vertex_index)});
        ++vertex_index;
    }
}
