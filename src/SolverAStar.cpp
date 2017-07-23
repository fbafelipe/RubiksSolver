#include "SolverAStar.h"

#include "NodeHeap.h"
#include "SolverAlgorithm.h"
#include "Util.h"

#include <map>
#include <set>
#include <iostream>
#include <limits>


typedef std::map<RubiksState, NodeData> NodeDataMap;
typedef std::pair<RubiksState, NodeData> NodeDataPair;


static const unsigned int MOVE_COST = 1;
static const unsigned int MAX_TIME = 5000;


static void reconstructPath(RotationList & solution, const NodeDataMap & nodeDataMap, NodeData *rootNode, NodeData *completeNodeData);
static unsigned int heuristicDist(const RubiksState & state);

bool solveAStar(RotationList & solution, const RubiksState & startingRubiks) {
	NodeDataMap nodeDataMap;
	NodeHeap openset;
	
	const unsigned int sourceValue = heuristicDist(startingRubiks);
	
	uint64_t startTime = currentTime();
	
	NodeDataMap::iterator sourceIt = nodeDataMap.insert(NodeDataPair(startingRubiks, NodeData(startingRubiks, NULL, R_COUNT, 0, sourceValue))).first;
	openset.insert(&sourceIt->second);
	
	NodeData *rootNode = &sourceIt->second;
	NodeData *bestSolution = rootNode;
	unsigned int bestSolutionMoves = std::numeric_limits<unsigned int>::max();
	
	unsigned int attempts = 0;
	
	while (!openset.isEmpty()) {
		NodeData *nodeData = openset.top();
		
		if (nodeData->rubiksState.isComplete()) {
			reconstructPath(solution, nodeDataMap, rootNode, nodeData);
			return true;
		}
		
		if (currentTime() > startTime + MAX_TIME) {
			std::cout << "Timeout with " << attempts << " attempts" << std::endl;
			reconstructPath(solution, nodeDataMap, rootNode, bestSolution);
			return solveAlgorithm(solution, bestSolution->rubiksState);
		}
		
		openset.popTop();
		nodeData->closed = true;
		++attempts;
		
		if (nodeData->fScore < bestSolutionMoves) {
			bestSolutionMoves = nodeData->fScore;
			bestSolution = nodeData;
			std::cout << "Best: " << bestSolutionMoves << std::endl;
		}
		
		Rotation comeFromInverse = INVERSE_ROTATION[nodeData->cameFromRotation];
		Rotation tripleRotation = R_COUNT;
		if (nodeData->cameFrom != NULL && nodeData->cameFrom->cameFrom != NULL
					&& nodeData->cameFrom->cameFromRotation == nodeData->cameFrom->cameFrom->cameFromRotation) {
			tripleRotation = nodeData->cameFrom->cameFromRotation;
		}
		
		for (Rotation r = (Rotation)0; r < R_COUNT; r = (Rotation)(r+1)) {
			if (r == comeFromInverse || r == tripleRotation)
				continue;
			
			RubiksState t = nodeData->rubiksState.rotate(r);
			NodeDataMap::iterator tDataIt = nodeDataMap.find(t);
			
			if (tDataIt != nodeDataMap.end() && tDataIt->second.closed)
				continue;
			
			const unsigned int tentativeGScore = nodeData->gScore + MOVE_COST;
			const unsigned int dist = heuristicDist(t);
			const unsigned int hVal = std::min(nodeData->fScore - nodeData->gScore, dist);
			
			if (tDataIt == nodeDataMap.end()) {
				const unsigned int fVal = tentativeGScore + hVal;
				tDataIt = nodeDataMap.insert(NodeDataPair(t, NodeData(t, nodeData, r, tentativeGScore, fVal))).first;
				openset.insert(&tDataIt->second);
			}
			else if (tentativeGScore < tDataIt->second.gScore) {
				tDataIt->second.cameFrom = nodeData;
				tDataIt->second.cameFromRotation = r;
				tDataIt->second.gScore = tentativeGScore;
				tDataIt->second.fScore = tentativeGScore + hVal;
				
				openset.updateAt(tDataIt->second.heapIndex);
			}
		}
	}
	
	return false;
}

static void reconstructPath(RotationList & solution, const NodeDataMap & nodeDataMap, NodeData *rootNode, NodeData *completeNodeData) {
	RotationList inverseSolution;
	NodeData *nodeData = completeNodeData;
	
	while (nodeData != rootNode) {
		inverseSolution.push_back(nodeData->cameFromRotation);
		nodeData = nodeData->cameFrom;
	}
	
	for (RotationList::reverse_iterator it = inverseSolution.rbegin(); it != inverseSolution.rend(); ++it) {
		solution.push_back(*it);
	}
	
	RubiksState state = rootNode->rubiksState;
	for (RotationList::const_iterator it = solution.begin(); it != solution.end(); ++it) {
		state = state.rotate(*it);
	}
	assert(state == completeNodeData->rubiksState);
}

static unsigned int heuristicDist(const RubiksState & state) {
	RotationList solution;
	solveAlgorithm(solution, state);
	
	return solution.size();
}
