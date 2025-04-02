#pragma once
#include "pch.h"

// Structure that represents a riddle
struct Riddle {
	string period;
	int complexity;
	string name;
	string introduction;
	vector<string> hints;
	string answer;
	vector<string> facts;

	// Pointer to the next riddle
	Riddle* next;
};

Riddle* loadRiddlesFromFile(string& filename);
void displayRiddles(Riddle* head);
void saveRiddleToFile(Riddle* head, string& filename);
void addRiddle(Riddle* head, string& filename);
void freeRiddles(Riddle* head);
bool compareByPeriod(Riddle* a, Riddle* b);
Riddle* merge(Riddle* left, Riddle* right);
Riddle* mergeSort(Riddle* head);
void deleteRiddle(Riddle* head, string& filename);
void editRiddle(Riddle* head, string& filename);