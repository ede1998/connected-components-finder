/*
 * Vertex.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "Vertex.hpp"

#include "Edge.hpp"

bool operator ==(const Vertex& lhs, const Vertex& rhs)
{
    return &lhs == &rhs;
}

const std::set<Edge*>& Vertex::getIncidentEdges() const
{
    return _edges;
}

unsigned int Vertex::getDegree()
{
    return _edges.size();
}

std::set<Vertex*> Vertex::getNeighbourhood() const
{
    std::set<Vertex*> nbh;
    for (Edge* e : getIncidentEdges())
    {
        Vertex& v = e->getAdjacentVertex(*this);
        nbh.insert(&v);
    }
    return nbh;
}

Vertex::Vertex(const vID id, Environment& env) :
        _id(id), _env(env)
{
}

Edge* Vertex::getIncidentEdge(const Vertex& other) const
{
    for (Edge* e : _edges)
    {
        if (e->getAdjacentVertex(*this) == other)
        {
            return e;
        }
    }
    return nullptr;
}

vID Vertex::getID() const
{
    return _id;
}

bool Vertex::addEdge(Edge& e)
{
    return _edges.emplace(&e).second;
}

Environment& Vertex::getEnv() const
{
    return _env;
}

