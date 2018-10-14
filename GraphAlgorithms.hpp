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
#include "Direction.hpp"

Graph generateConnectedComponents(const Vertex& v, const Direction d = DIR_BOTH);
std::vector<Graph> findAllConnectedComponents(const Environment& env);
std::vector<Graph> findAllStronglyConnectedComponents(const Environment& env);

#endif /* GRAPHALGORITHMS_HPP_ */
