#ifndef SOLVER_DEPTH_H
#define SOLVER_DEPTH_H

#include "Defs.h"

#include <vector>


typedef std::vector<Rotation> RotationList;

class RubiksState;


// return true if the solution was found
bool solveDepth(RotationList & solution, const RubiksState & rubiks);

#endif
