#include <iostream>
#include <sstream>
#include <time.h>
#include "BinHeap.h"
#include "Graph.h"
#include <limits.h>

using namespace std;

double PrimMST(Graph* iGraph, int startVertex) {
	double sum = 0.0;
	int numGraphVertices = iGraph->getNumVertices();
	vector<double> dist(numGraphVertices, (double)INT_MAX);
	vector<int> prev(numGraphVertices, -1);
	vector<bool> MSTSet(numGraphVertices, false);
	
	vector<vector<GraphEdge> > graphAdjacencies = iGraph->getAdjacencies();
	dist[startVertex] = 0.0;

	BinHeap<GraphVertex>* heap = new BinHeap<GraphVertex>(numGraphVertices);
	heap->insert(GraphVertex(startVertex, 0.0));

	while (!heap->isEmpty()) 
	{
		GraphVertex v = heap->extractMin();
		int vertexIndex = v.getVertexIndex();
		for (vector<GraphEdge>::size_type edgeIdx = 0; edgeIdx < graphAdjacencies[vertexIndex].size(); edgeIdx++) 
		{
			GraphEdge currentEdge = graphAdjacencies[vertexIndex][edgeIdx];
			int edgeOtherVertex = currentEdge.getEdgeDestVertex();
			if (!(MSTSet[edgeOtherVertex]) &&
				(dist[edgeOtherVertex] - currentEdge.getEdgeWeight()) > EPS) 
			{
				dist[edgeOtherVertex] = currentEdge.getEdgeWeight();
				prev[edgeOtherVertex] = vertexIndex;
				heap->insert(GraphVertex(edgeOtherVertex, dist[edgeOtherVertex]));
			}
		}
		MSTSet[vertexIndex] = true;
	}
	
	for (vector<double>::size_type j = 1; j < (unsigned int)numGraphVertices; j++)
	{
		sum += dist[j];
	}

	return sum;
}

int main(int argc, char** argv) {
	if (argc != 5){
		cout << "Incorrect input args list" << endl;
	}

	srand((unsigned int)time(NULL));
	
	istringstream ss1(argv[2]);
	int numPoints;
	if (!(ss1 >> numPoints))
		cerr << "Invalid number for numPoints" << argv[2] << '\n';

	istringstream ss2(argv[3]);
	int numTrials;
	if (!(ss2 >> numTrials))
		cerr << "Invalid number for numTrials" << argv[3] << '\n';

	istringstream ss3(argv[4]);
	int dimension;
	if (!(ss3 >> dimension))
		cerr << "Invalid number for dimension" << argv[4] << '\n';

	switch (dimension)
	{
	case 0: {
		Graph* G = new Graph(numPoints);
		for (int i = 1; i <= numPoints; i++)
		{
			for (int j = 1; j <= numPoints; j++)
			{
				if (i == j)
					continue;
				double weight = G->getEdgeWeight(i, j);
				if(weight == -1.0)
					weight = ((double)rand() / (RAND_MAX));
				G->addEdge(i, j, weight);
			}
		}
		
		double sum = PrimMST(G, 1);
	}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;

	}

	return 0;
}