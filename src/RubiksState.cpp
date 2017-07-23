#include "RubiksState.h"

#include "Util.h"

#include <cassert>
#include <cstdlib>


RubiksState::RubiksState() {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		rubiks[f][1][1] = FACE_COLOR_MAP[f];
	}
}

bool RubiksState::isComplete() const {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		Color c = FACE_COLOR_MAP[f];
		
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (rubiks[f][i][j] != c) return false;
			}
		}
	}
	
	return true;
}

Edge RubiksState::getEdge(EdgePosition edgePos) const {
	switch (edgePos) {
		case P_TOP_LEFT:
			return (Edge) (rubiks[F_TOP][1][0] | rubiks[F_LEFT][0][1]);
		case P_TOP_RIGHT:
			return (Edge) (rubiks[F_TOP][1][2] | rubiks[F_RIGHT][0][1]);
		case P_TOP_NEAR:
			return (Edge) (rubiks[F_TOP][2][1] | rubiks[F_NEAR][0][1]);
		case P_TOP_FAR:
			return (Edge) (rubiks[F_TOP][0][1] | rubiks[F_FAR][0][1]);
	
		case P_LEFT_NEAR:
			return (Edge) (rubiks[F_LEFT][1][2] | rubiks[F_NEAR][1][0]);
		case P_RIGHT_NEAR:
			return (Edge) (rubiks[F_RIGHT][1][0] | rubiks[F_NEAR][1][2]);
		case P_RIGHT_FAR:
			return (Edge) (rubiks[F_RIGHT][1][2] | rubiks[F_FAR][1][0]);
		case P_LEFT_FAR:
			return (Edge) (rubiks[F_LEFT][1][0] | rubiks[F_FAR][1][2]);
	
		case P_BOTTOM_LEFT:
			return (Edge) (rubiks[F_BOTTOM][1][0] | rubiks[F_LEFT][2][1]);
		case P_BOTTOM_RIGHT:
			return (Edge) (rubiks[F_BOTTOM][1][2] | rubiks[F_RIGHT][2][1]);
		case P_BOTTOM_NEAR:
			return (Edge) (rubiks[F_BOTTOM][0][1] | rubiks[F_NEAR][2][1]);
		case P_BOTTOM_FAR:
			return (Edge) (rubiks[F_BOTTOM][2][1] | rubiks[F_FAR][2][1]);
	}
	
	abort();
}

Corner RubiksState::getCorner(CornerPosition cornerPos) const {
	switch (cornerPos) {
		case P_TOP_LEFT_NEAR:
			return (Corner) (rubiks[F_TOP][2][0] | rubiks[F_LEFT][0][2] | rubiks[F_NEAR][0][0]);
		case P_TOP_RIGHT_NEAR:
			return (Corner) (rubiks[F_TOP][2][2] | rubiks[F_RIGHT][0][0] | rubiks[F_NEAR][0][2]);
		case P_TOP_LEFT_FAR:
			return (Corner) (rubiks[F_TOP][0][0] | rubiks[F_LEFT][0][0] | rubiks[F_FAR][0][2]);
		case P_TOP_RIGHT_FAR:
			return (Corner) (rubiks[F_TOP][0][2] | rubiks[F_RIGHT][0][2] | rubiks[F_FAR][0][0]);
	
		case P_BOTTOM_LEFT_NEAR:
			return (Corner) (rubiks[F_BOTTOM][0][0] | rubiks[F_LEFT][2][2] | rubiks[F_NEAR][2][0]);
		case P_BOTTOM_RIGHT_NEAR:
			return (Corner) (rubiks[F_BOTTOM][0][2] | rubiks[F_RIGHT][2][0] | rubiks[F_NEAR][2][2]);
		case P_BOTTOM_LEFT_FAR:
			return (Corner) (rubiks[F_BOTTOM][2][0] | rubiks[F_LEFT][2][0] | rubiks[F_FAR][2][2]);
		case P_BOTTOM_RIGHT_FAR:
			return (Corner) (rubiks[F_BOTTOM][2][2] | rubiks[F_RIGHT][2][2] | rubiks[F_FAR][2][0]);
	}
	
	abort();
}

EdgePosition RubiksState::getEdgePosition(Edge edge) const {
	for (unsigned int i = 0; i < EDGE_COUNT; ++i) {
		if (getEdge((EdgePosition) i) == edge)
			return (EdgePosition) i;
	}
	
	abort();
}

