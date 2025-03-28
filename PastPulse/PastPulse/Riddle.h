#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

// Structure that represents a riddle
struct Riddle {
	std::string question;
	std::string answer;
	std::vector<std::string> hints;
	std::string lastQuestion;
	std::vector<std::string> facts;

	// Pointer to the next riddle
	Riddle* next;
};

Riddle* loadRiddlesFromFile(std::string& filename);
void displayRiddles(Riddle* head);
void saveRiddleToFile(Riddle* head, std::string& filename);
void addRiddle(Riddle* head, std::string& filename);
void freeRiddles(Riddle* head);