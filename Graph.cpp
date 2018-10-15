/*
 * Graph.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: erik
 */

#include "Graph.hpp"

#include <algorithm>
#include <iostream>

#include "Edge.hpp"
#include "Vertex.hpp"

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

Graph::Graph(Environment& env) :
        _env(env)
{
}

bool Graph::addVertex(const Vertex& v)
{
    return _vertices.emplace(&v).second;
}

bool Graph::addEdge(const Edge& e)
{
    return _edges.emplace(&e).second;
}

bool Graph::removeVertex(const Vertex& v)
{
    auto iter = _vertices.find(&v);
    if (iter != _vertices.end())
    {
        _vertices.erase(iter);
        return true;
    }
    return false;
}

bool Graph::removeEdge(const Edge& e)
{
    auto iter = _edges.find(&e);
    if (iter != _edges.end())
    {
        _edges.erase(iter);
        return true;
    }
    return false;
}

const std::set<const Vertex*>& Graph::getVertices() const
{
    return _vertices;
}

const std::set<const Edge*>& Graph::getEdges() const
{
    return _edges;
}

Environment& Graph::getEnv() const
{
    return _env;
}

void Graph::printNodes() const
{
    printContainer(_vertices.cbegin(), _vertices.cend(), ' ');
    std::cout << std::endl;
}

void Graph::printEdges() const
{
    auto printer =
            [] (const Edge* ce)
            {
                Edge* e = const_cast<Edge*>(ce);
                std::cout << e->getFirst().getID() << " " << e->getSecond().getID() << std::endl;
            };
    std::for_each(_edges.cbegin(), _edges.cend(), printer);
}

std::set<const Vertex*>& Graph::getVertices()
{
    return _vertices;
}

std::set<const Edge*>& Graph::getEdges()
{
    return _edges;
}
