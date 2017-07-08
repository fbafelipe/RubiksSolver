#include "RubiksReader.h"

#include "RubiksState.h"
#include "Util.h"

#include <iostream>


static void readFace(RubiksState & rubiks, Face f);

void readRubiks(RubiksState & rubiks) {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		std::cout << FACE_COLOR_MAP[f] << " (top " << FACE_COLOR_MAP[TOP_FACE_MAP[f]] << "):" << std::endl;
		readFace(rubiks, (Face)f);
	}
}

static void readFace(RubiksState & rubiks, Face f) {
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			
			Color color = C_WHITE;
			char c;
			do {
				std::cout << (i+1) << "," << (j+1) << ": ";
				std::cout.flush();
				std::cin >> c;
				
				switch (c) {
					case 'w':
					case 'W':
						color = C_WHITE;
						break;
					case 'y':
					case 'Y':
						color = C_YELLOW;
						break;
					case 'b':
					case 'B':
						color = C_BLUE;
						break;
					case 'g':
					case 'G':
						color = C_GREEN;
						break;
					case 'r':
					case 'R':
						color = C_RED;
						break;
					case 'o':
					case 'O':
						color = C_ORANGE;
						break;
					default:
						c = '\0';
				}
			} while (!c);
			
			rubiks.setColor(color, f, i, j);
		}
	}
}
