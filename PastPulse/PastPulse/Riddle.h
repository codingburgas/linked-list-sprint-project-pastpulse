#pragma once
#include "pch.h"
using json = nlohmann::json;

// Structure that represents a riddle
struct Riddle {
	std::string name;
	std::string introduction;
	std::string answer;
	std::vector<std::string> hints;
	std::vector<std::string> facts;
	std::string period;
	int complexity;

	// Pointer to the next riddle
	Riddle* next;
};

Riddle* loadRiddlesFromFile(std::string& filename);
void displayRiddles(Riddle* head);
void saveRiddleToFile(Riddle* head, std::string& filename);
void addRiddle(Riddle* head, std::string& filename);
void freeRiddles(Riddle* head);
bool compareByPeriod(Riddle* a, Riddle* b);
Riddle* merge(Riddle* left, Riddle* right);
Riddle* mergeSort(Riddle* head);
void deleteRiddle(Riddle* head, std::string& filename);