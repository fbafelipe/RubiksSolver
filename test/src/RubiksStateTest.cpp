#include "RubiksStateTest.h"

#include "RubiksGenerator.h"
#include "RubiksState.h"
#include "TestUtils.h"


CPPUNIT_TEST_SUITE_REGISTRATION(RubiksStateTest);


static RubiksState createWhiteCubeWithSingleRed(Face face, unsigned int i, unsigned int j);


void RubiksStateTest::setUp() {}

void RubiksStateTest::tearDown() {}

void RubiksStateTest::testGetEdgesIncompleteCube() {
	RubiksState rubiks = readRubiks("state1.txt");
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_LEFT) == (C_YELLOW | C_BLUE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_NEAR) == (C_YELLOW | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_RIGHT) == (C_BLUE | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_FAR) == (C_WHITE | C_RED));
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_LEFT_NEAR) == (C_WHITE | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_RIGHT_NEAR) == (C_RED | C_YELLOW));
	CPPUNIT_ASSERT(rubiks.getEdge(P_RIGHT_FAR) == (C_YELLOW | C_GREEN));
	CPPUNIT_ASSERT(rubiks.getEdge(P_LEFT_FAR) == (C_RED | C_GREEN));
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_LEFT) == (C_WHITE | C_GREEN));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_NEAR) == (C_WHITE | C_BLUE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_RIGHT) == (C_GREEN | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_FAR) == (C_BLUE | C_RED));
}

void RubiksStateTest::testGetEdgesCompleteCube() {
	RubiksState rubiks = readRubiks("state_complete.txt");
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_LEFT) == (C_BLUE | C_WHITE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_NEAR) == (C_BLUE | C_RED));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_RIGHT) == (C_BLUE | C_YELLOW));
	CPPUNIT_ASSERT(rubiks.getEdge(P_TOP_FAR) == (C_BLUE | C_ORANGE));
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_LEFT_NEAR) == (C_WHITE | C_RED));
	CPPUNIT_ASSERT(rubiks.getEdge(P_RIGHT_NEAR) == (C_YELLOW | C_RED));
	CPPUNIT_ASSERT(rubiks.getEdge(P_RIGHT_FAR) == (C_YELLOW | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_LEFT_FAR) == (C_WHITE | C_ORANGE));
	
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_LEFT) == (C_GREEN | C_WHITE));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_NEAR) == (C_GREEN | C_RED));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_RIGHT) == (C_GREEN | C_YELLOW));
	CPPUNIT_ASSERT(rubiks.getEdge(P_BOTTOM_FAR) == (C_GREEN | C_ORANGE));
}

void RubiksStateTest::testGetCornersIncompleteCube() {
	RubiksState rubiks = readRubiks("state1.txt");
	
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_LEFT_NEAR) == (C_BLUE | C_YELLOW | C_RED));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_RIGHT_NEAR) == (C_BLUE | C_ORANGE | C_YELLOW));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_LEFT_FAR) == (C_GREEN | C_RED | C_WHITE));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_RIGHT_FAR) == (C_YELLOW | C_GREEN | C_ORANGE));
	
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_LEFT_NEAR) == (C_WHITE | C_BLUE | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_RIGHT_NEAR) == (C_GREEN | C_RED | C_YELLOW));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_LEFT_FAR) == (C_WHITE | C_ORANGE | C_GREEN));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_RIGHT_FAR) == (C_WHITE | C_BLUE | C_RED));
}

void RubiksStateTest::testGetCornerColorCompleteCube() {
	RubiksState rubiks = generateCompleteRubiks();
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_TOP) == FACE_COLOR_MAP[F_TOP]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_TOP) == FACE_COLOR_MAP[F_TOP]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_TOP) == FACE_COLOR_MAP[F_TOP]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_TOP) == FACE_COLOR_MAP[F_TOP]);
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_BOTTOM) == FACE_COLOR_MAP[F_BOTTOM]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_BOTTOM) == FACE_COLOR_MAP[F_BOTTOM]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_BOTTOM) == FACE_COLOR_MAP[F_BOTTOM]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_BOTTOM) == FACE_COLOR_MAP[F_BOTTOM]);
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_LEFT) == FACE_COLOR_MAP[F_LEFT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_LEFT) == FACE_COLOR_MAP[F_LEFT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_LEFT) == FACE_COLOR_MAP[F_LEFT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_LEFT) == FACE_COLOR_MAP[F_LEFT]);
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_RIGHT) == FACE_COLOR_MAP[F_RIGHT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_RIGHT) == FACE_COLOR_MAP[F_RIGHT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_RIGHT) == FACE_COLOR_MAP[F_RIGHT]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_RIGHT) == FACE_COLOR_MAP[F_RIGHT]);
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_NEAR) == FACE_COLOR_MAP[F_NEAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_NEAR) == FACE_COLOR_MAP[F_NEAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_NEAR) == FACE_COLOR_MAP[F_NEAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_NEAR) == FACE_COLOR_MAP[F_NEAR]);
	
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_FAR) == FACE_COLOR_MAP[F_FAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_FAR) == FACE_COLOR_MAP[F_FAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_FAR) == FACE_COLOR_MAP[F_FAR]);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_FAR) == FACE_COLOR_MAP[F_FAR]);
}

