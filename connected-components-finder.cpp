#include <iostream>
#include <graph.hpp>
#include <set>
#include <algorithm>
#include <cassert>

using namespace DHBW;

std::set<VertexId> makeNeighbourhood(VertexId v,
                                           const Graph& g);
EdgeId getConnectingEdge(VertexId v1,
                     VertexId v2,
                     const Graph& g);

void printStats(const Graph& g)
{
    std::cout << "Number of vertices: " << g.num_vertices() << std::endl;
    std::cout << "Number of edges: " << g.num_edges() << std::endl;
}

template<class Iterator>
void printContainer(Iterator first, Iterator last, char delim)
{
    if (first != last)
    {
        std::cout << *first++;
    }

    for (Iterator iter = first; iter != last; ++iter)
    {
        std::cout << delim << *iter;
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
    Graph graph = Graph(argv[1], GraphInputFormat::plain);
    std::set<VertexId> connectedVertices, remainingVertices;
    std::set<EdgeId> connectedEdges;

    printStats(graph);

    // Initialize buffers
    connectedVertices.insert(0);
    remainingVertices.insert(0);

    // main loop
    while (!remainingVertices.empty())
    {
        VertexId v = *remainingVertices.begin();
        auto vertexV = graph.vertex(v);
        remainingVertices.erase(remainingVertices.begin());

        // find all neighbours that are not in R
        std::set<VertexId> remNeighbourhood;
        auto neighbourhood = makeNeighbourhood(v, graph);
        std::set_difference(neighbourhood.begin(),
                            neighbourhood.end(),
                            connectedVertices.begin(),
                            connectedVertices.end(),
                            std::inserter(remNeighbourhood,
                                          remNeighbourhood.begin()));

        // loop over them
        while (!remNeighbourhood.empty())
        {
            VertexId w = *remNeighbourhood.begin();
            remNeighbourhood.erase(remNeighbourhood.begin());

            connectedVertices.insert(w);
            remainingVertices.insert(w);
            connectedEdges.insert(getConnectingEdge(v,w, graph));
        }
    }


    printContainer(connectedVertices.begin(), connectedVertices.end(), ' ');
    std::cout << std::endl;

    return 0;
}

std::set<VertexId> makeNeighbourhood(VertexId v,
                                           const Graph& g)
{
    std::set<VertexId> nbh;
    auto vertexV = g.vertex(v);

    for (size_t i = 0; i < vertexV.num_edges(); ++i)
    {
        const Edge& e = g.edge(vertexV.edge(i));
        VertexId other = e.other_vertex(v);
        nbh.insert(other);
    }

    return nbh;
}

EdgeId getConnectingEdge(VertexId v1, VertexId v2, const Graph& g)
{
    auto vertexV1 = g.vertex(v1);
    auto vertexV2 = g.vertex(v2);

    for (size_t i = 0; i < vertexV1.num_edges(); ++i)
    {
        const EdgeId e = vertexV1.edge(i);
        const Edge& edgeE = g.edge(e);
        if (edgeE.other_vertex(v1) == v2)
        {
            return e;
        }
    }
    assert(false);
    return 0;
}
