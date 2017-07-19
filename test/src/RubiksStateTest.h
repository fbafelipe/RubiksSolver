#ifndef RUBIKS_STATE_TEST_H
#define RUBIKS_STATE_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class RubiksStateTest : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(RubiksStateTest);
	
	CPPUNIT_TEST(testGetEdgesIncompleteCube);
	CPPUNIT_TEST(testGetEdgesCompleteCube);
	
	CPPUNIT_TEST(testGetCornersIncompleteCube);
	CPPUNIT_TEST(testGetCornersCompleteCube);
	
	CPPUNIT_TEST(testGetCornerColorCompleteCube);
	CPPUNIT_TEST(testGetCornerColorUniqueColors);
	
	CPPUNIT_TEST(testIsCompleteIncompleteCube);
	CPPUNIT_TEST(testIsCompleteCompleteCube);
	
	CPPUNIT_TEST_SUITE_END();
	
	public:
		void setUp();
		void tearDown();
		
		void testGetEdgesIncompleteCube();
		void testGetEdgesCompleteCube();
		
		void testGetCornersIncompleteCube();
		void testGetCornersCompleteCube();
		
		void testGetCornerColorCompleteCube();
		void testGetCornerColorUniqueColors();
		
		void testIsCompleteIncompleteCube();
		void testIsCompleteCompleteCube();
};

#endif
