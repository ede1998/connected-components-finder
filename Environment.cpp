/*
 * Environment.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "Environment.hpp"

#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

#include "Edge.hpp"
#include "Vertex.hpp"


Environment::Environment()
: _edgesSize(0), _verticesSize(0)
{
}

Environment::Environment(const char* filename) :
        _verticesSize(0), _edgesSize(0)
{
    std::ifstream fs(filename);
    assert(fs.good());

    vID numVertices;
    fs >> numVertices;

    // Add vertices and save temporarily
    std::vector<Vertex*> buffer;
    buffer.reserve(numVertices);
    for (vID i = 0; i < numVertices; ++i)
    {
        buffer.push_back(&addVertex());
    }

    unsigned int left, right;
    while (fs >> left >> right)
    {
        addEdge(*buffer[left], *buffer[right]);
    }
}

Edge& Environment::addEdge(Vertex& v1, Vertex& v2)
{
    assert(std::find(_vertices.begin(), _vertices.end(), v1)
            != _vertices.end());
    assert(std::find(_vertices.begin(), _vertices.end(), v2)
            != _vertices.end());

    _edges.push_front(Edge(_edgesSize, v1, v2, *this));
    ++_edgesSize;

    Edge& e = _edges.front();
    v1.addEdge(e);
    v2.addEdge(e);

    return e;
}

Vertex& Environment::addVertex()
{
    _vertices.push_front(Vertex(_verticesSize, *this));
    ++_verticesSize;
    return _vertices.front();
}

unsigned int Environment::getEdgeSize() const
{
    return _edgesSize;
}

unsigned int Environment::getVertexSize() const
{
    return _verticesSize;
}

Vertex& Environment::getVertex(size_t index)
{
    auto selectID = [index](const Vertex& v) {   return v.getID() == index;};
    auto iter = std::find_if(_vertices.begin(), _vertices.end(), selectID);
    assert(iter != _vertices.end());
    return *iter;
}

Edge& Environment::getEdge(size_t index)
{
    auto selectID = [index](const Edge& v) {   return v.getID() == index;};
    auto iter = std::find_if(_edges.begin(), _edges.end(), selectID);
    assert(iter != _edges.end());
    return *iter;
}

std::set<const Vertex*> Environment::getAllVertices() const
{
    std::set<const Vertex*> s;
    for (const Vertex& v: _vertices)
    {
        s.insert(&v);
    }
    return s;
}

std::set<const Edge*> Environment::getAllEdges() const
{
    std::set<const Edge*> s;
    for (const Edge& e: _edges)
    {
        s.insert(&e);
    }
    return s;
}
