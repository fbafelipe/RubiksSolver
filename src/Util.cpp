#include "Util.h"

#include <cassert>
#include <cstdlib>


static void findSideSequence(Face rotationAxis, Face *sequence);
static void setupFaceSequence(Face *faces, Face f1, Face f2, Face f3, Face f4);
static Rotation faceToRotation(Face face, bool inverse);


Face colorToFace(Color color) {
	switch (color) {
		case C_WHITE:
			return F_LEFT;
		case C_YELLOW:
			return F_RIGHT;
		case C_BLUE:
			return F_TOP;
		case C_GREEN:
			return F_BOTTOM;
		case C_RED:
			return F_NEAR;
		case C_ORANGE:
			return F_FAR;
	}
	
	abort();
}

// faces must have size >= 2
void getEdgePosFaces(EdgePosition pos, Face *faces) {
	switch (pos) {
		case P_TOP_LEFT:
			faces[0] = F_TOP;
			faces[1] = F_LEFT;
			break;
		case P_TOP_RIGHT:
			faces[0] = F_TOP;
			faces[1] = F_RIGHT;
			break;
		case P_TOP_NEAR:
			faces[0] = F_TOP;
			faces[1] = F_NEAR;
			break;
		case P_TOP_FAR:
			faces[0] = F_TOP;
			faces[1] = F_FAR;
			break;
		
		case P_LEFT_NEAR:
			faces[0] = F_LEFT;
			faces[1] = F_NEAR;
			break;
		case P_RIGHT_NEAR:
			faces[0] = F_RIGHT;
			faces[1] = F_NEAR;
			break;
		case P_RIGHT_FAR:
			faces[0] = F_RIGHT;
			faces[1] = F_FAR;
			break;
		case P_LEFT_FAR:
			faces[0] = F_LEFT;
			faces[1] = F_FAR;
			break;
		
		case P_BOTTOM_LEFT:
			faces[0] = F_BOTTOM;
			faces[1] = F_LEFT;
			break;
		case P_BOTTOM_RIGHT:
			faces[0] = F_BOTTOM;
			faces[1] = F_RIGHT;
			break;
		case P_BOTTOM_NEAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_NEAR;
			break;
		case P_BOTTOM_FAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_FAR;
			break;
		default:
			abort();
	}
}

// faces must have size >= 2, faces[0] will contain the face that comes first on the rotation axis
void getEdgePosFacesOrdered(EdgePosition pos, Face *faces, Face rotationAxis) {
	getEdgePosFaces(pos, faces);
	
	unsigned int rotations = computeTransformSingleAxis(rotationAxis, faces[0], faces[1]);
	if (rotations != 1) {
		Face f = faces[0];
		faces[0] = faces[1];
		faces[1] = f;
	}
}

// faces must have size >= 3
void getCornerPosFaces(CornerPosition pos, Face *faces) {
	switch (pos) {
		case P_TOP_LEFT_NEAR:
			faces[0] = F_TOP;
			faces[1] = F_LEFT;
			faces[2] = F_NEAR;
			break;
		case P_TOP_RIGHT_NEAR:
			faces[0] = F_TOP;
			faces[1] = F_RIGHT;
			faces[2] = F_NEAR;
			break;
		case P_TOP_LEFT_FAR:
			faces[0] = F_TOP;
			faces[1] = F_LEFT;
			faces[2] = F_FAR;
			break;
		case P_TOP_RIGHT_FAR:
			faces[0] = F_TOP;
			faces[1] = F_RIGHT;
			faces[2] = F_FAR;
			break;
		
		case P_BOTTOM_LEFT_NEAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_LEFT;
			faces[2] = F_NEAR;
			break;
		case P_BOTTOM_RIGHT_NEAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_RIGHT;
			faces[2] = F_NEAR;
			break;
		case P_BOTTOM_LEFT_FAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_LEFT;
			faces[2] = F_FAR;
			break;
		case P_BOTTOM_RIGHT_FAR:
			faces[0] = F_BOTTOM;
			faces[1] = F_RIGHT;
			faces[2] = F_FAR;
			break;
	}
}

bool edgePosContainFace(EdgePosition pos, Face face) {
	const unsigned int COUNT = 2;
	Face faces[COUNT];
	getEdgePosFaces(pos, faces);
	
	for (unsigned int i = 0; i < COUNT; ++i) {
		if (faces[i] == face)
			return true;
	}
	
	return false;
}

bool cornerPosContainFace(CornerPosition pos, Face face) {
	const unsigned int COUNT = 3;
	Face faces[COUNT];
	getCornerPosFaces(pos, faces);
	
	for (unsigned int i = 0; i < COUNT; ++i) {
		if (faces[i] == face)
			return true;
	}
	
	return false;
}

Face getEdgePosOtherFace(EdgePosition pos, Face face) {
	Face faces[2];
	getEdgePosFaces(pos, faces);
	
	assert(faces[0] == face || faces[1] == face);
	
	return faces[0] == face ? faces[1] : faces[0];
}

Color getEdgeOtherColor(Edge edge, Color color) {
	assert(edge & color);
	return edge & ~color;
}

