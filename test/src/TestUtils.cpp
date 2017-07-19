#include "TestUtils.h"

#include "RubiksReader.h"


RubiksState readRubiks(const char *file) {
	RubiksState rubiks;
	readRubiksFromFile(rubiks, (std::string("../data/") + file).c_str());
	return rubiks;
}

