/*
 * GraphAlgorithms.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "GraphAlgorithms.hpp"

#include <set>
#include <algorithm>

#include "Environment.hpp"

Graph generateConnectedComponents(const Vertex& v)
{
    std::set<const Vertex*> connectedVertices, remainingVertices;
    std::set<const Edge*> connectedEdges;


    // Initialize buffers
    connectedVertices.insert(&v);
    remainingVertices.insert(&v);

    // main loop
    while (!remainingVertices.empty())
    {
        const Vertex* v = *remainingVertices.begin();
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

    // build resulting subgraph
    Graph g(v.getEnv());
    for (const auto* constV: connectedVertices)
    {
        g.addVertex(*const_cast<Vertex*>(constV));
    }
    for (const auto* constE: connectedEdges)
    {
        g.addEdge(*const_cast<Edge*>(constE));
    }

    return g;
}
