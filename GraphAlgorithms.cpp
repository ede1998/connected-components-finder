/*
 * GraphAlgorithms.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "GraphAlgorithms.hpp"

#include <cassert>
#include <set>
#include <algorithm>

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

        // find all neighbours that are not in already connected
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

            const Edge* e = v->getIncidentEdge(*w);
            assert(e);
            connectedEdges.insert(e);
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

std::vector<Graph> findAllConnectedComponents(const Environment& env)
{
    std::vector<Graph> result;
    std::set<const Vertex*> unvisitedVertices = env.getAllVertices();

    while (!unvisitedVertices.empty())
    {
        const Vertex* v = *unvisitedVertices.begin();

        result.emplace_back(generateConnectedComponents(*v));

        const std::set<Vertex*>& currentVertices = result.back().getVertices();

        // remove connected vertices from unvisitedVertices
        std::set<const Vertex*> tmp;
        auto beg = std::make_move_iterator(unvisitedVertices.begin());
        auto end = std::make_move_iterator(unvisitedVertices.end());
        std::set_difference(beg, end, currentVertices.begin(), currentVertices.end(), std::inserter(tmp, tmp.begin()));
        unvisitedVertices.swap(tmp);
    }

    return result;
}