CornerPosition getCornerOnBottom(CornerPosition cornerPos) {
	switch (cornerPos) {
		case P_TOP_LEFT_NEAR:
			return P_BOTTOM_LEFT_NEAR;
		case P_TOP_RIGHT_NEAR:
			return P_BOTTOM_RIGHT_NEAR;
		case P_TOP_LEFT_FAR:
			return P_BOTTOM_LEFT_FAR;
		case P_TOP_RIGHT_FAR:
			return P_BOTTOM_RIGHT_FAR;
		default:
			abort();
	}
}

unsigned int computeTransformSingleAxis(Face rotationAxis, Face startFace, Face endFace) {
	Face sequence[4];
	findSideSequence(rotationAxis, sequence);
	
	unsigned int startPos = 0;
	for (unsigned int i = 0; i < 4; ++i) {
		if (sequence[i] == startFace) {
			startPos = i;
			break;
		}
	}
	
	for (unsigned int i = 0; i < 4; ++i) {
		if (sequence[(startPos + i) % 4] == endFace)
			return i;
	}
	
	abort();
}

Rotation computeRelativeRotation(Rotation rotation, Face nearFace, Face topFace) {
	bool inverse;
	Face rotationFace;
	if (rotation < (unsigned int) F_COUNT) {
		rotationFace = (Face) rotation;
		inverse = false;
	}
	else {
		rotationFace = (Face) INVERSE_ROTATION[rotation];
		inverse = true;
	}
	
	switch (rotationFace) {
		case F_NEAR:
			return faceToRotation(nearFace, inverse);
		case F_FAR:
			return faceToRotation(OPPOSING_FACE[nearFace], inverse);
		case F_TOP:
			return faceToRotation(topFace, inverse);
		case F_BOTTOM:
			return faceToRotation(OPPOSING_FACE[topFace], inverse);
		case F_LEFT:
		case F_RIGHT:
		{
			const unsigned int COUNT = 4;
			Face sequence[COUNT];
			findSideSequence(nearFace, sequence);
			
			unsigned int topIndex = COUNT;
			for (unsigned int i = 0; i < COUNT; ++i) {
				if (sequence[i] == topFace) {
					topIndex = i;
					break;
				}
			}
			assert(topIndex < COUNT);
			
			unsigned int index = rotationFace == F_LEFT ? (topIndex + COUNT - 1) % COUNT : (topIndex + 1) % COUNT;
			return faceToRotation(sequence[index], inverse);
		}
		default:
			abort();
	}
}

static void findSideSequence(Face rotationAxis, Face *sequence) {
	switch (rotationAxis) {
		case F_LEFT:
			setupFaceSequence(sequence, F_TOP, F_NEAR, F_BOTTOM, F_FAR);
			break;
		case F_RIGHT:
			setupFaceSequence(sequence, F_TOP, F_FAR, F_BOTTOM, F_NEAR);
			break;
		case F_TOP:
			setupFaceSequence(sequence, F_NEAR, F_LEFT, F_FAR, F_RIGHT);
			break;
		case F_BOTTOM:
			setupFaceSequence(sequence, F_NEAR, F_RIGHT, F_FAR, F_LEFT);
			break;
		case F_NEAR:
			setupFaceSequence(sequence, F_TOP, F_RIGHT, F_BOTTOM, F_LEFT);
			break;
		case F_FAR:
			setupFaceSequence(sequence, F_TOP, F_LEFT, F_BOTTOM, F_RIGHT);
			break;
		default:
			abort();
	}
}

static void setupFaceSequence(Face *faces, Face f1, Face f2, Face f3, Face f4) {
	faces[0] = f1;
	faces[1] = f2;
	faces[2] = f3;
	faces[3] = f4;
}

static Rotation faceToRotation(Face face, bool inverse) {
	return inverse ? INVERSE_ROTATION[face] : (Rotation) face;
}

std::ostream & operator<<(std::ostream & stream, Color c) {
	switch (c) {
		case C_WHITE:
			stream << "W";
			break;
		case C_YELLOW:
			stream << "Y";
			break;
		case C_BLUE:
			stream << "B";
			break;
		case C_GREEN:
			stream << "G";
			break;
		case C_RED:
			stream << "R";
			break;
		case C_ORANGE:
			stream << "O";
			break;
		default:
			break;
	}
	
	return stream;
}

std::ostream & operator<<(std::ostream & stream, Rotation r) {
	switch (r) {
		case R_LEFT:
			stream << "L";
			break;
		case R_RIGHT:
			stream << "R";
			break;
		case R_TOP:
			stream << "T";
			break;
		case R_BOTTOM:
			stream << "B";
			break;
		case R_NEAR:
			stream << "N";
			break;
		case R_FAR:
			stream << "F";
			break;

		case R_LEFT_INVERSE:
			stream << "Li";
			break;
		case R_RIGHT_INVERSE:
			stream << "Ri";
			break;
		case R_TOP_INVERSE:
			stream << "Ti";
			break;
		case R_BOTTOM_INVERSE:
			stream << "Bi";
			break;
		case R_NEAR_INVERSE:
			stream << "Ni";
			break;
		case R_FAR_INVERSE:
			stream << "Fi";
			break;
			
		default:
			break;
	}
	
	return stream;
}
