#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Riddle {
	std::string question;
	std::string answer;
	std::vector<std::string> hints;

	Riddle* next;
};

Riddle* loadRiddlesFromFile(std::string& filename);