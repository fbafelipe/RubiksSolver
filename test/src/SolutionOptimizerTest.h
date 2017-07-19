#ifndef SOLUTION_OPTIMIZER_TEST_H
#define SOLUTION_OPTIMIZER_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class SolutionOptimizerTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(SolutionOptimizerTest);
	
	CPPUNIT_TEST(testOptimizeAlreadyComplete);
	CPPUNIT_TEST(testOptimizeState1);
	CPPUNIT_TEST(testOptimizeRandomCubes);
	
	CPPUNIT_TEST_SUITE_END();
	
	public:
		void setUp();
		void tearDown();
		
		void testOptimizeAlreadyComplete();
		void testOptimizeState1();
		void testOptimizeRandomCubes();
};

#endif
