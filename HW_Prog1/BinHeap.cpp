#include "BinHeap.h"

using namespace std;

template<class T>
BinHeap<T>::BinHeap(int iSize) {
	heapElements(iSize + 2);
	positionVec(iSize + 2);
	maxSize = iSize;
	heapSize = 0;
}

//template<class T>
//BinHeap<T>::BinHeap(const vector<T>& iElems)
//{
//}

template<class T>
void BinHeap<T>::insert(const T & elem)
{
	heapSize++;
	int N = heapSize;
	heapElements[heapSize] = elem;
	positionVec[elem.getVertexIndex()] = heapSize;
	while ((N > 1) && (heapElements[N / 2] > heapElements[N])) {
		T temp = heapElements[N];
		heapElements[N] = heapElements[N/2];
		positionVec[heapElements[N].getVertexIndex()] = N;
		heapElements[N / 2] = temp;
		positionVec[temp.getVertexIndex()] = N/2;
		N = (N / 2);
	}
}

template<class T>
T & BinHeap<T>::extractMin()
{
	int root = 1;
	T min = heapElements[root];
	heapElements[root] = heapElements[heapSize--];
	minHeapify(root);
	return min;
}

template<class T>
void BinHeap<T>::changeKey(T & elem, double val)
{
	int root = 1;
	
}

//template<class T>
//void BinHeap<T>::buildHeap()
//{
//}

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
	if ((r <= heapSize) && (heapElements[r] < heapElements[iPos])) {
		smallest = r;
	}
	if (smallest != iPos) {
		T temp = heapElements[iPos];
		heapElements[iPos] = heapElements[smallest];
		heapElements[smallest] = temp;
		minHeapify(smallest);
	}
}