CornerPosition RubiksState::getCornerPosition(Corner corner) const {
	for (unsigned int i = 0; i < CORNER_COUNT; ++i) {
		if (getCorner((CornerPosition) i) == corner)
			return (CornerPosition) i;
	}
	
	abort();
}

Color RubiksState::getEdgeColor(EdgePosition edgePos, Face face) const {
	switch (edgePos) {
		case P_TOP_LEFT:
			return face == F_TOP ? rubiks[F_TOP][1][0] : rubiks[F_LEFT][0][1];
		case P_TOP_RIGHT:
			return face == F_TOP ? rubiks[F_TOP][1][2] : rubiks[F_RIGHT][0][1];
		case P_TOP_NEAR:
			return face == F_TOP ? rubiks[F_TOP][2][1] : rubiks[F_NEAR][0][1];
		case P_TOP_FAR:
			return face == F_TOP ? rubiks[F_TOP][0][1] : rubiks[F_FAR][0][1];
	
		case P_LEFT_NEAR:
			return face == F_LEFT ? rubiks[F_LEFT][1][2] : rubiks[F_NEAR][1][0];
		case P_RIGHT_NEAR:
			return face == F_RIGHT ? rubiks[F_RIGHT][1][0] : rubiks[F_NEAR][1][2];
		case P_RIGHT_FAR:
			return face == F_RIGHT ? rubiks[F_RIGHT][1][2] : rubiks[F_FAR][1][0];
		case P_LEFT_FAR:
			return face == F_LEFT ? rubiks[F_LEFT][1][0] : rubiks[F_FAR][1][2];
	
		case P_BOTTOM_LEFT:
			return face == F_BOTTOM ? rubiks[F_BOTTOM][1][0] : rubiks[F_LEFT][2][1];
		case P_BOTTOM_RIGHT:
			return face == F_BOTTOM ? rubiks[F_BOTTOM][1][2] : rubiks[F_RIGHT][2][1];
		case P_BOTTOM_NEAR:
			return face == F_BOTTOM ? rubiks[F_BOTTOM][0][1] : rubiks[F_NEAR][2][1];
		case P_BOTTOM_FAR:
			return face == F_BOTTOM ? rubiks[F_BOTTOM][2][1] : rubiks[F_FAR][2][1];
	}
	
	abort();
}

Color RubiksState::getCornerColor(CornerPosition cornerPos, Face face) const {
	switch (cornerPos) {
		case P_TOP_LEFT_NEAR:
			switch (face) {
				case F_TOP: return rubiks[F_TOP][2][0];
				case F_LEFT: return rubiks[F_LEFT][0][2];
				case F_NEAR: return rubiks[F_NEAR][0][0];
				default: abort();
			}
		case P_TOP_RIGHT_NEAR:
			switch (face) {
				case F_TOP: return rubiks[F_TOP][2][2];
				case F_RIGHT: return rubiks[F_RIGHT][0][0];
				case F_NEAR: return rubiks[F_NEAR][0][2];
				default: abort();
			}
		case P_TOP_LEFT_FAR:
			switch (face) {
				case F_TOP: return rubiks[F_TOP][0][0];
				case F_LEFT: return rubiks[F_LEFT][0][0];
				case F_FAR: return rubiks[F_FAR][0][2];
				default: abort();
			}
		case P_TOP_RIGHT_FAR:
			switch (face) {
				case F_TOP: return rubiks[F_TOP][0][2];
				case F_RIGHT: return rubiks[F_RIGHT][0][2];
				case F_FAR: return rubiks[F_FAR][0][0];
				default: abort();
			}
	
		case P_BOTTOM_LEFT_NEAR:
			switch (face) {
				case F_BOTTOM: return rubiks[F_BOTTOM][0][0];
				case F_LEFT: return rubiks[F_LEFT][2][2];
				case F_NEAR: return rubiks[F_NEAR][2][0];
				default: abort();
			}
		case P_BOTTOM_RIGHT_NEAR:
			switch (face) {
				case F_BOTTOM: return rubiks[F_BOTTOM][0][2];
				case F_RIGHT: return rubiks[F_RIGHT][2][0];
				case F_NEAR: return rubiks[F_NEAR][2][2];
				default: abort();
			}
		case P_BOTTOM_LEFT_FAR:
			switch (face) {
				case F_BOTTOM: return rubiks[F_BOTTOM][2][0];
				case F_LEFT: return rubiks[F_LEFT][2][0];
				case F_FAR: return rubiks[F_FAR][2][2];
				default: abort();
			}
		case P_BOTTOM_RIGHT_FAR:
			switch (face) {
				case F_BOTTOM: return rubiks[F_BOTTOM][2][2];
				case F_RIGHT: return rubiks[F_RIGHT][2][2];
				case F_FAR: return rubiks[F_FAR][2][0];
				default: abort();
			}
	}
	
	abort();
}

