#include <iostream>

#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "Environment.hpp"

void printStats(const Environment& env)
{
    std::cout << "Number of vertices: " << env.getVertexSize() << std::endl;
    std::cout << "Number of edges: " << env.getEdgeSize() << std::endl;
}

template<class Iterator>
void printContainer(Iterator first, Iterator last, char delim)
{
    if (first != last)
    {
        std::cout << (*first)->getID();
    }

    for (Iterator iter = ++first; iter != last; ++iter)
    {
        std::cout << delim << (*iter)->getID();
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Program needs a file with graph to operate on."
                << std::endl;
        return 0;
    }
    Environment env = Environment(argv[1]);

    printStats(env);

    Graph g = generateConnectedComponents(env.getVertex(0));

    printContainer(g.getVertices().cbegin(), g.getVertices().cend(), ' ');
    std::cout << std::endl;

    return 0;
}
