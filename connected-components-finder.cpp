#include <iostream>
#include "Graph.hpp"
#include <set>
#include <algorithm>
#include <cassert>

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
    std::set<Vertex*> connectedVertices, remainingVertices;
    std::set<Edge*> connectedEdges;

    printStats(env);

    // Initialize buffers
    connectedVertices.insert(&env.getVertex(0));
    remainingVertices.insert(&env.getVertex(0));

    // main loop
    while (!remainingVertices.empty())
    {
        Vertex* v = *remainingVertices.begin();
        remainingVertices.erase(remainingVertices.begin());

        // find all neighbours that are not in R
        std::set<Vertex*> remNeighbourhood;
        auto neighbourhood = v->getNeighbourhood();
        std::set_difference(neighbourhood.begin(),
                            neighbourhood.end(),
                            connectedVertices.begin(),
                            connectedVertices.end(),
                            std::inserter(remNeighbourhood,
                                          remNeighbourhood.begin()));

        // loop over them
        while (!remNeighbourhood.empty())
        {
            Vertex* w = *remNeighbourhood.begin();
            remNeighbourhood.erase(remNeighbourhood.begin());

            connectedVertices.insert(w);
            remainingVertices.insert(w);
            connectedEdges.insert(v->getIncidentEdge(*w));
        }
    }


    printContainer(connectedVertices.begin(), connectedVertices.end(), ' ');
    std::cout << std::endl;

    return 0;
}
