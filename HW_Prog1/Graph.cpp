#include "Graph.h"
#include "math.h"

bool operator<(GraphVertex const & lhs, GraphVertex const & rhs)
{
	return (lhs.vertexDist-rhs.vertexDist < 1.0e-09);
}

bool operator>(GraphVertex const & lhs, GraphVertex const & rhs)
{
	return (lhs.vertexDist - rhs.vertexDist > 1.0e-09);
}

GraphVertex & GraphVertex::operator=(const GraphVertex & rhs)
{
	if (this == &rhs)
		return *this;
	vertexDist = rhs.vertexDist;
	vertexIndex = rhs.vertexIndex;

	return *this;
}