// check position and orientation
bool RubiksState::isEdgeCorrect(EdgePosition pos) const {
	switch (pos) {
		case P_TOP_LEFT:
			return rubiks[F_TOP][1][0] == FACE_COLOR_MAP[F_TOP] && rubiks[F_LEFT][0][1] == FACE_COLOR_MAP[F_LEFT];
		case P_TOP_RIGHT:
			return rubiks[F_TOP][1][2] == FACE_COLOR_MAP[F_TOP] && rubiks[F_RIGHT][0][1] == FACE_COLOR_MAP[F_RIGHT];
		case P_TOP_NEAR:
			return rubiks[F_TOP][2][1] == FACE_COLOR_MAP[F_TOP] && rubiks[F_NEAR][0][1] == FACE_COLOR_MAP[F_NEAR];
		case P_TOP_FAR:
			return rubiks[F_TOP][0][1] == FACE_COLOR_MAP[F_TOP] && rubiks[F_FAR][0][1] == FACE_COLOR_MAP[F_FAR];
	
		case P_LEFT_NEAR:
			return rubiks[F_LEFT][1][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][1][0] == FACE_COLOR_MAP[F_NEAR];
		case P_RIGHT_NEAR:
			return rubiks[F_RIGHT][1][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][1][2] == FACE_COLOR_MAP[F_NEAR];
		case P_RIGHT_FAR:
			return rubiks[F_RIGHT][1][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][1][0] == FACE_COLOR_MAP[F_FAR];
		case P_LEFT_FAR:
			return rubiks[F_LEFT][1][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][1][2] == FACE_COLOR_MAP[F_FAR];
	
		case P_BOTTOM_LEFT:
			return rubiks[F_BOTTOM][1][0] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_LEFT][2][1] == FACE_COLOR_MAP[F_LEFT];
		case P_BOTTOM_RIGHT:
			return rubiks[F_BOTTOM][1][2] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_RIGHT][2][1] == FACE_COLOR_MAP[F_RIGHT];
		case P_BOTTOM_NEAR:
			return rubiks[F_BOTTOM][0][1] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_NEAR][2][1] == FACE_COLOR_MAP[F_NEAR];
		case P_BOTTOM_FAR:
			return rubiks[F_BOTTOM][2][1] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_FAR][2][1] == FACE_COLOR_MAP[F_FAR];
	}
	
	abort();
}

// check only position
bool RubiksState::isEdgePosCorrect(EdgePosition pos) const {
	return getEdge(pos) == EDGE_FROM_POS_MAP[pos];
}

// check position and orientation
bool RubiksState::isCornerCorrect(CornerPosition pos) const {
	switch (pos) {
		case P_TOP_LEFT_NEAR:
			return rubiks[F_TOP][2][0] == FACE_COLOR_MAP[F_TOP] && rubiks[F_LEFT][0][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][0][0] == FACE_COLOR_MAP[F_NEAR];
		case P_TOP_RIGHT_NEAR:
			return rubiks[F_TOP][2][2] == FACE_COLOR_MAP[F_TOP] && rubiks[F_RIGHT][0][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][0][2] == FACE_COLOR_MAP[F_NEAR];
		case P_TOP_LEFT_FAR:
			return rubiks[F_TOP][0][0] == FACE_COLOR_MAP[F_TOP] && rubiks[F_LEFT][0][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][0][2] == FACE_COLOR_MAP[F_FAR];
		case P_TOP_RIGHT_FAR:
			return rubiks[F_TOP][0][2] == FACE_COLOR_MAP[F_TOP] && rubiks[F_RIGHT][0][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][0][0] == FACE_COLOR_MAP[F_FAR];
	
		case P_BOTTOM_LEFT_NEAR:
			return rubiks[F_BOTTOM][0][0] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_LEFT][2][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][2][0] == FACE_COLOR_MAP[F_NEAR];
		case P_BOTTOM_RIGHT_NEAR:
			return rubiks[F_BOTTOM][0][2] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_RIGHT][2][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][2][2] == FACE_COLOR_MAP[F_NEAR];
		case P_BOTTOM_LEFT_FAR:
			return rubiks[F_BOTTOM][2][0] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_LEFT][2][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][2][2] == FACE_COLOR_MAP[F_FAR];
		case P_BOTTOM_RIGHT_FAR:
			return rubiks[F_BOTTOM][2][2] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_RIGHT][2][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][2][0] == FACE_COLOR_MAP[F_FAR];
	}
	
	abort();
}