void RubiksStateTest::testGetCornerColorUniqueColors() {
	RubiksState rubiks;
	
	rubiks = createWhiteCubeWithSingleRed(F_TOP, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_TOP) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_TOP, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_TOP) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_TOP, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_TOP) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_TOP, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_TOP) == C_RED);
	
	rubiks = createWhiteCubeWithSingleRed(F_BOTTOM, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_BOTTOM) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_BOTTOM, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_BOTTOM) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_BOTTOM, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_BOTTOM) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_BOTTOM, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_BOTTOM) == C_RED);
	
	rubiks = createWhiteCubeWithSingleRed(F_LEFT, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_LEFT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_LEFT, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_LEFT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_LEFT, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_LEFT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_LEFT, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_LEFT) == C_RED);
	
	rubiks = createWhiteCubeWithSingleRed(F_RIGHT, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_RIGHT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_RIGHT, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_RIGHT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_RIGHT, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_RIGHT) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_RIGHT, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_RIGHT) == C_RED);
	
	rubiks = createWhiteCubeWithSingleRed(F_NEAR, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_NEAR, F_NEAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_NEAR, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_NEAR, F_NEAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_NEAR, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_NEAR, F_NEAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_NEAR, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_NEAR, F_NEAR) == C_RED);
	
	rubiks = createWhiteCubeWithSingleRed(F_FAR, 0, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_LEFT_FAR, F_FAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_FAR, 0, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_TOP_RIGHT_FAR, F_FAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_FAR, 2, 2);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_LEFT_FAR, F_FAR) == C_RED);
	rubiks = createWhiteCubeWithSingleRed(F_FAR, 2, 0);
	CPPUNIT_ASSERT(rubiks.getCornerColor(P_BOTTOM_RIGHT_FAR, F_FAR) == C_RED);
}

void RubiksStateTest::testGetCornersCompleteCube() {
	RubiksState rubiks = readRubiks("state_complete.txt");
	
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_LEFT_NEAR) == (C_BLUE | C_WHITE | C_RED));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_RIGHT_NEAR) == (C_BLUE | C_YELLOW | C_RED));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_LEFT_FAR) == (C_BLUE | C_WHITE | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getCorner(P_TOP_RIGHT_FAR) == (C_BLUE | C_YELLOW | C_ORANGE));
	
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_LEFT_NEAR) == (C_GREEN | C_WHITE | C_RED));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_RIGHT_NEAR) == (C_GREEN | C_YELLOW | C_RED));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_LEFT_FAR) == (C_GREEN | C_WHITE | C_ORANGE));
	CPPUNIT_ASSERT(rubiks.getCorner(P_BOTTOM_RIGHT_FAR) == (C_GREEN | C_YELLOW | C_ORANGE));
}

void RubiksStateTest::testIsCompleteIncompleteCube() {
	RubiksState rubiks = readRubiks("state1.txt");
	
	CPPUNIT_ASSERT(!rubiks.isComplete());
}

void RubiksStateTest::testIsCompleteCompleteCube() {
	RubiksState rubiks = readRubiks("state_complete.txt");
	
	CPPUNIT_ASSERT(rubiks.isComplete());
}

static RubiksState createWhiteCubeWithSingleRed(Face face, unsigned int row, unsigned int col) {
	RubiksState rubiks;
	
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (i != 1 || j != 1)
					rubiks.setColor(C_WHITE, (Face) f, i, j);
			}
		}
	}
	
	rubiks.setColor(C_RED, face, row, col);
	
	return rubiks;
}
