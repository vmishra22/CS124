#pragma once
#ifndef _BIN_HEAP_
#define _BIN_HEAP_

#include <vector>
#include <iostream>

template <class T>
class BinHeap {
public: 
	BinHeap(int iSize = 10);
	//BinHeap(const vector<T>& iElems);

	void insert(const T& elem);
	T& extractMin();
	void changeKey(T& elem, double val);
	//void buildHeap();
	void minHeapify(int iPos);
private:
	std::vector<T> heapElements;
	int heapSize;
	int maxSize;
};

#endif