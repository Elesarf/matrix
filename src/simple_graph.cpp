#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <list>

#include "simple_graph.h"

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

static bool allChecked(const std::vector<VertexState> vec)
{
    for (const auto &v:vec)
        if (v != VertexState::Processed)
            return false;
    return true;
}

void simple_graph::calculateGraph()
{
    auto vertex_count = m_adjMatrix.size();
    std::vector<VertexState> nodes(vertex_count, VertexState::NotProcessed);
    std::stack<size_t> stack;
    auto vertex_index = 0u;

    while (!allChecked(nodes)) {

        auto now_index = 0u;

        for (const auto &v:nodes){
            if (v == VertexState::NotProcessed)
                break;

            ++now_index;
        }

        if (now_index == vertex_count)
            break;

        // insert root vertex index in to stack
        stack.push(now_index);

        while(!stack.empty())
        {
            auto now_node = stack.top();
            nodes[now_node] = VertexState::Processed;
            stack.pop();

            for(size_t j = 0; j < vertex_count; ++j)
            {
                if (m_adjMatrix.at(now_node).at(j) == 1 && nodes.at(j) == VertexState::NotProcessed)
                {
                    stack.push(j);
                    break;
                }
            }

            m_graph.insert({(now_node + 1), m_vertexes.at(vertex_index)});
            ++vertex_index;
        }
    }
}
