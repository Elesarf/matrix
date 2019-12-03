#include <iostream>
#include <string>
#include <queue>
#include <tuple>
#include <fstream>
#include <exception>

static const std::string c_matrix_entity("Matrix:");
static const std::string c_vertex_entity("Vertex:");

enum class VertexState
{
    Undetected = 0,
    Detected,
    Visited
};

std::tuple<std::vector<std::vector<int>>, std::vector<std::string>> load_file()
{
    std::ifstream file("./input.txt");
    if (!file.is_open())
        throw std::runtime_error("file not open");

    std::string now_string;
    std::getline(file, now_string);

    if (now_string != c_matrix_entity)
        throw std::runtime_error("not correct file");

    std::getline(file, now_string);

    auto matrix_size = now_string.length();
    std::cout << "Matrix dimension: " << matrix_size
              << "x" << matrix_size
              << std::endl;

    std::vector<std::vector<int>> adj_matrix(matrix_size, std::vector<int>(matrix_size, 0));

    for (auto &v:adj_matrix)
    {
        for (size_t i = 0; i < now_string.length(); ++i)
        {
            v[i] = std::stoi(now_string.substr(i, 1));
        }

        std::getline(file, now_string);

        if (!file.good())
            throw std::runtime_error("not correct file");

        if (now_string == c_vertex_entity)
            break;
    }

    std::vector<std::string> vertexes(matrix_size);

    for (auto &v:vertexes)
    {
        std::getline(file, now_string);

        v = now_string;

        if (!file.good())
            throw std::runtime_error("not correct file");
    }

    return std::tuple<std::vector<std::vector<int>>, std::vector<std::string>>
    {std::move(adj_matrix), std::move(vertexes)};
}

int main()
{
    auto file_result = load_file();
    auto adj_matrix = std::get<0>(file_result);
    auto vertexes = std::get<1>(file_result);

    std::cout << "Your matrix:" << std::endl;
    for (const auto &v:adj_matrix)
    {
        for(const auto &ve:v)
            std::cout << ve << " ";
        std::cout << std::endl;
    }

    std::cout << "Your vertexes:" << std::endl;
    for (const auto &v:vertexes)
    {
        std::cout << v << std::endl;
    }

    std::queue<size_t> queue;
    auto matrix_size = adj_matrix.size();

    std::vector<VertexState> nodes(matrix_size, VertexState::Undetected);

    queue.push(0);
    while(!queue.empty())
    {
        size_t node = queue.front();

        queue.pop();
        nodes[node] = VertexState::Visited;

        for(size_t j = 0; j < matrix_size; ++j)
        {
            if (adj_matrix.at(node).at(j) == 1 && nodes.at(j) == VertexState::Undetected)
            {
                queue.push(j);
                nodes[j] = VertexState::Detected;
            }
        }
        std::cout << "vert " << vertexes.at(node) << std::endl;
    }

    return 0;
}
