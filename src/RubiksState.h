#ifndef RUBIKS_STATE_H
#define RUBIKS_STATE_H

#include "Defs.h"

#include <ostream>


class RubiksState {
public:
	RubiksState();
	
	bool isComplete() const;
	unsigned int heuristicDist() const;
	
	void setColor(Color c, Face f, unsigned int i, unsigned int j);
	
	Edge getEdge(EdgePosition edgePos) const;
	Corner getCorner(CornerPosition cornerPos) const;
	
	EdgePosition getEdgePosition(Edge edge) const;
	CornerPosition getCornerPosition(Corner corner) const;
	
	Color getEdgeColor(EdgePosition edgePos, Face face) const;
	Color getCornerColor(CornerPosition cornerPos, Face face) const;
	
	// check position and orientation
	bool isEdgeCorrect(EdgePosition pos) const;
	
	// check only position
	bool isEdgePosCorrect(EdgePosition pos) const;
	
	// check position and orientation
	bool isCornerCorrect(CornerPosition pos) const;
	
	// check only position
	bool isCornerPosCorrect(CornerPosition pos) const;
	
	RubiksState rotate(Rotation r, unsigned int times) const;
	RubiksState rotate(Rotation r) const;
	
	RubiksState rotateLeft() const;
	RubiksState rotateRight() const;
	RubiksState rotateTop() const;
	RubiksState rotateBottom() const;
	RubiksState rotateNear() const;
	RubiksState rotateFar() const;
	
	RubiksState rotateLeftInverse() const;
	RubiksState rotateRightInverse() const;
	RubiksState rotateTopInverse() const;
	RubiksState rotateBottomInverse() const;
	RubiksState rotateNearInverse() const;
	RubiksState rotateFarInverse() const;
	
	bool operator==(const RubiksState & other) const;
	bool operator!=(const RubiksState & other) const;
	
	// needed for std::map
	bool operator<(const RubiksState & other) const;
	
	friend std::ostream & operator<<(std::ostream & stream, const RubiksState & state);
	
private:
	inline void rotateFaceOnly(RubiksState & ns, Face f) const;
	inline void rotateInverseFaceOnly(RubiksState & ns, Face f) const;
	
	// faces positions are relative as follow blue is top,
	// for blue face, orange is top,
	// for green face red is top
	Color rubiks[F_COUNT][3][3];
};

#endif
