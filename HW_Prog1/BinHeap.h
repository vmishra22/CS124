#pragma once
#ifndef _BIN_HEAP_
#define _BIN_HEAP_

#include <vector>
#include <iostream>
using namespace std;

template <class T>
class BinHeap {
public: 
	BinHeap(int iSize): heapElements(iSize + 2), positionVec(iSize + 2, -1){
		maxSize = iSize;
		heapSize = 0;
	}

	bool isEmpty();
	void insert(T& elem);
	T extractMin();
	void changeKey(T& elem, double val);
	void minHeapify(int iPos);
private:
	vector<T> heapElements;
	vector<int> positionVec;
	int heapSize;
	int maxSize;
};



template<class T>
bool BinHeap<T>::isEmpty() {
	return (heapSize == 0);
}

template<class T>
void BinHeap<T>::insert( T & elem)
{
	if (positionVec[elem.getVertexIndex()] == -1) {
		heapSize++;
		int N = heapSize;
		heapElements[heapSize] = elem;
		positionVec[elem.getVertexIndex()] = heapSize;
		while ((N > 1) && (heapElements[N / 2] > heapElements[N])) {
			T temp = heapElements[N];
			heapElements[N] = heapElements[N / 2];
			positionVec[heapElements[N].getVertexIndex()] = N;
			heapElements[N / 2] = temp;
			positionVec[temp.getVertexIndex()] = N / 2;
			N = (N / 2);
		}
	}
	else {
		changeKey(elem, elem.getVertexDist());
	}
}

template<class T>
T BinHeap<T>::extractMin()
{
	int root = 1;
	T min = heapElements[root];
	heapElements[root] = heapElements[heapSize--];
	positionVec[heapElements[root].getVertexIndex()] = root;
	minHeapify(root);
	return min;
}

template<class T>
void BinHeap<T>::changeKey(T & elem, double val)
{
	int heapPos = positionVec[elem.getVertexIndex()];
	heapElements[heapPos].setVertexDist(val);
	int N = heapPos;
	minHeapify(N);
	while ((N > 1) && (heapElements[N / 2] > heapElements[N])) {
		T temp = heapElements[N];
		heapElements[N] = heapElements[N / 2];
		positionVec[heapElements[N].getVertexIndex()] = N;
		heapElements[N / 2] = temp;
		positionVec[temp.getVertexIndex()] = N / 2;
		N = (N / 2);
	}
}

template<class T>
void BinHeap<T>::minHeapify(int iPos)
{
	int l = 2 * iPos;
	int r = 2 * iPos + 1;
	int smallest = 0;

	if ((l <= heapSize) && (heapElements[l] < heapElements[iPos])) {
		smallest = l;
	}
	else {
		smallest = iPos;
	}
	if ((r <= heapSize) && (heapElements[r] < heapElements[smallest])) {
		smallest = r;
	}
	if (smallest != iPos) {
		T temp = heapElements[iPos];
		heapElements[iPos] = heapElements[smallest];
		positionVec[heapElements[iPos].getVertexIndex()] = iPos;
		heapElements[smallest] = temp;
		positionVec[temp.getVertexIndex()] = smallest;
		minHeapify(smallest);
	}
}
#endif