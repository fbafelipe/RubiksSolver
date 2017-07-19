#include "SolverAlgorithmTest.h"

#include "RubiksGenerator.h"
#include "SolverAlgorithm.h"
#include "TestUtils.h"
#include "Util.h"

#include <cstdlib>


CPPUNIT_TEST_SUITE_REGISTRATION(SolverAlgorithmTest);


void SolverAlgorithmTest::setUp() {}

void SolverAlgorithmTest::tearDown() {}

void SolverAlgorithmTest::testSolveAlreadyComplete() {
	RubiksState rubiks = readRubiks("state_complete.txt");
	RotationList solution;
	
	bool solved = solveAlgorithm(solution, rubiks);
	
	CPPUNIT_ASSERT(solved);
	CPPUNIT_ASSERT(solution.empty());
}

void SolverAlgorithmTest::testSolveState1() {
	RubiksState rubiks = readRubiks("state1.txt");
	RotationList solution;
	
	bool solved = solveAlgorithm(solution, rubiks);
	
	CPPUNIT_ASSERT(solved);
	
	for (RotationList::const_iterator it = solution.begin(); it != solution.end(); ++it)
		rubiks = rubiks.rotate(*it);
	
	CPPUNIT_ASSERT(rubiks.isComplete());
}

void SolverAlgorithmTest::testSolveRandomCubes() {
	srand(42); // use fixed seed, so the test can be repeated
	
	const unsigned int CUBE_COUNT = 512;
	const unsigned int RANDOM_ROTATIONS = 512;
	
	for (unsigned int i = 0; i < CUBE_COUNT; ++i) {
		RubiksState rubiks = generateRandomRubiks(RANDOM_ROTATIONS);
		RotationList solution;
		
		bool solved = solveAlgorithm(solution, rubiks);
	
		CPPUNIT_ASSERT(solved);
		
		for (RotationList::const_iterator it = solution.begin(); it != solution.end(); ++it)
			rubiks = rubiks.rotate(*it);
		
		CPPUNIT_ASSERT(rubiks.isComplete());
	}
}
