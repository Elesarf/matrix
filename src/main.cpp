#include "simple_graph.h"

int main()
{
    simple_graph gr("graph.txt");
    gr.printUserData();
    gr.calculateGraph();
    gr.printGraph();

    return 0;
}
