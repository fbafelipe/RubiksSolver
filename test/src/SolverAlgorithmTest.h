#ifndef SOLVER_ALGORITHM_TEST_H
#define SOLVER_ALGORITHM_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class SolverAlgorithmTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(SolverAlgorithmTest);
	
	CPPUNIT_TEST(testSolveAlreadyComplete);
	CPPUNIT_TEST(testSolveState1);
	CPPUNIT_TEST(testSolveRandomCubes);
	
	CPPUNIT_TEST_SUITE_END();
	
	public:
		void setUp();
		void tearDown();
		
		void testSolveAlreadyComplete();
		void testSolveState1();
		void testSolveRandomCubes();
};

#endif
