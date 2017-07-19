#include "SolverAlgorithm.h"

#include "RubiksState.h"
#include "Util.h"

#include <cassert>
#include <cstdlib>
#include <iostream>


static void solveTopEdges(RotationList & solution, RubiksState & rubiks);
static void putTopEdgesInPlace(RotationList & solution, RubiksState & rubiks, const EdgePosition *edgesPos, unsigned int edgesCount);
static void adjustTopEdgesOrientations(RotationList & solution, RubiksState & rubiks, const EdgePosition *edgesPos, unsigned int edgesCount);

static void solveTopCorners(RotationList & solution, RubiksState & rubiks);
static void positionCornerToMoveToTop(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos);
static void adjustTopCornerOrientation(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos);
static void switchCornerTopBottom(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos);

static void solveMiddleEdges(RotationList & solution, RubiksState & rubiks);
static void switchMiddleEdgeWithBottom(RotationList & solution, RubiksState & rubiks, Face switchFace, Face leftOrRight);

static void solveBottomEdges(RotationList & solution, RubiksState & rubiks);
static void adjustBottomEdgesOrientation(RotationList & solution, RubiksState & rubiks, EdgePosition *edgesPos, unsigned int edgesCount);
static void adjustBottomEdgesPositions(RotationList & solution, RubiksState & rubiks, EdgePosition *edgesPos, unsigned int edgesCount);
static void switchBottomEdgePosition(RotationList & solution, RubiksState & rubiks, EdgePosition edge);

static void solveBottomCorners(RotationList & solution, RubiksState & rubiks);
static void adjustBottomCornersPositions(RotationList & solution, RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount);
static bool findPivotFaceForBottomCornersPositionAdjust(RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount, Face *pivot);
static void adjustBottomCornersOrientations(RotationList & solution, RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount);

static unsigned int findBestInititalRotationForFace(RotationList & solution, RubiksState & rubiks, Face face, const EdgePosition *edgesPos, unsigned int edgesCount);
static void doRotation(RotationList & solution, RubiksState & rubiks, Rotation rotation);
static void doRotation(RotationList & solution, RubiksState & rubiks, Rotation rotation, unsigned int count);

class ReferenceRotator {
	private:
		RotationList *mSolution;
		RubiksState *mRubiks;
		Face mNearFace;
		Face mTopFace;
		
	public:
		ReferenceRotator(RotationList *solution, RubiksState *rubiks, Face nearFace, Face topFace) {
			mSolution = solution;
			mRubiks = rubiks;
			mNearFace = nearFace;
			mTopFace = topFace;
		}
		
		void rotate(Rotation rotation) {
			rotation = computeRelativeRotation(rotation, mNearFace, mTopFace);
			doRotation(*mSolution, *mRubiks, rotation);
		}
};


bool solveAlgorithm(RotationList & solution, const RubiksState & rubiks) {
	RubiksState state = rubiks;
	
	solveTopEdges(solution, state);
	solveTopCorners(solution, state);
	solveMiddleEdges(solution, state);
	solveBottomEdges(solution, state);
	solveBottomCorners(solution, state);
	
	return state.isComplete();
}

static void solveTopEdges(RotationList & solution, RubiksState & rubiks) {
	const unsigned int COUNT = 4;
	EdgePosition edgesPos[COUNT] = {P_TOP_LEFT, P_TOP_NEAR, P_TOP_RIGHT, P_TOP_FAR};
	
	findBestInititalRotationForFace(solution, rubiks, F_TOP, edgesPos, COUNT);
	putTopEdgesInPlace(solution, rubiks, edgesPos, COUNT);
	adjustTopEdgesOrientations(solution, rubiks, edgesPos, COUNT);
}

