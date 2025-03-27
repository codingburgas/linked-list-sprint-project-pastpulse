#include <iostream>
#include "Riddle.h"

int main() {
	std::string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
}
