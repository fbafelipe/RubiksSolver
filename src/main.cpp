#include "RubiksReader.h"
#include "RubiksState.h"
#include "SolverAStar.h"
#include "SolverDepth.h"
#include "Util.h"

#include <iostream>
#include <cstdlib>


int main(int argc, char *argv[]) {
	RubiksState rubiks;
	readRubiks(rubiks);
	
	RotationList solution;
	if (!solveAStar(solution, rubiks)) {
		std::cerr << "Solution not found." << std::endl;
		return -1;
	}
	
	std::cout << "Solution found with " << solution.size() << " moves." << std::endl;
	std::cout << "Look at red face, with blue top, then rotate this sequence:\n" << std::endl;
	
	for (RotationList::const_iterator it = solution.begin(); it != solution.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	
	return 0;
}
