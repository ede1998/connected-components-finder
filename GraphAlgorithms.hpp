/*
 * GraphAlgorithms.hpp
 *
 *  Created on: Oct 13, 2018
 *      Author: erik
 */

#ifndef GRAPHALGORITHMS_HPP_
#define GRAPHALGORITHMS_HPP_

#include <vector>

#include "Edge.hpp"
#include "Environment.hpp"
#include "Graph.hpp"
#include "Vertex.hpp"

Graph generateConnectedComponents(const Vertex& v);
std::vector<Graph> findAllConnectedComponents(const Environment& env);

#endif /* GRAPHALGORITHMS_HPP_ */
