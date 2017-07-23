#include "RubiksReader.h"
#include "RubiksState.h"
#include "SolutionOptimizer.h"
#include "SolverAlgorithm.h"
#include "SolverAStar.h"
#include "SolverDepth.h"
#include "Util.h"

#include <iostream>
#include <cstdlib>
#include <cassert>


int main(int argc, char *argv[]) {
	RubiksState rubiks;
	
	if (argc >= 2)
		readRubiksFromFile(rubiks, argv[1]);
	else
		readRubiksFromStdin(rubiks);
	
	RotationList solution;
	if (!solveAStar(solution, rubiks)) {
	//if (!solveAlgorithm(solution, rubiks)) {
		std::cerr << "Solution not found." << std::endl;
		return -1;
	}
	
	RotationList finalSolution;
	optimizeSolution(finalSolution, solution, rubiks);
	
	std::cout << "Solution found with " << finalSolution.size() << " moves. (optimized from " << solution.size() << ")" << std::endl;
	std::cout << "Look at red face, with blue top, then rotate this sequence:\n" << std::endl;
	
	for (RotationList::const_iterator it = finalSolution.begin(); it != finalSolution.end(); ++it) {
		std::cout << *it << " ";
		rubiks = rubiks.rotate(*it);
	}
	std::cout << std::endl;
	
	assert(rubiks.isComplete());
	
	return 0;
}