static void putTopEdgesInPlace(RotationList & solution, RubiksState & rubiks, const EdgePosition *edgesPos, unsigned int edgesCount) {
	for (unsigned int i = 0; i < edgesCount; ++i) {
		if (!rubiks.isEdgePosCorrect(edgesPos[i])) {
			EdgePosition targetPos = edgesPos[i];
			Edge edge = EDGE_FROM_POS_MAP[targetPos];
			EdgePosition currentPos = rubiks.getEdgePosition(edge);
			
			if (edgePosContainFace(currentPos, F_TOP)) {
				// a top edge on the wrong side face, move it to bottom so next step can solve it
				doRotation(solution, rubiks, (Rotation) getEdgePosOtherFace(currentPos, F_TOP), 2);
				currentPos = rubiks.getEdgePosition(edge);
			}
			
			Face targetSideFace = getEdgePosOtherFace(targetPos, F_TOP);
			
			if (edgePosContainFace(currentPos, F_BOTTOM)) {
				Face currentSideFace = getEdgePosOtherFace(currentPos, F_BOTTOM);
				
				unsigned int rotations = computeTransformSingleAxis(F_BOTTOM, currentSideFace, targetSideFace);
				doRotation(solution, rubiks, R_BOTTOM, rotations);
				doRotation(solution, rubiks, (Rotation) targetSideFace, 2);
				
				assert(rubiks.isEdgePosCorrect(targetPos));
			}
			else {
				Face faces[2];
				getEdgePosFaces(currentPos, faces);
				Face currentSideFace = rubiks.getEdgeColor(currentPos, faces[0]) == FACE_COLOR_MAP[F_TOP] ? faces[1] : faces[0];
				
				unsigned int topRotations = computeTransformSingleAxis(F_TOP, targetSideFace, currentSideFace);
				unsigned int sideRotations = computeTransformSingleAxis(currentSideFace, getEdgePosOtherFace(currentPos, currentSideFace), F_TOP);
				doRotation(solution, rubiks, R_TOP, topRotations);
				doRotation(solution, rubiks, (Rotation) currentSideFace, sideRotations);
				doRotation(solution, rubiks, R_TOP_INVERSE, topRotations);
				
				assert(rubiks.isEdgePosCorrect(targetPos));
			}
		}
	}
}

static void adjustTopEdgesOrientations(RotationList & solution, RubiksState & rubiks, const EdgePosition *edgesPos, unsigned int edgesCount) {
	for (unsigned int i = 0; i < edgesCount; ++i) {
		if (!rubiks.isEdgeCorrect(edgesPos[i])) {
			assert(rubiks.isEdgePosCorrect(edgesPos[i]));
			
			Face face = getEdgePosOtherFace(edgesPos[i], F_TOP);
			
			ReferenceRotator referenceRotator(&solution, &rubiks, face, F_TOP);
			referenceRotator.rotate(R_NEAR);
			referenceRotator.rotate(R_TOP_INVERSE);
			referenceRotator.rotate(R_RIGHT);
			referenceRotator.rotate(R_TOP);
		}
	}
}

static void solveTopCorners(RotationList & solution, RubiksState & rubiks) {
	const unsigned int COUNT = 4;
	CornerPosition cornersPos[COUNT] = {P_TOP_LEFT_NEAR, P_TOP_RIGHT_NEAR, P_TOP_LEFT_FAR, P_TOP_RIGHT_FAR};
	
	for (unsigned int i = 0; i < COUNT; ++i) {
		positionCornerToMoveToTop(solution, rubiks, cornersPos[i]);
		adjustTopCornerOrientation(solution, rubiks, cornersPos[i]);
	}
}

static void positionCornerToMoveToTop(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos) {
	Corner corner = CORNER_FROM_POS_MAP[targetPos];
	CornerPosition currentPos = rubiks.getCornerPosition(corner);
	
	if (currentPos == targetPos)
		return;
	
	if (!cornerPosContainFace(currentPos, F_BOTTOM)) {
		switchCornerTopBottom(solution, rubiks, currentPos);
		currentPos = rubiks.getCornerPosition(corner);
	}
	
	assert(cornerPosContainFace(currentPos, F_BOTTOM));
	
	RubiksState targetState = rubiks;
	CornerPosition targetBottomPos = getCornerOnBottom(targetPos);
	unsigned int rotations = 0;
	
	do {
		if (currentPos == targetBottomPos)
			break;
		
		targetState = targetState.rotate(R_BOTTOM);
		currentPos = targetState.getCornerPosition(corner);
		++rotations;
	} while (rotations < 4);
	
	if (rotations == 4)
		abort();
	
	doRotation(solution, rubiks, R_BOTTOM, rotations);
}

static void adjustTopCornerOrientation(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos) {
	const unsigned int MAX_ITERATIONS = 32;
	
	for (unsigned int i = 0; i < MAX_ITERATIONS && !rubiks.isCornerCorrect(targetPos); ++i) {
		switchCornerTopBottom(solution, rubiks, targetPos);
	}
	
	if (!rubiks.isCornerCorrect(targetPos))
		abort();
}

