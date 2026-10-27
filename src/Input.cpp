#include "Input.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::string readText(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input was interrupted.");
        }
        if (value.find_first_not_of(" \t") != std::string::npos) {
            return value;
        }
        std::cout << "The field cannot be empty. Try again.\n";
    }
}

int readInt(const std::string& prompt, int minimum, int maximum) {
    while (true) {
        std::string line;
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input was interrupted.");
        }
        std::istringstream input(line);
        int number;
        char extra;
        if ((input >> number) && !(input >> extra) &&
            number >= minimum && number <= maximum) {
            return number;
        }
        std::cout << "Enter an integer from " << minimum
                  << " to " << maximum << ".\n";
    }
}

double readPrice(const std::string& prompt) {
    while (true) {
        std::string line;
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            throw std::runtime_error("Input was interrupted.");
        }
        std::replace(line.begin(), line.end(), ',', '.');
        std::istringstream input(line);
        double number;
        char extra;
        if ((input >> number) && !(input >> extra) &&
            std::isfinite(number) && number >= 0.0) {
            return number;
        }
        std::cout << "Enter a non-negative price (example: 129.50).\n";
    }
}
