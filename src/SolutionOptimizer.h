#ifndef SOLUTION_OPTIMIZER_H
#define SOLUTION_OPTIMIZER_H

#include "Solver.h"


class RubiksState;


void optimizeSolution(RotationList & finalSolution, const RotationList & initialSolution, const RubiksState & rubiksState);

#endif
