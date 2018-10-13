/*
 * Edge.hpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#ifndef EDGE_HPP_
#define EDGE_HPP_

#include <utility>

using eID = unsigned int;

class Environment;
class Graph;
class Vertex;

class Edge
{
    friend class Environment;
public:
   Vertex& getAdjacentVertex(const Vertex& other) const;
   Vertex& getFirst();
   Vertex& getSecond();
   eID getID() const;
   Environment& getEnv() const;
private:
    explicit Edge(const eID id, Vertex& first, Vertex& second, Environment& g);

    std::pair<Vertex*, Vertex*> _endpoint;
    Environment& _env;
    const eID _id;
};

bool operator==(const Edge& lhs, const Edge& rhs);

#endif /* EDGE_HPP_ */