static void switchCornerTopBottom(RotationList & solution, RubiksState & rubiks, CornerPosition targetPos) {
	Face nearFace;
	switch (targetPos) {
		case P_TOP_LEFT_NEAR:
			nearFace = F_LEFT;
			break;
		case P_TOP_RIGHT_NEAR:
			nearFace = F_NEAR;
			break;
		case P_TOP_LEFT_FAR:
			nearFace = F_FAR;
			break;
		case P_TOP_RIGHT_FAR:
			nearFace = F_RIGHT;
			break;
		default:
			abort();
	}
	
	ReferenceRotator referenceRotator(&solution, &rubiks, nearFace, F_TOP);
	referenceRotator.rotate(R_RIGHT_INVERSE);
	referenceRotator.rotate(R_BOTTOM_INVERSE);
	referenceRotator.rotate(R_RIGHT);
	referenceRotator.rotate(R_BOTTOM);
}

static void solveMiddleEdges(RotationList & solution, RubiksState & rubiks) {
	const unsigned int COUNT = 4;
	EdgePosition edgesPos[COUNT] = {P_LEFT_NEAR, P_RIGHT_NEAR, P_RIGHT_FAR, P_LEFT_FAR};
	
	for (unsigned int i = 0; i < COUNT; ++i) {
		EdgePosition targetPos = edgesPos[i];
		Edge edge = EDGE_FROM_POS_MAP[targetPos];
		EdgePosition currentPos = rubiks.getEdgePosition(edge);
		
		if (rubiks.isEdgeCorrect(targetPos))
			continue;
		
		Face faces[2];
		unsigned int rotations;
		
		if (!edgePosContainFace(currentPos, F_BOTTOM)) {
			getEdgePosFacesOrdered(currentPos, faces, F_TOP);
			
			switchMiddleEdgeWithBottom(solution, rubiks, faces[0], F_LEFT);
			currentPos = rubiks.getEdgePosition(edge);
			
			assert(edgePosContainFace(currentPos, F_BOTTOM));
		}
		
		getEdgePosFacesOrdered(targetPos, faces, F_TOP);
		
		Face currentSideFace = getEdgePosOtherFace(currentPos, F_BOTTOM);
		Face leftRightRef;
		Face rotateToFace;
		if (rubiks.getEdgeColor(currentPos, currentSideFace) == FACE_COLOR_MAP[faces[0]]) {
			leftRightRef = F_LEFT;
			rotateToFace = faces[0];
		}
		else {
			rotateToFace = faces[1];
			leftRightRef = F_RIGHT;
		}
		
		rotations = computeTransformSingleAxis(F_BOTTOM, currentSideFace, rotateToFace);
		doRotation(solution, rubiks, R_BOTTOM, rotations);
		switchMiddleEdgeWithBottom(solution, rubiks, rotateToFace, leftRightRef);
		doRotation(solution, rubiks, R_BOTTOM_INVERSE, rotations);
		
		assert(rubiks.isEdgeCorrect(targetPos));
	}
}

static void switchMiddleEdgeWithBottom(RotationList & solution, RubiksState & rubiks, Face switchFace, Face leftOrRight) {
	ReferenceRotator referenceRotator(&solution, &rubiks, switchFace, F_BOTTOM);
	
	if (leftOrRight == F_RIGHT) {
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_LEFT_INVERSE);
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_LEFT);
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_NEAR);
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_NEAR_INVERSE);
	}
	else {
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_RIGHT);
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_RIGHT_INVERSE);
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_NEAR_INVERSE);
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_NEAR);
	}
}

static void solveBottomEdges(RotationList & solution, RubiksState & rubiks) {
	const unsigned int COUNT = 4;
	EdgePosition edgesPos[COUNT] = {P_BOTTOM_LEFT, P_BOTTOM_RIGHT, P_BOTTOM_NEAR, P_BOTTOM_FAR};
	
	adjustBottomEdgesOrientation(solution, rubiks, edgesPos, COUNT);
	adjustBottomEdgesPositions(solution, rubiks, edgesPos, COUNT);
}

