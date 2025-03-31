#pragma once
#include "pch.h"

void menu();
void displayMenu(int selected);
void printCentered(const string& text, int y);
void newLine(int newLines);
void displayOptions(const vector<string>& options, int selected, const vector<string>& fileContent);