// check only position
bool RubiksState::isCornerPosCorrect(CornerPosition pos) const {
	return getCorner(pos) == CORNER_FROM_POS_MAP[pos];
}

unsigned int RubiksState::heuristicDist() const {
	unsigned int dist = 720;
	
	if (rubiks[F_TOP][2][0] == rubiks[F_TOP][2][1] && rubiks[F_NEAR][0][0] == rubiks[F_NEAR][0][1]) dist -= 10;
	if (rubiks[F_TOP][2][1] == rubiks[F_TOP][2][2] && rubiks[F_NEAR][0][1] == rubiks[F_NEAR][0][2]) dist -= 10;
	
	if (rubiks[F_TOP][0][0] == rubiks[F_TOP][1][0] && rubiks[F_LEFT][0][0] == rubiks[F_LEFT][0][1]) dist -= 10;
	if (rubiks[F_TOP][1][0] == rubiks[F_TOP][2][0] && rubiks[F_LEFT][0][1] == rubiks[F_LEFT][0][2]) dist -= 10;
	
	if (rubiks[F_TOP][0][2] == rubiks[F_TOP][1][2] && rubiks[F_RIGHT][0][2] == rubiks[F_RIGHT][0][1]) dist -= 10;
	if (rubiks[F_TOP][1][2] == rubiks[F_TOP][2][2] && rubiks[F_RIGHT][0][1] == rubiks[F_RIGHT][0][0]) dist -= 10;
	
	if (rubiks[F_TOP][0][0] == rubiks[F_TOP][0][1] && rubiks[F_FAR][0][2] == rubiks[F_FAR][0][1]) dist -= 10;
	if (rubiks[F_TOP][0][1] == rubiks[F_TOP][0][2] && rubiks[F_FAR][0][1] == rubiks[F_FAR][0][0]) dist -= 10;
	
	if (rubiks[F_BOTTOM][0][0] == rubiks[F_BOTTOM][0][1] && rubiks[F_NEAR][2][0] == rubiks[F_NEAR][2][1]) dist -= 10;
	if (rubiks[F_BOTTOM][0][1] == rubiks[F_BOTTOM][0][2] && rubiks[F_NEAR][2][1] == rubiks[F_NEAR][2][2]) dist -= 10;
	
	if (rubiks[F_BOTTOM][0][0] == rubiks[F_BOTTOM][1][0] && rubiks[F_LEFT][2][2] == rubiks[F_LEFT][2][1]) dist -= 10;
	if (rubiks[F_BOTTOM][1][0] == rubiks[F_BOTTOM][2][0] && rubiks[F_LEFT][2][1] == rubiks[F_LEFT][2][0]) dist -= 10;
	
	if (rubiks[F_BOTTOM][0][2] == rubiks[F_BOTTOM][1][2] && rubiks[F_RIGHT][2][0] == rubiks[F_RIGHT][2][1]) dist -= 10;
	if (rubiks[F_BOTTOM][1][2] == rubiks[F_BOTTOM][2][2] && rubiks[F_RIGHT][2][1] == rubiks[F_RIGHT][2][2]) dist -= 10;
	
	Face sequence[4] = {F_NEAR, F_RIGHT, F_FAR, F_LEFT};
	for (unsigned int i = 0; i < 4; ++i) {
		Face f1 = sequence[i];
		Face f2 = sequence[(i + 3) % 4];
		
		if (rubiks[f1][0][0] == rubiks[f1][1][0] && rubiks[f2][0][2] == rubiks[f2][1][2]) dist -= 10;
		if (rubiks[f1][1][0] == rubiks[f1][2][0] && rubiks[f2][1][2] == rubiks[f2][2][2]) dist -= 10;
	}
	
	// middle
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		if (rubiks[f][0][1] == rubiks[f][1][1]) dist -= 10;
		if (rubiks[f][1][2] == rubiks[f][1][1]) dist -= 10;
		if (rubiks[f][2][1] == rubiks[f][1][1]) dist -= 10;
	}
	
	assert(dist <= 720);
	return dist;
}

/*unsigned int RubiksState::heuristicDist() const {
	unsigned int dist = 720;
	
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (j < 2) {
					if (rubiks[f][i][j] == rubiks[f][i][j+1])
						dist -= 10;
				}
				
				if (i < 2) {
					if (rubiks[f][i][j] == rubiks[f][i+1][j])
						dist -= 10;
				}
			}
		}
	}
	
	assert(dist <= 720);
	return dist;
}*/

