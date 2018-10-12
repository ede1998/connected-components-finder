/*
 * Graph.h
 *
 *  Created on: Oct 12, 2018
 *      Author: erik
 */

#ifndef COMBOPTWS2018_GRAPH_H_
#define COMBOPTWS2018_GRAPH_H_

#include <set>
#include <vector>
#include <utility>
#include <cstddef>
#include <optional>

using vID = unsigned int;
using eID = unsigned int;

class Vertex;
class Edge;
class Environment;
class Graph;

class Vertex
{
    friend class Environment;
public:
   bool operator==(const Vertex& other);
   const std::set<Edge*>& getIncidentEdges();
   unsigned int getDegree();
   std::set<Vertex*> getNeighbourhood();
   Edge* getIncidentEdge(const Vertex& other);
   vID getID();
private:
    explicit Vertex(const vID id, Environment& g);
    bool addEdge(Edge& e);

    std::set<Edge*> _edges;
    Environment& _env;
    const vID _id;
};

class Edge
{
    friend class Environment;
public:
   bool operator==(const Edge& other);
   Vertex& getAdjacentVertex(const Vertex& other);
   Vertex& getFirst();
   Vertex& getSecond();
   eID getID();
private:
    explicit Edge(const eID id, Vertex& first, Vertex& second, Environment& g);

    std::pair<Vertex*, Vertex*> _endpoint;
    Environment& _env;
    const eID _id;
};

class Graph
{
    friend class Environment;
public:
private:
};

class Environment
{
public:
    Environment() = default;
    Environment(const char* file);
    Edge& addEdge(Vertex& v1, Vertex& v2);
    Vertex& addVertex();

    unsigned int getEdgeSize() const;
    unsigned int getVertexSize() const;

    Vertex& getVertex(size_t index);
    Edge& getEdge(size_t index);
private:
    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};

#endif /* COMBOPTWS2018_GRAPH_H_ */
