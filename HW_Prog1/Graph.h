#pragma once
#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>

class GraphEdge {
public:
	GraphEdge(int V, double w): mDestVertex(V), mEdgeWeight(w){

	}
	int getEdgeDestVertex() const{ 
		return mDestVertex; 
	}
	double getEdgeWeight() const {
		return mEdgeWeight;
	}
private:
	int mDestVertex;
	double mEdgeWeight;
};

class Graph {
public:
	Graph(int vericesSize):mGraphAdjacencies(vericesSize + 1) {

	}

private:
	std::vector< std::vector<GraphEdge> > mGraphAdjacencies;
};


#endif