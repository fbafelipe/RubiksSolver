#include "SolverDepth.h"

#include "RubiksState.h"

#include <list>
#include <map>
#include <set>
#include <iostream>


static const unsigned int WIDE_DEPTH = 6;
static const unsigned int MAX_DEPTH = 20;


typedef std::set<RubiksState> RubiksSet;


struct RubiksNode {
	inline RubiksNode(const RubiksState & r, unsigned int d) : rubiks(r), depth(d) {}
	inline RubiksNode();
	
	RubiksState rubiks;
	unsigned int depth;
	
	RotationList solution;
};


static bool depthSearch(const RubiksState & rubiks, RotationList & solution, unsigned int depth, unsigned int maxDepth, const RubiksSet & rubiksSet);

bool solveDepth(RotationList & solution, const RubiksState & startingRubiks) {
	if (startingRubiks.isComplete()) return true;
	
	bool solved = false;
	unsigned int maxDepth = MAX_DEPTH;
	
	RubiksSet rubiksSet;
	std::list<RubiksNode> queue;
	
	rubiksSet.insert(startingRubiks);
	queue.push_back(RubiksNode(startingRubiks, 0));
	
	while (!queue.empty()) {
		RubiksNode node = queue.front();
		queue.pop_front();
		
		if (node.depth < WIDE_DEPTH) {
			for (Rotation r = (Rotation)0; r < R_COUNT; r = (Rotation)(r+1)) {
				RubiksState rubiks = node.rubiks.rotate(r);
				if (rubiksSet.find(rubiks) != rubiksSet.end()) continue;
				rubiksSet.insert(rubiks);
				
				RubiksNode newNode(rubiks, node.depth + 1);
				newNode.solution = node.solution;
				newNode.solution.push_back(r);
				
				if (rubiks.isComplete()) {
					solution = newNode.solution;
					return true;
				}
				
				queue.push_back(newNode);
			}
		}
		else {
			std::cout << "Doing depth search..." << std::endl;
			
			if (depthSearch(node.rubiks, node.solution, node.depth, maxDepth, rubiksSet)) {
				if (!solved || node.solution.size() < solution.size()) {
					solution = node.solution;
					maxDepth = solution.size() - 1;
					solved = true;
				}
			}
		}
	}
	
	return solved;
}

static bool depthSearch(const RubiksState & rubiks, RotationList & solution, unsigned int depth, unsigned int maxDepth, const RubiksSet & rubiksSet) {
	RotationList foundSol;
	bool solved = false;
	
	for (Rotation r = (Rotation)0; r < R_COUNT; r = (Rotation)(r+1)) {
		if (r == solution.back() || r == INVERSE_ROTATION[solution.back()]) continue;
		
		RubiksState rs = rubiks.rotate(r);
		if (rubiksSet.find(rubiks) != rubiksSet.end()) continue;
		if (rs.isComplete()) {
			solution.push_back(r);
			std::cout << "Solution found with " << solution.size() << " moves, searching for better..." << std::endl;
			return true;
		}
		
		if (depth >= maxDepth) continue;
		
		RotationList sol = solution;
		sol.push_back(r);
		if (depthSearch(rs, sol, depth+1, maxDepth, rubiksSet)) {
			if (!solved || sol.size() < foundSol.size()) {
				foundSol = sol;
				maxDepth = foundSol.size() - 1;
				solved = true;
			}
		}
	}
	
	return solved;
}
