#include "Graph.h"
#include "math.h"

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
