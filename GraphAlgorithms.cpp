/*
 * GraphAlgorithms.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "GraphAlgorithms.hpp"

#include <algorithm>
#include <cassert>
#include <map>
#include <set>

Graph generateConnectedComponents(const Vertex& v, const Direction d)
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

        // find all neighbors that are not in already connected
        std::set<Vertex*> remNeighbourhood;
        auto neighbourhood(std::move(v->getNeighbourhood(d)));
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

            const Edge* e = v->getIncidentEdge(*w, d);
            assert(e);
            connectedEdges.insert(e);
        }
    }

    // build resulting subgraph
    Graph g(v.getEnv());
    for (const auto* constV : connectedVertices)
    {
        g.addVertex(*const_cast<Vertex*>(constV));
    }
    for (const auto* constE : connectedEdges)
    {
        g.addEdge(*const_cast<Edge*>(constE));
    }

    return g;
}

std::vector<Graph> findAllConnectedComponents(const Environment& env)
{
    std::vector<Graph> result;
    std::set<const Vertex*> unvisitedVertices(std::move(env.getAllVertices()));

    while (!unvisitedVertices.empty())
    {
        const Vertex* v = *unvisitedVertices.begin();

        result.emplace_back(generateConnectedComponents(*v));

        const std::set<const Vertex*>& currentVertices = result.back().getVertices();

        // remove connected vertices from unvisitedVertices
        std::set<const Vertex*> tmp;
        auto beg = std::make_move_iterator(unvisitedVertices.begin());
        auto end = std::make_move_iterator(unvisitedVertices.end());
        std::set_difference(beg,
                            end,
                            currentVertices.begin(),
                            currentVertices.end(),
                            std::inserter(tmp, tmp.begin()));
        unvisitedVertices.swap(tmp);
    }

    return result;
}

std::vector<Graph> findAllStronglyConnectedComponents(const Environment& env)
{
    std::set<const Vertex*> all(std::move(env.getAllVertices()));
    std::map<const Vertex*, std::set<Vertex*>> table;

    std::for_each(all.begin(),
                  all.end(),
                  [&table](const Vertex* v)
                  {   auto iter = table.emplace(v, std::move(v->getNeighbourhood(DIR_OUTGOING))).first;
                      iter->second.emplace(const_cast<Vertex*>(v));
                  });

    // warshall algorithm to find all connected nodes for each node
    bool changed;
    do
    {
        changed = false;
        for (auto& pair : table)
        {
            auto& s = pair.second;
            // add neighborhood of all neighbors
            std::for_each(s.begin(), s.end(), [&s, &table, &changed] (Vertex* v)
            {
                const auto& set2 = table.find(v)->second;
                const size_t prevSize = s.size();
                s.insert(set2.begin(), set2.end());
                changed |= s.size() != prevSize;
            });

        }
    } while (changed);

    // find all strongly connected components
    auto& remainingVertices = all;
    std::vector<Graph> components;

    while (!remainingVertices.empty())
    {
        components.emplace_back(const_cast<Environment&>(env));
        auto& current = components.back();
        current.addVertex(**remainingVertices.begin());

        for (const Vertex* v: current.getVertices())
        {
            auto vIter = table.find(v);
            // assert(vIter != table.end());
            // for each v-w-path find a corresponding w-v-path
            for (const Vertex* w: vIter->second)
            {
                auto wIter = table.find(w);
                // assert(wIter != table.end();
                if (wIter->second.find(const_cast<Vertex*>(v)) != wIter->second.end())
                {
                    current.addEdge(*v->getIncidentEdge(*w, DIR_INCOMING));
                    current.addEdge(*v->getIncidentEdge(*w, DIR_OUTGOING));
                    current.addVertex(*w);
                }
            }
        }

        // remove connected vertices from unvisitedVertices
        std::set<const Vertex*> tmp;
        auto beg = std::make_move_iterator(remainingVertices.begin());
        auto end = std::make_move_iterator(remainingVertices.end());
        std::set_difference(beg,
                            end,
                            current.getVertices().begin(),
                            current.getVertices().end(),
                            std::inserter(tmp, tmp.begin()));
        remainingVertices.swap(tmp);
    }

    return components;

}

std::vector<Graph> findAllStronglyConnectedComponentsFast(const Environment& env)
{
    std::vector<Graph> result;
    std::set<const Vertex*> unvisitedVertices(std::move(env.getAllVertices()));

    while (!unvisitedVertices.empty())
    {
        const Vertex* v = *unvisitedVertices.begin();

        // find all w-v-paths
        std::set<const Vertex*> incoming(
                std::move(generateConnectedComponents(*v, DIR_INCOMING).getVertices()));
        // find all v-w-paths
        std::set<const Vertex*> outgoing(
                std::move(generateConnectedComponents(*v, DIR_OUTGOING).getVertices()));

        // find all vertices w with v-w-path and w-v-path by intersection
        // of the two sets => strongly connected
        result.emplace_back(const_cast<Environment&>(env));
        std::set<const Vertex*>& currentComponent = result.back().getVertices();
        {
            auto beg = std::make_move_iterator(incoming.begin());
            auto end = std::make_move_iterator(incoming.end());
            std::set_intersection(beg,
                                  end,
                                  outgoing.begin(),
                                  outgoing.end(),
                                  std::inserter(currentComponent,
                                                currentComponent.begin()));
        }

        // remove connected vertices from unvisitedVertices
        {
            std::set<const Vertex*> tmp;
            auto beg = std::make_move_iterator(unvisitedVertices.begin());
            auto end = std::make_move_iterator(unvisitedVertices.end());
            std::set_difference(beg,
                                end,
                                currentComponent.begin(),
                                currentComponent.end(),
                                std::inserter(tmp, tmp.begin()));
            unvisitedVertices.swap(tmp);
        }
    }

    return result;
}
