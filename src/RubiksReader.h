#ifndef RUBIKS_READER_H
#define RUBIKS_READER_H

class RubiksState;

void readRubiksFromStdin(RubiksState & rubiks);
void readRubiksFromFile(RubiksState & rubiks, const char *file);

#endif
