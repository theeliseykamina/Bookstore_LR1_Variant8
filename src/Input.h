#ifndef INPUT_H
#define INPUT_H

#include <string>

std::string readText(const std::string& prompt);
int readInt(const std::string& prompt, int minimum, int maximum);
double readPrice(const std::string& prompt);

#endif