/*unsigned int RubiksState::heuristicDist() const {
	unsigned int dist = 1000;
	
	// check corners
	if (rubiks[F_LEFT][0][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][0][2] == FACE_COLOR_MAP[F_FAR] && rubiks[F_TOP][0][0] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_LEFT][0][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][0][0] == FACE_COLOR_MAP[F_NEAR] && rubiks[F_TOP][2][0] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_LEFT][2][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][2][2] == FACE_COLOR_MAP[F_FAR] && rubiks[F_BOTTOM][2][0] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	if (rubiks[F_LEFT][2][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][2][0] == FACE_COLOR_MAP[F_NEAR] && rubiks[F_BOTTOM][0][0] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	
	if (rubiks[F_RIGHT][0][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][0][2] == FACE_COLOR_MAP[F_NEAR] && rubiks[F_TOP][2][2] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_RIGHT][0][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][0][0] == FACE_COLOR_MAP[F_FAR] && rubiks[F_TOP][0][2] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_RIGHT][2][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][2][2] == FACE_COLOR_MAP[F_NEAR] && rubiks[F_BOTTOM][0][2] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	if (rubiks[F_RIGHT][2][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][2][0] == FACE_COLOR_MAP[F_FAR] && rubiks[F_BOTTOM][2][2] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	
	// check edges
	if (rubiks[F_LEFT][0][1] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_TOP][1][0] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_LEFT][1][0] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_FAR][1][2] == FACE_COLOR_MAP[F_FAR]) dist -= 50;
	if (rubiks[F_LEFT][1][2] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_NEAR][1][0] == FACE_COLOR_MAP[F_NEAR]) dist -= 50;
	if (rubiks[F_LEFT][2][1] == FACE_COLOR_MAP[F_LEFT] && rubiks[F_BOTTOM][1][0] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	
	if (rubiks[F_RIGHT][0][1] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_TOP][1][2] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_RIGHT][1][0] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_NEAR][1][2] == FACE_COLOR_MAP[F_NEAR]) dist -= 50;
	if (rubiks[F_RIGHT][1][2] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_FAR][1][0] == FACE_COLOR_MAP[F_FAR]) dist -= 50;
	if (rubiks[F_RIGHT][2][1] == FACE_COLOR_MAP[F_RIGHT] && rubiks[F_BOTTOM][1][2] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	
	if (rubiks[F_NEAR][0][1] == FACE_COLOR_MAP[F_NEAR] && rubiks[F_TOP][2][1] == FACE_COLOR_MAP[F_TOP]) dist -= 50;
	if (rubiks[F_TOP][0][1] == FACE_COLOR_MAP[F_TOP] && rubiks[F_FAR][0][1] == FACE_COLOR_MAP[F_FAR]) dist -= 50;
	if (rubiks[F_FAR][2][1] == FACE_COLOR_MAP[F_FAR] && rubiks[F_BOTTOM][2][1] == FACE_COLOR_MAP[F_BOTTOM]) dist -= 50;
	if (rubiks[F_BOTTOM][0][1] == FACE_COLOR_MAP[F_BOTTOM] && rubiks[F_NEAR][1][2] == FACE_COLOR_MAP[F_NEAR]) dist -= 50;
	
	return dist;
}*/

