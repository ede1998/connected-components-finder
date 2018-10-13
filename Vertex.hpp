/*
 * Vertex.hpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#ifndef VERTEX_HPP_
#define VERTEX_HPP_

#include <set>

using vID = unsigned int;

class Edge;
class Environment;
class Graph;

class Vertex
{
    friend class Environment;
public:
   const std::set<Edge*>& getIncidentEdges() const;
   unsigned int getDegree();
   std::set<Vertex*> getNeighbourhood() const;
   Edge* getIncidentEdge(const Vertex& other) const;
   vID getID() const;
   Environment& getEnv() const;
private:
    explicit Vertex(const vID id, Environment& g);
    bool addEdge(Edge& e);

    std::set<Edge*> _edges;
    Environment& _env;
    const vID _id;
};

bool operator==(const Vertex& lhs, const Vertex& rhs);

#endif /* VERTEX_HPP_ */