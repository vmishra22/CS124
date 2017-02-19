#pragma once
#ifndef _GRAPH_
#define _GRAPH_

#include <iostream>
#include <vector>

class GraphVertex {
public:
	GraphVertex(int v, double d) : vertexIndex(v), vertexDist(d) {
	}
	friend bool operator < (GraphVertex const& lhs, GraphVertex const& rhs);
	friend bool operator > (GraphVertex const& lhs, GraphVertex const& rhs);
	GraphVertex& operator= (const GraphVertex &rhs);
	int getVertexIndex() const { return vertexIndex; }
	double getVertexDist() const { return vertexDist; }
private:
	int vertexIndex;
	double vertexDist;
};

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

	void addEdge(const int& iStartVertex, const int& iEndVertex, double weight){
		mGraphAdjacencies[iStartVertex].push_back(GraphEdge(iEndVertex, weight));
	}

	std::vector< std::vector<GraphEdge> >&  getAdjacencies() {
		return mGraphAdjacencies;
	}

	unsigned int getNumVertices() const {
		return mGraphAdjacencies.size();
	}
private:
	std::vector< std::vector<GraphEdge> > mGraphAdjacencies;
};


#endif