/*unsigned int RubiksState::heuristicDist() const {
	unsigned int dist = 1000;
	
	Color topColor = FACE_COLOR_MAP[F_TOP];
	Color bottomColor = FACE_COLOR_MAP[F_BOTTOM];
	Color nearColor = FACE_COLOR_MAP[F_NEAR];
	Color farColor = FACE_COLOR_MAP[F_FAR];
	Color leftColor = FACE_COLOR_MAP[F_LEFT];
	Color rightColor = FACE_COLOR_MAP[F_RIGHT];
	
	// check top face edges
	unsigned int fixed = 0;
	if (rubiks[F_TOP][0][1] == topColor && rubiks[F_FAR][0][1] == farColor) ++fixed;
	if (rubiks[F_TOP][1][0] == topColor && rubiks[F_LEFT][0][1] == leftColor) ++fixed;
	if (rubiks[F_TOP][1][2] == topColor && rubiks[F_RIGHT][0][1] == rightColor) ++fixed;
	if (rubiks[F_TOP][2][1] == topColor && rubiks[F_NEAR][0][1] == nearColor) ++fixed;
	
	dist -= fixed * 50;
	if (fixed < 4)
		return dist;
	
	// check top face corners
	fixed = 0;
	if (rubiks[F_TOP][0][0] == topColor && rubiks[F_LEFT][0][0] == leftColor && rubiks[F_FAR][0][2] == farColor) ++fixed;
	if (rubiks[F_TOP][0][2] == topColor && rubiks[F_RIGHT][0][2] == rightColor && rubiks[F_FAR][0][0] == farColor) ++fixed;
	if (rubiks[F_TOP][2][0] == topColor && rubiks[F_LEFT][0][2] == leftColor && rubiks[F_NEAR][0][0] == nearColor) ++fixed;
	if (rubiks[F_TOP][2][2] == topColor && rubiks[F_RIGHT][0][0] == rightColor && rubiks[F_NEAR][0][2] == nearColor) ++fixed;
	
	dist -= fixed * 50;
	if (fixed < 4)
		return dist;
	
	// check middle corners
	fixed = 0;
	if (rubiks[F_NEAR][1][0] == nearColor && rubiks[F_LEFT][1][2] == leftColor) ++fixed;
	if (rubiks[F_NEAR][1][2] == nearColor && rubiks[F_RIGHT][1][0] == rightColor) ++fixed;
	if (rubiks[F_FAR][1][0] == farColor && rubiks[F_RIGHT][1][2] == rightColor) ++fixed;
	if (rubiks[F_FAR][1][2] == farColor && rubiks[F_LEFT][1][0] == leftColor) ++fixed;
	
	dist -= fixed * 50;
	if (fixed < 4)
		return dist;
	
	// check bottom edges
	fixed = 0;
	if (rubiks[F_NEAR][2][1] == nearColor && rubiks[F_BOTTOM][0][1] == bottomColor) ++fixed;
	if (rubiks[F_LEFT][2][1] == leftColor && rubiks[F_BOTTOM][1][0] == bottomColor) ++fixed;
	if (rubiks[F_RIGHT][2][1] == rightColor && rubiks[F_BOTTOM][1][2] == bottomColor) ++fixed;
	if (rubiks[F_FAR][2][1] == farColor && rubiks[F_BOTTOM][2][1] == bottomColor) ++fixed;
	
	dist -= fixed * 50;
	if (fixed < 4)
		return dist;
	
	// check bottom corners
	fixed = 0;
	if (rubiks[F_BOTTOM][0][0] == bottomColor && rubiks[F_NEAR][2][0] == nearColor && rubiks[F_LEFT][2][2] == leftColor) ++fixed;
	if (rubiks[F_BOTTOM][0][2] == bottomColor && rubiks[F_NEAR][2][2] == nearColor && rubiks[F_RIGHT][2][0] == rightColor) ++fixed;
	if (rubiks[F_BOTTOM][2][0] == bottomColor && rubiks[F_FAR][2][2] == farColor && rubiks[F_LEFT][2][0] == leftColor) ++fixed;
	if (rubiks[F_BOTTOM][2][2] == bottomColor && rubiks[F_FAR][2][0] == farColor && rubiks[F_RIGHT][2][2] == rightColor) ++fixed;
	
	dist -= fixed * 50;
	
	if (dist > 1000)
		abort();
	
	return dist;
}*/

void RubiksState::setColor(Color c, Face f, unsigned int i, unsigned int j) {
	rubiks[f][i][j] = c;
}

RubiksState RubiksState::rotate(Rotation r, unsigned int times) const {
	RubiksState state = *this;
	
	for (unsigned int i = 0; i < times; ++i)
		state = rotate(r);
	
	return state;
}

RubiksState RubiksState::rotate(Rotation r) const {
	switch (r) {
		case R_LEFT: return rotateLeft();
		case R_RIGHT: return rotateRight();
		case R_TOP:  return rotateTop();
		case R_BOTTOM: return rotateBottom();
		case R_NEAR: return rotateNear();
		case R_FAR: return rotateFar();
		
		case R_LEFT_INVERSE: return rotateLeftInverse();
		case R_RIGHT_INVERSE: return rotateRightInverse();
		case R_TOP_INVERSE: return rotateTopInverse();
		case R_BOTTOM_INVERSE: return rotateBottomInverse();
		case R_NEAR_INVERSE: return rotateNearInverse();
		case R_FAR_INVERSE: return rotateFarInverse();
		default:
			abort();
	}
}

