#include "Graph.h"
#include <vector>
#include "math.h"

using namespace std;

bool operator<(GraphVertex const & lhs, GraphVertex const & rhs)
{
	return (lhs.vertexDist-rhs.vertexDist < EPS);
}

bool operator>(GraphVertex const & lhs, GraphVertex const & rhs)
{
	return (lhs.vertexDist - rhs.vertexDist > EPS);
}

GraphVertex & GraphVertex::operator=(const GraphVertex & rhs)
{
	if (this == &rhs)
		return *this;
	vertexDist = rhs.vertexDist;
	vertexIndex = rhs.vertexIndex;

	return *this;
}

double Graph::getEdgeWeight(const int& iStartVertex, const int& iEndVertex) {
	for (vector<GraphEdge>::size_type edgeIdx = 0; edgeIdx < mGraphAdjacencies[iEndVertex].size(); edgeIdx++)
	{
		GraphEdge currentEdge = mGraphAdjacencies[iEndVertex][edgeIdx];
		if (currentEdge.getEdgeDestVertex() == iStartVertex)
			return currentEdge.getEdgeWeight();
	}
	return -1;
}