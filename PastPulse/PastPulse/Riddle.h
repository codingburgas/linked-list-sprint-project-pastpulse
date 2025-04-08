#pragma once
#include "pch.h"

// Structure that represents a riddle
struct Riddle {
	string period;
	int complexity;
	string name;
	string introduction;
	vector<string> hints;
	vector<string> answerHints;
	string answer;
	vector<string> facts;

	// Pointer to the next riddle
	Riddle* next;
};

// Load and save riddles
Riddle* loadRiddlesFromFile(string& filename);
void saveRiddleToFile(Riddle* head, string& filename);
bool openFile(ifstream& file, const string& filename);

// Add Edit and Delete operations
void addRiddle(Riddle* head, string& filename);
void editRiddle(Riddle* head, string& filename);
void deleteRiddle(Riddle* head, string& filename);

// Display and filter 
void displayRiddles(Riddle* head);
bool askHint(Riddle* riddle);
void startFilteredRiddle(Riddle* riddlesHead);
vector<Riddle*> filterByPeriodAndComplexity(Riddle* head, const string& period, int complexity);

// Sorting(Merge Sort) by period and complexity
bool compareByPeriod(Riddle* a, Riddle* b);
Riddle* merge(Riddle* left, Riddle* right);
Riddle* mergeSortByPeriod(Riddle* head);

Riddle* mergeSortByComplexity(Riddle* head);
Riddle* mergeByComplexity(Riddle* left, Riddle* right);
Riddle* splitComplexity(Riddle* head);