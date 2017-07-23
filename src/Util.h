#ifndef UTIL_H
#define UTIL_H

#include "Defs.h"

#include <stdint.h>
#include <ostream>


uint64_t currentTime();

Face colorToFace(Color color);

void getEdgePosFaces(EdgePosition pos, Face *faces); // faces must have size >= 2
void getEdgePosFacesOrdered(EdgePosition pos, Face *faces, Face rotationAxis); // faces must have size >= 2, faces[0] will contain the face that comes first on the rotation axis
void getCornerPosFaces(CornerPosition pos, Face *faces); // faces must have size >= 3

bool edgePosContainFace(EdgePosition pos, Face face);
bool cornerPosContainFace(CornerPosition pos, Face face);

Face getEdgePosOtherFace(EdgePosition pos, Face face);
Color getEdgeOtherColor(Edge edge, Color color);

CornerPosition getCornerOnBottom(CornerPosition cornerPos);

// rotate edge(rotationAxis, startFace) so it will be on edge(rotationAxis, endFace)
// return number of rotations
unsigned int computeTransformSingleAxis(Face rotationAxis, Face startFace, Face endFace);

// transform a rotation from another reference of near/top axis
Rotation computeRelativeRotation(Rotation rotation, Face nearFace, Face topFace);

std::ostream & operator<<(std::ostream & stream, Color c);

std::ostream & operator<<(std::ostream & stream, Rotation r);

#endif
