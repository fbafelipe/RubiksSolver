#include "RubiksReader.h"

#include "RubiksState.h"
#include "Util.h"

#include <iostream>
#include <cstdio>


class ColorReader {
	public:
		virtual ~ColorReader() {}
		virtual void announceFace(unsigned int faceIndex) = 0;
		virtual char readColor(unsigned int i, unsigned int j) = 0;
};

class StdinColorReader : public ColorReader {
	public:
		void announceFace(unsigned int faceIndex) {
			std::cout << FACE_COLOR_MAP[faceIndex] << " (top " << FACE_COLOR_MAP[TOP_FACE_MAP[faceIndex]] << "):" << std::endl;
		}
		
		char readColor(unsigned int i, unsigned int j) {
			char c;
			std::cout << (i+1) << "," << (j+1) << ": ";
			std::cout.flush();
			std::cin >> c;
			return c;
		}
};


static void readRubiks(ColorReader & colorReader, RubiksState & rubiks);
static void readFace(ColorReader & colorReader, RubiksState & rubiks, Face f);


class FileColorReader : public ColorReader {
	private:
		FILE *fp;
	
	public:
		FileColorReader(const char *file) {
			fp = fopen(file, "r");
		}
		
		~FileColorReader() {
			fclose(fp);
		}
		
		void announceFace(unsigned int faceIndex) {}
		
		char readColor(unsigned int i, unsigned int j) {
			return fgetc(fp);
		}
};

void readRubiksFromStdin(RubiksState & rubiks) {
	StdinColorReader colorReader;
	readRubiks(colorReader, rubiks);
}

void readRubiksFromFile(RubiksState & rubiks, const char *file) {
	FileColorReader colorReader(file);
	readRubiks(colorReader, rubiks);
}

static void readRubiks(ColorReader & colorReader, RubiksState & rubiks) {
	for (unsigned int f = 0; f < F_COUNT; ++f) {
		colorReader.announceFace(f);
		readFace(colorReader, rubiks, (Face)f);
	}
}

static void readFace(ColorReader & colorReader, RubiksState & rubiks, Face f) {
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 3; ++j) {
			if (i == 1 && j == 1) continue;
			
			Color color = C_WHITE;
			char c;
			do {
				c = colorReader.readColor(i, j);
				
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
