/*
 * Edge.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "Edge.hpp"

#include "Vertex.hpp"

bool operator ==(const Edge& lhs, const Edge& rhs)
{
    return &lhs == &rhs;
}

Vertex& Edge::getAdjacentVertex(const Vertex& other) const
{
    return (*_endpoint.first == other) ? *_endpoint.second : *_endpoint.first;
}

Vertex& Edge::getFirst()
{
    return *_endpoint.first;
}

Vertex& Edge::getSecond()
{
    return *_endpoint.second;
}

eID Edge::getID() const
{
    return _id;
}

Edge::Edge(const eID id, Vertex& first, Vertex& second, Environment& env) :
        _id(id), _env(env)
{
    _endpoint.first = &first;
    _endpoint.second = &second;
}

Environment& Edge::getEnv() const
{
    return _env;
}
