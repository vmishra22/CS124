#include <iostream>
#include <sstream>
#include <time.h>
#include "Graph.h"
#include "BinHeap.h"
#include <limits.h>

using namespace std;

static void PrimMST(Graph* iGraph, int startVertex) {
	int numGraphVertices = iGraph->getNumVertices();
	vector<int> dist(numGraphVertices);
	vector<int> prev(numGraphVertices);
	
	vector<vector<GraphEdge> > graphAdjacencies = iGraph->getAdjacencies();
	for (vector<vector<GraphEdge> >::size_type idx = 1; idx <= iGraph->getNumVertices(); idx++) {
		dist[idx] = INT_MAX;
		prev[idx] = -1;
	}
	dist[1] = 0;

	BinHeap<GraphVertex>* heap = new BinHeap<GraphVertex>(numGraphVertices);
	heap->insert(GraphVertex(1, 0));
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
		for (int i = 1; i < numPoints; i++) {
			for (int j = i+1; j <= numPoints; j++) {
				double weight = ((double)rand() / (RAND_MAX));
				G->addEdge(i, j, weight);
			}
		}

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