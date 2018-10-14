/*
 * Graph.h
 *
 *  Created on: Oct 12, 2018
 *      Author: erik
 */

#ifndef COMBOPTWS2018_GRAPH_H_
#define COMBOPTWS2018_GRAPH_H_

#include <set>

class Vertex;
class Edge;
class Environment;


class Graph
{
    friend class Environment;
public:
    Graph(Environment& env);
    bool addVertex(const Vertex& v);
    bool addEdge(const Edge& e);
    bool removeVertex(const Vertex& v);
    bool removeEdge(const Edge& e);
    const std::set<const Vertex*>& getVertices() const;
    const std::set<const Edge*>& getEdges() const;
    Environment& getEnv() const;
    void printNodes() const;
    void printEdges() const;
private:
    std::set<const Vertex*> _vertices;
    std::set<const Edge*> _edges;
    Environment& _env;
};


#endif /* COMBOPTWS2018_GRAPH_H_ */
