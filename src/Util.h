#ifndef UTIL_H
#define UTIL_H

#include "Defs.h"

#include <ostream>


std::ostream & operator<<(std::ostream & stream, Color c);

std::ostream & operator<<(std::ostream & stream, Rotation r);

#endif