RubiksState RubiksState::rotateLeft() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_LEFT);
	
	for (unsigned int i = 0; i < 3; ++i) {
		ns.rubiks[F_TOP][i][0] = rubiks[F_FAR][2 - i][2];
		ns.rubiks[F_NEAR][i][0] = rubiks[F_TOP][i][0];
		ns.rubiks[F_BOTTOM][i][0] = rubiks[F_NEAR][i][0];
		ns.rubiks[F_FAR][i][2] = rubiks[F_BOTTOM][2 - i][0];
	}
	
	return ns;
}

RubiksState RubiksState::rotateRight() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_RIGHT);
	
	for (unsigned int i = 0; i < 3; ++i) {
		ns.rubiks[F_FAR][2 - i][0] = rubiks[F_TOP][i][2];
		ns.rubiks[F_TOP][i][2] = rubiks[F_NEAR][i][2];
		ns.rubiks[F_NEAR][i][2] = rubiks[F_BOTTOM][i][2];
		ns.rubiks[F_BOTTOM][2 - i][2] = rubiks[F_FAR][i][0];
	}
	
	return ns;
}

RubiksState RubiksState::rotateTop() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_TOP);
	
	for (unsigned int j = 0; j < 3; ++j) {
		ns.rubiks[F_NEAR][0][j] = rubiks[F_RIGHT][0][j];
		ns.rubiks[F_RIGHT][0][j] = rubiks[F_FAR][0][j];
		ns.rubiks[F_FAR][0][j] = rubiks[F_LEFT][0][j];
		ns.rubiks[F_LEFT][0][j] = rubiks[F_NEAR][0][j];
	}
	
	return ns;
}

RubiksState RubiksState::rotateBottom() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_BOTTOM);
	
	for (unsigned int j = 0; j < 3; ++j) {
		ns.rubiks[F_RIGHT][2][j] = rubiks[F_NEAR][2][j];
		ns.rubiks[F_FAR][2][j] = rubiks[F_RIGHT][2][j];
		ns.rubiks[F_LEFT][2][j] = rubiks[F_FAR][2][j];
		ns.rubiks[F_NEAR][2][j] = rubiks[F_LEFT][2][j];
	}
	
	return ns;
}

RubiksState RubiksState::rotateNear() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_NEAR);
	
	for (unsigned int k = 0; k < 3; ++k) {
		ns.rubiks[F_TOP][2][k] = rubiks[F_LEFT][2 - k][2];
		ns.rubiks[F_RIGHT][k][0] = rubiks[F_TOP][2][k];
		ns.rubiks[F_BOTTOM][0][k] = rubiks[F_RIGHT][2 - k][0];
		ns.rubiks[F_LEFT][k][2] = rubiks[F_BOTTOM][0][k];
	}
	
	return ns;
}

RubiksState RubiksState::rotateFar() const {
	RubiksState ns = *this;
	
	rotateFaceOnly(ns, F_FAR);
	
	for (unsigned int k = 0; k < 3; ++k) {
		ns.rubiks[F_LEFT][2 - k][0] = rubiks[F_TOP][0][k];
		ns.rubiks[F_TOP][0][k] = rubiks[F_RIGHT][k][2];
		ns.rubiks[F_RIGHT][2 - k][2] = rubiks[F_BOTTOM][2][k];
		ns.rubiks[F_BOTTOM][2][k] = rubiks[F_LEFT][k][0];
	}
	
	return ns;
}

RubiksState RubiksState::rotateLeftInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_LEFT);
	
	for (unsigned int i = 0; i < 3; ++i) {
		ns.rubiks[F_FAR][2 - i][2] = rubiks[F_TOP][i][0];
		ns.rubiks[F_TOP][i][0] = rubiks[F_NEAR][i][0];
		ns.rubiks[F_NEAR][i][0] = rubiks[F_BOTTOM][i][0];
		ns.rubiks[F_BOTTOM][2 - i][0] = rubiks[F_FAR][i][2];
	}
	
	return ns;
}

RubiksState RubiksState::rotateRightInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_RIGHT);
	
	for (unsigned int i = 0; i < 3; ++i) {
		ns.rubiks[F_TOP][i][2] = rubiks[F_FAR][2 - i][0];
		ns.rubiks[F_NEAR][i][2] = rubiks[F_TOP][i][2];
		ns.rubiks[F_BOTTOM][i][2] = rubiks[F_NEAR][i][2];
		ns.rubiks[F_FAR][i][0] = rubiks[F_BOTTOM][2 - i][2];
	}
	
	return ns;
}

