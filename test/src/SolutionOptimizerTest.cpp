#include "SolutionOptimizerTest.h"

#include "RubiksGenerator.h"
#include "SolutionOptimizer.h"
#include "SolverAlgorithm.h"
#include "TestUtils.h"
#include "Util.h"

#include <cstdlib>


CPPUNIT_TEST_SUITE_REGISTRATION(SolutionOptimizerTest);


void SolutionOptimizerTest::setUp() {}

void SolutionOptimizerTest::tearDown() {}

void SolutionOptimizerTest::testOptimizeAlreadyComplete() {
	RubiksState rubiks = readRubiks("state_complete.txt");
	RotationList solution;
	
	RotationList finalSolution;
	optimizeSolution(finalSolution, solution, rubiks);
	
	CPPUNIT_ASSERT(finalSolution.empty());
}

void SolutionOptimizerTest::testOptimizeState1() {
	RubiksState rubiks = readRubiks("state1.txt");
	RotationList solution;
	
	solveAlgorithm(solution, rubiks);
	
	RotationList finalSolution;
	optimizeSolution(finalSolution, solution, rubiks);
	
	for (RotationList::const_iterator it = finalSolution.begin(); it != finalSolution.end(); ++it)
		rubiks = rubiks.rotate(*it);
	
	CPPUNIT_ASSERT(rubiks.isComplete());
	CPPUNIT_ASSERT(finalSolution.size() <= solution.size());
}

void SolutionOptimizerTest::testOptimizeRandomCubes() {
	srand(42); // use fixed seed, so the test can be repeated
	
	const unsigned int CUBE_COUNT = 512;
	const unsigned int RANDOM_ROTATIONS = 512;
	
	for (unsigned int i = 0; i < CUBE_COUNT; ++i) {
		RubiksState rubiks = generateRandomRubiks(RANDOM_ROTATIONS);
		RotationList solution;
		
		bool solved = solveAlgorithm(solution, rubiks);
		CPPUNIT_ASSERT(solved);
		
		RotationList finalSolution;
		optimizeSolution(finalSolution, solution, rubiks);
		
		for (RotationList::const_iterator it = finalSolution.begin(); it != finalSolution.end(); ++it)
			rubiks = rubiks.rotate(*it);
		
		CPPUNIT_ASSERT(rubiks.isComplete());
		CPPUNIT_ASSERT(finalSolution.size() <= solution.size());
	}
}
