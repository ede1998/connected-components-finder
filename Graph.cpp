/*
 * Graph.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: erik
 */

#include "Graph.hpp"

Graph::Graph(Environment& env)
: _env(env)
{
}

bool Graph::addVertex(Vertex& v)
{
    return _vertices.emplace(&v).second;
}

bool Graph::addEdge(Edge& e)
{
    return _edges.emplace(&e).second;
}

bool Graph::removeVertex(Vertex& v)
{
    auto iter = _vertices.find(&v);
    if (iter != _vertices.end())
    {
        _vertices.erase(iter);
        return true;
    }
    return false;
}

bool Graph::removeEdge(Edge& e)
{
    auto iter = _edges.find(&e);
    if (iter != _edges.end())
    {
        _edges.erase(iter);
        return true;
    }
    return false;
}

const std::set<Vertex*>& Graph::getVertices() const
{
    return _vertices;
}

const std::set<Edge*>& Graph::getEdges() const
{
    return _edges;
}

Environment& Graph::getEnv() const
{
    return _env;
}
