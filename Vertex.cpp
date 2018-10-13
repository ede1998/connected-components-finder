/*
 * Vertex.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#include "Vertex.hpp"

#include <algorithm>

#include "Edge.hpp"

bool operator ==(const Vertex& lhs, const Vertex& rhs)
{
    return &lhs == &rhs;
}

std::set<Edge*> Vertex::getIncidentEdges(const Direction d) const
{
    std::set<Edge*> result;
    switch (d)
    {
        case DIR_BOTH:
            return _edges;
        case DIR_INCOMING:
            for (Edge* e : _edges)
                if (e->getSecond() == *this)
                {
                    result.emplace(e);
                }
            break;
        case DIR_OUTGOING:
            for (Edge* e : _edges)
                if (e->getFirst() == *this)
                {
                    result.emplace(e);
                }
            break;
    }
    return result;
}

unsigned int Vertex::getDegree(const Direction d)
{
    auto incCounter = [d, this] (Edge* e) -> bool
    {   return e->getSecond() == *this;};

    auto outCounter = [d, this] (Edge* e) -> bool
    {   return e->getFirst() == *this;};

    switch (d)
    {
        case DIR_BOTH:
            return _edges.size();
        case DIR_INCOMING:
            return std::count_if(_edges.begin(), _edges.end(), incCounter);
        case DIR_OUTGOING:
            return std::count_if(_edges.begin(), _edges.end(), outCounter);
    }
    return 0;
}

std::set<Vertex*> Vertex::getNeighbourhood(const Direction d) const
{
    std::set<Vertex*> nbh;
    for (Edge* e : _edges)
    {
        Vertex& v = e->getAdjacentVertex(*this);
        switch (d)
        {
            case DIR_BOTH:
                nbh.insert(&v);
                break;
            case DIR_INCOMING:
                if (e->getSecond() == *this)
                {
                    nbh.insert(&v);
                }
                break;
            case DIR_OUTGOING:
                if (e->getFirst() == *this)
                {
                    nbh.insert(&v);
                }
                break;
        }
    }
    return nbh;
}

Vertex::Vertex(const vID id, Environment& env) :
        _id(id), _env(env)
{
}

Edge* Vertex::getIncidentEdge(const Vertex& other, const Direction d) const
{
    for (Edge* e : _edges)
    {
        if (e->getAdjacentVertex(*this) == other)
        {
            switch (d)
            {
                case DIR_BOTH:
                    return e;
                case DIR_OUTGOING:
                    if (e->getFirst() == *this)
                    {
                        return e;
                    }
                    break;
                case DIR_INCOMING:
                    if (e->getSecond() == *this)
                    {
                        return e;
                    }
                    break;
            }
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

