#include "Util.h"


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
