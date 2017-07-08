#ifndef NODE_HEAP_H
#define NODE_HEAP_H

#include "NodeData.h"

#include <cassert>
#include <vector>


class NodeHeap {
public:
	inline bool isEmpty() const {
		return heap.empty();
	}
	
	inline unsigned int getSize() const {
		return heap.size();
	}
	
	inline void insert(NodeData *data) {
		heap.push_back(data);
		upHeap(heap.size() - 1);
	}
	
	inline NodeData *top() {
		return heap.front();
	}
	
	inline void popTop() {
		heap.front() = heap.back();
		heap.front()->heapIndex = 0;
		heap.pop_back();
		downHeap(0);
	}
	
	inline void removeAt(unsigned int index) {
		heap[index] = heap.back();
		heap[index]->heapIndex = index;
		heap.pop_back();
		downHeap(index);
	}
	
	inline void updateAt(unsigned int index) {
		upHeap(index);
	}
	
	inline const std::vector<NodeData *> & getVector() {
		return heap;
	}
	
	inline void clear() {
		heap.clear();
	}
	
private:
	inline void upHeap(unsigned int index) {
		NodeData *tmp = heap[index];
		
		while (index > 0) {
			unsigned int parent = (index+1)/2 - 1;
			assert(parent < index);
			
			NodeData *p = heap[parent];
			
			if (*tmp < *p) {
				heap[index] = p;
				heap[index]->heapIndex = index;
				index = parent;
			}
			else break;
		}
		
		heap[index] = tmp;
		heap[index]->heapIndex = index;
	}
	
	inline void downHeap(unsigned int index) {
		NodeData *tmp = heap[index];
		
		const unsigned int halfSize = heap.size()/2;
		
		while (index < halfSize) {
			unsigned int i = 2*index + 1;
			
			if (index < heap.size() && *heap[i+1] < *heap[i]) ++i;
			
			if (*heap[i] < *tmp) {
				heap[index] = heap[i];
				heap[index]->heapIndex = index;
				index = i;
			}
			else break;
		}
		
		heap[index] = tmp;
		heap[index]->heapIndex = index;
	}
	
	std::vector<NodeData *> heap;
};

#endif
