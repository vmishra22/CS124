#include <iostream>
#include <sstream>
#include <time.h>
#include "BinHeap.h"
#include "Graph.h"
#include <limits.h>
#include <fstream>
#include <cstdlib>
#include <cmath>

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
	GraphVertex s(startVertex, 0.0);
	heap->insert(s);

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
				GraphVertex other(edgeOtherVertex, dist[edgeOtherVertex]);
				heap->insert(other);
			}
		}
		MSTSet[vertexIndex] = true;
	}

	if (heap != NULL)
		delete(heap);
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

	
	ofstream output_file("data_output.txt", std::ofstream::app);
	if (!output_file.is_open()) { 
		cout << "Output file could not be opened! Terminating!" << endl;
		return 1;
	}

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
	case 0: 
	{
		int trialIndex = 0;
		double sumMST = 0.0;
		while(trialIndex < numTrials) {
			srand((unsigned int)time(NULL));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i <= numPoints; i++)
				{
					for (int j = 1; j <= numPoints; j++)
					{
						if (i == j)
							continue;
						double weight = G->getEdgeWeight(i, j);
						if (weight == -1.0)
							weight = ((double)rand() / (RAND_MAX));
						G->addEdge(i, j, weight);
					}
				}

				sumMST += PrimMST(G, 1);
				delete(G);
			}
			trialIndex++;
		}
		if (numTrials > 0) {
			output_file << "n: " << numPoints << " Average: " << (sumMST / numTrials)
				<< " NumTrials: " << numTrials << " dimension: " << dimension << endl;
		}
	}
		break;
	case 2: 
	{
		int trialIndex = 0;
		double sumMST = 0.0;
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i <= numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					for (int j = 1; j <= numPoints; j++)
					{
						if (i == j)
							continue;
						double weight = G->getEdgeWeight(i, j);
						if (weight == -1.0)
						{
							double jX = ((double)rand() / (RAND_MAX));
							double jY = ((double)rand() / (RAND_MAX));
							weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2));
						}
						/*if (weight < 0.05)*/
						G->addEdge(i, j, weight);
					}
				}

				sumMST += PrimMST(G, 1);
				delete(G);
			}
			trialIndex++;
		}
		if (numTrials > 0) {
			output_file << "n: " << numPoints << " Average: " << (sumMST / numTrials)
				<< " NumTrials: " << numTrials << " dimension: " << dimension << endl;
		}
	}
		break;
	case 3:
	{
		int trialIndex = 0;
		double sumMST = 0.0;
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i <= numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					double iZ = ((double)rand() / (RAND_MAX));
					for (int j = 1; j <= numPoints; j++)
					{
						if (i == j)
							continue;
						double weight = G->getEdgeWeight(i, j);
						if (weight == -1.0)
						{
							double jX = ((double)rand() / (RAND_MAX));
							double jY = ((double)rand() / (RAND_MAX));
							double jZ = ((double)rand() / (RAND_MAX));
							weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2) + pow((iZ - jZ), 2));
						}
						/*if (weight < 0.05)*/
						G->addEdge(i, j, weight);
					}
				}

				sumMST += PrimMST(G, 1);
				delete(G);
			}
			trialIndex++;
		}
		if (numTrials > 0) {
			output_file << "n: " << numPoints << " Average: " << (sumMST / numTrials)
				<< " NumTrials: " << numTrials << " dimension: " << dimension << endl;
		}
	}
		break;
	case 4:
	{
		int trialIndex = 0;
		double sumMST = 0.0;
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i <= numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					double iZ = ((double)rand() / (RAND_MAX));
					double iW = ((double)rand() / (RAND_MAX));
					for (int j = 1; j <= numPoints; j++)
					{
						if (i == j)
							continue;
						double weight = G->getEdgeWeight(i, j);
						if (weight == -1.0)
						{
							double jX = ((double)rand() / (RAND_MAX));
							double jY = ((double)rand() / (RAND_MAX));
							double jZ = ((double)rand() / (RAND_MAX));
							double jW = ((double)rand() / (RAND_MAX));
							weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2) + pow((iZ - jZ), 2) + pow((iW - jW), 2));
						}
						/*if (weight < 0.05)*/
						G->addEdge(i, j, weight);
					}
				}

				sumMST += PrimMST(G, 1);
				delete(G);
			}
			trialIndex++;
		}
		if (numTrials > 0) {
			output_file << "n: " << numPoints << " Average: " << (sumMST / numTrials)
				<< " NumTrials: " << numTrials << " dimension: " << dimension << endl;
		}
	}
		break;
	default:
		break;

	}

	output_file.close();

	return 0;
}