static void adjustBottomEdgesOrientation(RotationList & solution, RubiksState & rubiks, EdgePosition *edgesPos, unsigned int edgesCount) {
	Color bottomColor = FACE_COLOR_MAP[F_BOTTOM];
	const unsigned int MAX_ITERATIONS = 4;
	
	for (unsigned int it = 0; it < MAX_ITERATIONS; ++it) {
		bool adjusted = false;
		
		for (unsigned int i = 0; i < edgesCount; ++i) {
			EdgePosition targetPos = edgesPos[i];
			
			if (rubiks.getEdgeColor(targetPos, F_BOTTOM) != bottomColor) {
				adjusted = true;
				ReferenceRotator referenceRotator(&solution, &rubiks, getEdgePosOtherFace(targetPos, F_BOTTOM), F_BOTTOM);
				referenceRotator.rotate(R_NEAR);
				referenceRotator.rotate(R_RIGHT);
				referenceRotator.rotate(R_TOP);
				referenceRotator.rotate(R_RIGHT_INVERSE);
				referenceRotator.rotate(R_TOP_INVERSE);
				referenceRotator.rotate(R_NEAR_INVERSE);
			}
		}
		
		if (!adjusted)
			break;
	}
	
	// check
	for (unsigned int i = 0; i < edgesCount; ++i) {
		assert(rubiks.getEdgeColor(edgesPos[i], F_BOTTOM) == bottomColor);
	}
}

static void adjustBottomEdgesPositions(RotationList & solution, RubiksState & rubiks, EdgePosition *edgesPos, unsigned int edgesCount) {
	const unsigned int MAX_ITERATIONS = 8;
	for (unsigned int i = 0; i < MAX_ITERATIONS; ++i) {
		unsigned int correctEdges = findBestInititalRotationForFace(solution, rubiks, F_BOTTOM, edgesPos, edgesCount);
		
		assert(correctEdges > 0);
		
		if (correctEdges == 4)
			break;
		
		for (unsigned int j = 0; j < edgesCount; ++j) {
			if (!rubiks.isEdgeCorrect(edgesPos[j])) {
				switchBottomEdgePosition(solution, rubiks, edgesPos[j]);
				break;
			}
		}
	}
}

static void switchBottomEdgePosition(RotationList & solution, RubiksState & rubiks, EdgePosition edge) {
	ReferenceRotator referenceRotator(&solution, &rubiks, getEdgePosOtherFace(edge, F_BOTTOM), F_BOTTOM);
	referenceRotator.rotate(R_RIGHT);
	referenceRotator.rotate(R_TOP);
	referenceRotator.rotate(R_RIGHT_INVERSE);
	referenceRotator.rotate(R_TOP);
	referenceRotator.rotate(R_RIGHT);
	referenceRotator.rotate(R_TOP);
	referenceRotator.rotate(R_TOP);
	referenceRotator.rotate(R_RIGHT_INVERSE);
	referenceRotator.rotate(R_TOP);
}

static void solveBottomCorners(RotationList & solution, RubiksState & rubiks) {
	const unsigned int COUNT = 4;
	CornerPosition cornersPos[COUNT] = {P_BOTTOM_LEFT_NEAR, P_BOTTOM_RIGHT_NEAR, P_BOTTOM_LEFT_FAR, P_BOTTOM_RIGHT_FAR};
	
	adjustBottomCornersPositions(solution, rubiks, cornersPos, COUNT);
	adjustBottomCornersOrientations(solution, rubiks, cornersPos, COUNT);
}

static void adjustBottomCornersPositions(RotationList & solution, RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount) {
	Face pivot = F_NEAR;
	bool pivotFound = findPivotFaceForBottomCornersPositionAdjust(rubiks, cornersPos, cornersCount, &pivot);
	
	const unsigned int MAX_ITERATIONS = 16;
	unsigned int correctCorners = 0;
	for (unsigned int it = 0; it < MAX_ITERATIONS; ++it) {
		if (!pivotFound)
			pivotFound = findPivotFaceForBottomCornersPositionAdjust(rubiks, cornersPos, cornersCount, &pivot);
		
		correctCorners = 0;
		for (unsigned int i = 0; i < cornersCount; ++i) {
			if (rubiks.isCornerPosCorrect(cornersPos[i]))
				++correctCorners;
		}
		
		if (correctCorners >= cornersCount)
			break;
		
		ReferenceRotator referenceRotator(&solution, &rubiks, pivot, F_BOTTOM);
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_RIGHT);
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_LEFT_INVERSE);
		referenceRotator.rotate(R_TOP);
		referenceRotator.rotate(R_RIGHT_INVERSE);
		referenceRotator.rotate(R_TOP_INVERSE);
		referenceRotator.rotate(R_LEFT);
	}
	
	assert(correctCorners == cornersCount);
}

