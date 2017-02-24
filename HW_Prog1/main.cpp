#include <iostream>
#include <sstream>
#include <time.h>
#include "BinHeap.h"
#include "Graph.h"
#include <limits.h>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>

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

	double cUpper = *(max_element(dist.begin()+1, dist.end()));
	cout << "n: "<< numGraphVertices-1<< "Max Weight: " << cUpper << endl;
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
		double maxWeight = 1.1;
		if(numPoints >= 100 && numPoints <1000) maxWeight = 0.1;
		else if (numPoints >= 1000 && numPoints <2000) maxWeight = 0.008;
		else if (numPoints >= 2000 && numPoints <4000) maxWeight = 0.006;
		else if (numPoints >= 4000 && numPoints <8000) maxWeight = 0.004;
		else if (numPoints >= 8000 && numPoints <16000) maxWeight = 0.003;
		else if (numPoints >= 16000 && numPoints <32000) maxWeight = 0.001;
		else if (numPoints >= 32000 && numPoints <64000) maxWeight = 0.0007;
		else if (numPoints >= 64000 && numPoints <128000) maxWeight = 0.0003;
		else if (numPoints >= 128000) maxWeight = 0.00015;
		while(trialIndex < numTrials) {
			srand((unsigned int)time(NULL));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i < numPoints; i++)
				{
					for (int j = i+1; j <= numPoints; j++)
					{
						double weight = ((double)rand() / (RAND_MAX));
						if (weight - maxWeight < EPS) {
							cout << "i: " << i << " j: " << j << endl;
							G->addEdge(i, j, weight);
							G->addEdge(j, i, weight);
						}
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
		double maxWeight = 2.0;
		if (numPoints >= 100 && numPoints<1000) maxWeight = 0.20;
		else if (numPoints >= 1000 && numPoints<2000) maxWeight = 0.10;
		else if (numPoints >= 2000 && numPoints<4000) maxWeight = 0.06;
		else if (numPoints >= 4000 && numPoints<8000) maxWeight = 0.04;
		else if (numPoints >= 8000 && numPoints<16000) maxWeight = 0.03;
		else if (numPoints >= 16000 && numPoints<32000) maxWeight = 0.02;
		else if (numPoints >= 32000 && numPoints <64000) maxWeight = 0.015;
		else if (numPoints >= 64000 && numPoints <128000) maxWeight = 0.010;
		else if (numPoints >= 128000) maxWeight = 0.010;
		
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i < numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					for (int j = i+1; j <=numPoints; j++)
					{
						double jX = ((double)rand() / (RAND_MAX));
						double jY = ((double)rand() / (RAND_MAX));
						double weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2));
						if (weight - maxWeight < EPS) {
							cout << "i: " << i << " j: " << j << endl;
							G->addEdge(i, j, weight);
							G->addEdge(j, i, weight);
						}
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
		double maxWeight = 2.0;
		if (numPoints >= 100 && numPoints<1000) maxWeight = 0.50;
		else if (numPoints >= 1000 && numPoints<2000) maxWeight = 0.30;
		else if (numPoints >= 2000 && numPoints<4000) maxWeight = 0.15;
		else if (numPoints >= 4000 && numPoints < 8000) maxWeight = 0.10;
		else if (numPoints >= 8000 && numPoints<16000) maxWeight = 0.08;
		else if (numPoints >= 16000 && numPoints<32000) maxWeight = 0.07;
		else if (numPoints >= 32000 && numPoints <64000) maxWeight = 0.07;
		else if (numPoints >= 64000 && numPoints <128000) maxWeight = 0.06;
		else if (numPoints >= 128000) maxWeight = 0.04;
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i < numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					double iZ = ((double)rand() / (RAND_MAX));
					for (int j = i+1; j <= numPoints; j++)
					{
						double jX = ((double)rand() / (RAND_MAX));
						double jY = ((double)rand() / (RAND_MAX));
						double jZ = ((double)rand() / (RAND_MAX));
						double weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2) + pow((iZ - jZ), 2));
						if (weight - maxWeight < EPS) {
							cout << "i: " << i << " j: " << j << endl;
							G->addEdge(i, j, weight);
							G->addEdge(j, i, weight);
						}
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
		double maxWeight = 2.0;
		if (numPoints >= 100 && numPoints<1000) maxWeight = 0.5;
		else if (numPoints >= 1000 && numPoints<2000) maxWeight = 0.3;
		else if (numPoints >= 2000 && numPoints<4000) maxWeight = 0.25;
		else if (numPoints >= 4000 && numPoints < 8000) maxWeight = 0.23;
		else if (numPoints >= 8000 && numPoints<16000) maxWeight = 0.20;
		else if (numPoints >= 16000 && numPoints<32000) maxWeight = 0.15;
		else if (numPoints >= 32000 && numPoints <64000) maxWeight = 0.12;
		else if (numPoints >= 64000 && numPoints <128000) maxWeight = 0.10;
		else if (numPoints >= 128000) maxWeight = 0.08;
		while (trialIndex < numTrials) {
			srand((unsigned int)time(0));
			Graph* G = new Graph(numPoints);
			if (G != NULL) {
				for (int i = 1; i < numPoints; i++)
				{
					double iX = ((double)rand() / (RAND_MAX));
					double iY = ((double)rand() / (RAND_MAX));
					double iZ = ((double)rand() / (RAND_MAX));
					double iW = ((double)rand() / (RAND_MAX));
					for (int j = i+1; j <= numPoints; j++)
					{
						double jX = ((double)rand() / (RAND_MAX));
						double jY = ((double)rand() / (RAND_MAX));
						double jZ = ((double)rand() / (RAND_MAX));
						double jW = ((double)rand() / (RAND_MAX));
						double weight = sqrt(pow((iX - jX), 2) + pow((iY - jY), 2) + pow((iZ - jZ), 2) + pow((iW - jW), 2));
						
						if (weight - maxWeight < EPS) {
							cout << "i: " << i << " j: " << j << endl;
							G->addEdge(i, j, weight);
							G->addEdge(j, i, weight);
						}
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