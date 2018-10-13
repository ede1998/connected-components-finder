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
    bool addVertex(Vertex& v);
    bool addEdge(Edge& e);
    bool removeVertex(Vertex& v);
    bool removeEdge(Edge& e);
    const std::set<Vertex*>& getVertices() const;
    const std::set<Edge*>& getEdges() const;
    Environment& getEnv() const;
private:
    std::set<Vertex*> _vertices;
    std::set<Edge*> _edges;
    Environment& _env;
};


#endif /* COMBOPTWS2018_GRAPH_H_ */
