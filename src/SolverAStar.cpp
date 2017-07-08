#include "SolverAStar.h"

#include "NodeHeap.h"

#include <map>
#include <set>
#include <iostream>


typedef std::map<RubiksState, NodeData> NodeDataMap;
typedef std::pair<RubiksState, NodeData> NodeDataPair;


static const unsigned int MOVE_COST = 100;

static unsigned int closest = 1000000000;


static void reconstructPath(RotationList & solution, const NodeDataMap & nodeDataMap, NodeData *completeNodeData);

bool solveAStar(RotationList & solution, const RubiksState & startingRubiks) {
	NodeDataMap nodeDataMap;
	NodeHeap openset;
	
	const unsigned int sourceValue = startingRubiks.heuristicDist();
	
	NodeDataMap::iterator sourceIt = nodeDataMap.insert(NodeDataPair(startingRubiks, NodeData(startingRubiks, NULL, R_COUNT, 0, sourceValue))).first;
	openset.insert(&sourceIt->second);
	
	while (!openset.isEmpty()) {
		NodeData *nodeData = openset.top();
		
		if (nodeData->rubiksState.isComplete()) {
			reconstructPath(solution, nodeDataMap, nodeData);
			return true;
		}
		
		openset.popTop();
		nodeData->closed = true;
		
		for (Rotation r = (Rotation)0; r < R_COUNT; r = (Rotation)(r+1)) {
			RubiksState t = nodeData->rubiksState.rotate(r);
			
			NodeDataMap::iterator tDataIt = nodeDataMap.find(t);
			
			const unsigned int tentativeGScore = nodeData->gScore + MOVE_COST;
			const unsigned int hVal = std::min(nodeData->fScore - nodeData->gScore, t.heuristicDist());
			
			
			if (tDataIt == nodeDataMap.end()) {
				if (hVal < closest) {
					closest = hVal;
					std::cout << "Closest: " << closest << " (" << (tentativeGScore / MOVE_COST) << ", " << nodeDataMap.size() << " " << openset.getVector().size() << ")\n";
					std::cout << sizeof(NodeData) << "\n";
					std::cout << t << "\n\n\n--------------------------------------------------------------\n\n";
				}
				
				const unsigned int fVal = tentativeGScore + hVal;
				
				tDataIt = nodeDataMap.insert(NodeDataPair(t, NodeData(t, nodeData, r, tentativeGScore, fVal))).first;
				
				openset.insert(&tDataIt->second);
			}
			else {
				if (tDataIt->second.closed) continue;
				
				if (tentativeGScore < tDataIt->second.gScore) {
					tDataIt->second.cameFrom = nodeData;
					tDataIt->second.cameFromRotation = r;
					tDataIt->second.gScore = tentativeGScore;
					tDataIt->second.fScore = tentativeGScore + hVal;
					
					openset.updateAt(tDataIt->second.heapIndex);
				}
			}
		}
	}
	
	return false;
}

static void reconstructPath(RotationList & solution, const NodeDataMap & nodeDataMap, NodeData *completeNodeData) {
	RotationList inverseSolution;
	inverseSolution.push_back(completeNodeData->cameFromRotation);
	
	NodeDataMap::const_iterator it = nodeDataMap.find(completeNodeData->rubiksState);
	
	while (it != nodeDataMap.end()) {
		if (!it->second.cameFrom) break;
		
		inverseSolution.push_back(it->second.cameFromRotation);
		it = nodeDataMap.find(it->second.cameFrom->rubiksState);
	}
	
	for (RotationList::reverse_iterator it = inverseSolution.rbegin(); it != inverseSolution.rend(); ++it) {
		solution.push_back(*it);
	}
}