static bool findPivotFaceForBottomCornersPositionAdjust(RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount, Face *pivot) {
	const unsigned int COUNT = 4;
	Face referenceMap[COUNT] = {F_NEAR, F_RIGHT, F_LEFT, F_FAR};
	
	for (unsigned int i = 0; i < cornersCount; ++i) {
		if (rubiks.isCornerPosCorrect(cornersPos[i])) {
			*pivot = referenceMap[i];
			return true;
		}
	}
	
	return false;
}

static void adjustBottomCornersOrientations(RotationList & solution, RubiksState & rubiks, CornerPosition *cornersPos, unsigned int cornersCount) {
	const unsigned int COUNT = 4;
	Face referenceMap[COUNT] = {F_NEAR, F_RIGHT, F_LEFT, F_FAR};
	const unsigned int MAX_ITERATIONS = 16;
	Color bottomColor = FACE_COLOR_MAP[F_BOTTOM];
	
	Face referenceFace = F_NEAR;
	CornerPosition pivot = cornersPos[0];
	for (unsigned int i = 0; i < cornersCount; ++i) {
		if (!rubiks.isCornerCorrect(cornersPos[i])) {
			pivot = cornersPos[i];
			referenceFace = referenceMap[i];
			break;
		}
	}
	
	ReferenceRotator referenceRotator(&solution, &rubiks, referenceFace, F_BOTTOM);
	
	for (unsigned int i = 0; i < cornersCount; ++i) {
		unsigned int rotations = computeTransformSingleAxis(F_BOTTOM, referenceFace, referenceMap[i]);
		
		RubiksState checkRubiks = rubiks;
		RotationList checkSolution;
		doRotation(checkSolution, checkRubiks, R_BOTTOM_INVERSE, rotations);
		if (checkRubiks.getCornerColor(pivot, F_BOTTOM) == bottomColor)
			continue;
		
		doRotation(solution, rubiks, R_BOTTOM_INVERSE, rotations);
		
		for (unsigned int it = 0; it < MAX_ITERATIONS && rubiks.getCornerColor(pivot, F_BOTTOM) != bottomColor; ++it) {
			referenceRotator.rotate(R_RIGHT_INVERSE);
			referenceRotator.rotate(R_BOTTOM_INVERSE);
			referenceRotator.rotate(R_RIGHT);
			referenceRotator.rotate(R_BOTTOM);
		}
		
		doRotation(solution, rubiks, R_BOTTOM, rotations);
		
		assert(rubiks.isCornerCorrect(cornersPos[i]));
	}
}

// return the number of correct edges
static unsigned int findBestInititalRotationForFace(RotationList & solution, RubiksState & rubiks, Face face, const EdgePosition *edgesPos, unsigned int edgesCount) {
	unsigned int bestRotationCount = 0;
	unsigned int bestTopCorrectEdges = 0;
	
	Rotation rotation = (Rotation) face;
	
	RubiksState rotatedRubiks = rubiks;
	for (unsigned int i = 0; i < 4; ++i) {
		unsigned int topCorrectEdges = 0;
		
		for (unsigned int j = 0; j < edgesCount; ++j) {
			if (rotatedRubiks.isEdgePosCorrect(edgesPos[j]))
				++topCorrectEdges;
		}
		
		if (topCorrectEdges > bestTopCorrectEdges) {
			bestTopCorrectEdges = topCorrectEdges;
			bestRotationCount = i;
		}
		
		rotatedRubiks = rotatedRubiks.rotate(rotation);
	}
	
	doRotation(solution, rubiks, rotation, bestRotationCount);
	
	return bestTopCorrectEdges;
}

static void doRotation(RotationList & solution, RubiksState & rubiks, Rotation rotation) {
	solution.push_back(rotation);
	rubiks = rubiks.rotate(rotation);
}

static void doRotation(RotationList & solution, RubiksState & rubiks, Rotation rotation, unsigned int count) {
	count = count % 4;
	if (count == 3)
		doRotation(solution, rubiks, INVERSE_ROTATION[rotation]);
	else {
		for (unsigned int i = 0; i < count; ++i)
			doRotation(solution, rubiks, rotation);
	}
}
