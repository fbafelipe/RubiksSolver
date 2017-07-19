#include "SolutionOptimizer.h"

#include "RubiksState.h"

#include <cassert>


const Face FACE_FROM_ROTATION[R_COUNT] = {
	F_LEFT,
	F_RIGHT,
	F_TOP,
	F_BOTTOM,
	F_NEAR,
	F_FAR,
	
	F_LEFT,
	F_RIGHT,
	F_TOP,
	F_BOTTOM,
	F_NEAR,
	F_FAR
};


static void mergeRotationsSplitByOpposingFaceRotation(RotationList & solution);
static void mergeSameFaceRotations(RotationList & solution);
static int getRotationDirection(Rotation rotation); // 1 for normal, -1 for inverse


void optimizeSolution(RotationList & finalSolution, const RotationList & initialSolution, const RubiksState & rubiksState) {
	finalSolution = initialSolution;
	
	unsigned int solutionSize;
	
	do {
		solutionSize = finalSolution.size();
		
		mergeRotationsSplitByOpposingFaceRotation(finalSolution);
		mergeSameFaceRotations(finalSolution);
	} while(finalSolution.size() < solutionSize);
}

static void mergeRotationsSplitByOpposingFaceRotation(RotationList & solution) {
	for (unsigned int i = 0; i < solution.size(); ++i) {
		Face face = FACE_FROM_ROTATION[solution[i]];
		
		while (i + 1 < solution.size()) {
			if (FACE_FROM_ROTATION[solution[i + 1]] == face)
				++i;
			else
				break;
		}
		
		Face opposingFace = OPPOSING_FACE[face];
		unsigned int opposingFaceCount = 0;
		for (unsigned int j = i + 1; j < solution.size(); ++j) {
			if (FACE_FROM_ROTATION[solution[j]] == face) {
				assert(opposingFaceCount > 0);
				
				++i;
				assert(i != j);
				Rotation r = solution[i];
				solution[i] = solution[j];
				solution[j] = r;
			}
			else if (FACE_FROM_ROTATION[solution[j]] == opposingFace)
				++opposingFaceCount;
			else
				break;
		}
	}
}

static void mergeSameFaceRotations(RotationList & solution) {
	RotationList finalSolution;
	
	for (unsigned int i = 0; i < solution.size(); ++i) {
		Face face = FACE_FROM_ROTATION[solution[i]];
		int rotations = getRotationDirection(solution[i]);
		
		while (i + 1 < solution.size()) {
			if (FACE_FROM_ROTATION[solution[i + 1]] == face) {
				rotations += getRotationDirection(solution[++i]);
			}
			else
				break;
		}
		
		// make positive
		if (rotations < 0)
			rotations += -rotations * 4;
		rotations %= 4;
		
		if (rotations > 0) {
			if (rotations == 3)
				finalSolution.push_back(INVERSE_ROTATION[face]);
			else {
				for (int i = 0; i < rotations; ++i)
					finalSolution.push_back((Rotation) face);
			}
		}
	}
	
	solution = finalSolution;
}

// 1 for normal, -1 for inverse
static int getRotationDirection(Rotation rotation) {
	return ((int) rotation) < F_COUNT ? 1 : -1;
}
