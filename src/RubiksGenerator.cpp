#include "RubiksGenerator.h"

#include <cassert>
#include <cstdlib>


RubiksState generateCompleteRubiks() {
	RubiksState rubiks;
	
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		for (unsigned int i = 0; i < 3; ++i) {
			for (unsigned int j = 0; j < 3; ++j) {
				if (i != 1 || j != 1)
					rubiks.setColor(FACE_COLOR_MAP[f], (Face) f, i, j);
			}
		}
	}
	
	assert(rubiks.isComplete());
	
	return rubiks;
}

RubiksState generateRandomRubiks(unsigned int randomMoves) {
	RubiksState rubiks = generateCompleteRubiks();
	
	for (unsigned int i = 0; i < randomMoves; ++i) {
		rubiks = rubiks.rotate((Rotation) (rand() % R_COUNT));
	}
	
	return rubiks;
}
