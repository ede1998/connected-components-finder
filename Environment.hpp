/*
 * Environment.hpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#ifndef ENVIRONMENT_HPP_
#define ENVIRONMENT_HPP_

#include <forward_list>
#include <set>

using eID = unsigned int;
using vID = unsigned int;

class Edge;
class Graph;
class Vertex;

class Environment
{
public:
    Environment();
    Environment(const char* file);
    Edge& addEdge(Vertex& v1, Vertex& v2);
    Vertex& addVertex();

    unsigned int getEdgeSize() const;
    unsigned int getVertexSize() const;

    Vertex& getVertex(size_t index);
    Edge& getEdge(size_t index);

    std::set<const Vertex*> getAllVertices() const;
    std::set<const Edge*> getAllEdges() const;
private:
    std::forward_list<Vertex> _vertices;
    std::forward_list<Edge> _edges;

    vID _verticesSize;
    eID _edgesSize;
};

#endif /* ENVIRONMENT_HPP_ */
