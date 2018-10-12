/*
 * Graph.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: erik
 */

#include "Graph.hpp"

#include <fstream>
#include <cassert>
#include <algorithm>
#include <iterator>

Environment::Environment(const char* filename)
{
    std::ifstream fs(filename);
    assert(fs.good());

    const eID numEdges = std::count(std::istream_iterator<char>(fs),
                                    std::istream_iterator<char>(),
                                    ' ');
    fs.clear();
    fs.seekg(0, fs.beg);
    // neccessary to prevent _edges from reallocating which would invalidate
    // all references in the vertex classes
    _edges.reserve(numEdges);

    vID numVertices;
    fs >> numVertices;

    // neccessary to prevent _vertices from reallocating which would invalidate
    // all references in the vertex classes and edges classes
    _vertices.reserve(numVertices);
    // Add vertices and save temporarily
    for (vID i = 0; i < numVertices; ++i)
    {
        addVertex();
    }

    unsigned int left, right;
    while (fs >> left >> right)
    {
        addEdge(_vertices[left], _vertices[right]);
    }
}

bool Vertex::operator ==(const Vertex& other)
{
    return this == &other;
}

const std::set<Edge*>& Vertex::getIncidentEdges()
{
    return _edges;
}

unsigned int Vertex::getDegree()
{
    return _edges.size();
}

std::set<Vertex*> Vertex::getNeighbourhood()
{
    std::set<Vertex*> nbh;
    for (auto e : getIncidentEdges())
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

bool Edge::operator ==(const Edge& other)
{
    return this == &other;
}

Vertex& Edge::getAdjacentVertex(const Vertex& other)
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

Edge::Edge(const eID id, Vertex& first, Vertex& second, Environment& env) :
        _id(id), _env(env)
{
    _endpoint.first = &first;
    _endpoint.second = &second;
}

Edge& Environment::addEdge(Vertex& v1, Vertex& v2)
{
    assert(!_vertices.empty());
    assert(_vertices.data() <= &v1 && &v1 < _vertices.data() + _vertices.size());
    assert(_vertices.data() <= &v2 && &v2 < _vertices.data() + _vertices.size());

    _edges.push_back(Edge(_edges.size(), v1, v2, *this));

    Edge& e = _edges.back();
    v1.addEdge(e);
    v2.addEdge(e);

    return e;
}

Vertex& Environment::addVertex()
{
    _vertices.push_back(Vertex(_vertices.size(), *this));
    return _vertices.back();
}

unsigned int Environment::getEdgeSize()
{
    return _edges.size();
}

unsigned int Environment::getVertexSize()
{
    return _vertices.size();
}

bool Vertex::addEdge(Edge& e)
{
    return _edges.emplace(&e).second;
}
