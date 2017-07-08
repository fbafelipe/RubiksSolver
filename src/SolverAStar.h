#ifndef SOLVER_ASTAR_H
#define SOLVER_ASTAR_H

#include "Defs.h"

#include <vector>


typedef std::vector<Rotation> RotationList;

class RubiksState;


// return true if the solution was found
bool solveAStar(RotationList & solution, const RubiksState & rubiks);


#endif
