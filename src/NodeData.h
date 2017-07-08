#ifndef NODE_DATA_H
#define NODE_DATA_H

#include "RubiksState.h"


struct NodeData {
	inline NodeData() : cameFrom(NULL), cameFromRotation(R_COUNT), gScore(0.0f), fScore(0.0f), closed(false), heapIndex(0) {}
	
	inline NodeData(const RubiksState & rs, NodeData *cFrom, Rotation cFromR, unsigned int g, unsigned int f) : rubiksState(rs),
			cameFrom(cFrom), cameFromRotation(cFromR), gScore(g), fScore(f), closed(false), heapIndex(0) {}
	
	inline bool operator<(const NodeData & other) {
		return fScore < other.fScore;
	}
	
	RubiksState rubiksState;
	NodeData *cameFrom;
	Rotation cameFromRotation;
	unsigned int gScore;
	unsigned int fScore;
	bool closed;
	
	unsigned int heapIndex;
};

#endif