RubiksState RubiksState::rotateTopInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_TOP);
	
	for (unsigned int j = 0; j < 3; ++j) {
		ns.rubiks[F_RIGHT][0][j] = rubiks[F_NEAR][0][j];
		ns.rubiks[F_FAR][0][j] = rubiks[F_RIGHT][0][j];
		ns.rubiks[F_LEFT][0][j] = rubiks[F_FAR][0][j];
		ns.rubiks[F_NEAR][0][j] = rubiks[F_LEFT][0][j];
	}
	
	return ns;
}

RubiksState RubiksState::rotateBottomInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_BOTTOM);
	
	for (unsigned int j = 0; j < 3; ++j) {
		ns.rubiks[F_NEAR][2][j] = rubiks[F_RIGHT][2][j];
		ns.rubiks[F_RIGHT][2][j] = rubiks[F_FAR][2][j];
		ns.rubiks[F_FAR][2][j] = rubiks[F_LEFT][2][j];
		ns.rubiks[F_LEFT][2][j] = rubiks[F_NEAR][2][j];
	}
	
	return ns;
}

RubiksState RubiksState::rotateNearInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_NEAR);
	
	for (unsigned int k = 0; k < 3; ++k) {
		ns.rubiks[F_LEFT][2 - k][2] = rubiks[F_TOP][2][k];
		ns.rubiks[F_TOP][2][k] = rubiks[F_RIGHT][k][0];
		ns.rubiks[F_RIGHT][2 - k][0] = rubiks[F_BOTTOM][0][k];
		ns.rubiks[F_BOTTOM][0][k] = rubiks[F_LEFT][k][2];
	}
	
	return ns;
}

RubiksState RubiksState::rotateFarInverse() const {
	RubiksState ns = *this;
	
	rotateInverseFaceOnly(ns, F_FAR);
	
	for (unsigned int k = 0; k < 3; ++k) {
		ns.rubiks[F_TOP][0][k] = rubiks[F_LEFT][2 - k][0];
		ns.rubiks[F_RIGHT][k][2] = rubiks[F_TOP][0][k];
		ns.rubiks[F_BOTTOM][2][k] = rubiks[F_RIGHT][2 - k][2];
		ns.rubiks[F_LEFT][k][0] = rubiks[F_BOTTOM][2][k];
	}
	
	return ns;
}

inline void RubiksState::rotateFaceOnly(RubiksState & ns, Face f) const {
	ns.rubiks[f][0][0] = rubiks[f][2][0];
	ns.rubiks[f][0][1] = rubiks[f][1][0];
	ns.rubiks[f][0][2] = rubiks[f][0][0];
	
	ns.rubiks[f][1][0] = rubiks[f][2][1];
	ns.rubiks[f][1][2] = rubiks[f][0][1];
	
	ns.rubiks[f][2][0] = rubiks[f][2][2];
	ns.rubiks[f][2][1] = rubiks[f][1][2];
	ns.rubiks[f][2][2] = rubiks[f][0][2];
}

inline void RubiksState::rotateInverseFaceOnly(RubiksState & ns, Face f) const {
	ns.rubiks[f][2][0] = rubiks[f][0][0];
	ns.rubiks[f][1][0] = rubiks[f][0][1];
	ns.rubiks[f][0][0] = rubiks[f][0][2];
	
	ns.rubiks[f][2][1] = rubiks[f][1][0];
	ns.rubiks[f][0][1] = rubiks[f][1][2];
	
	ns.rubiks[f][2][2] = rubiks[f][2][0];
	ns.rubiks[f][1][2] = rubiks[f][2][1];
	ns.rubiks[f][0][2] = rubiks[f][2][2];
}

bool RubiksState::operator==(const RubiksState & other) const {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (rubiks[f][i][j] != other.rubiks[f][i][j]) return false;
			}
		}
	}
	
	return true;
}

bool RubiksState::operator!=(const RubiksState & other) const {
	return !(*this == other);
}

bool RubiksState::operator<(const RubiksState & other) const {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (rubiks[f][i][j] < other.rubiks[f][i][j]) return true;
			}
		}
	}
	
	return false;
}

std::ostream & operator<<(std::ostream & stream, const RubiksState & state) {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		stream << FACE_COLOR_MAP[f] << " (top " << FACE_COLOR_MAP[TOP_FACE_MAP[f]] << "):" << std::endl;
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				stream << state.rubiks[f][i][j] << ' ';
			}
			stream << std::endl;
		}
		stream << std::endl;
	}
	
	
	return stream;
}
