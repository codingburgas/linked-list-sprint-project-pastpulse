#include "Riddle.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Riddle* loadRiddlesFromFile(std::string& filename) {
	Riddle* head = nullptr;
	std::ifstream file(filename);

	// JSON object that will contain the data from the file
	json riddlesJson;
	// Read JSON data from the file and load it into the object
	file >> riddlesJson;
	file.close();

	// (range-based loop) to iterate over all elements in the JSON object 'riddlesJson'
	for (const auto& item : riddlesJson) {
		// Create a new riddle
		Riddle* newRiddle = new Riddle;
		newRiddle->question = item["question"];
		newRiddle->answer = item["answer"];
		newRiddle->hints = item["hints"];
		// Add the new riddle to the beginning of the linked list
		newRiddle->next = head;
		head = newRiddle;
	}
	return head;
}

void displayRiddles(Riddle* head) {
	if (!head) {
		std::cout << "There aren't any riddles";
		return;
	}
	// Pointer to the current list item
	Riddle* current = head;
	while (current) {
		std::cout << "Riddle" << current->question << std::endl;
		std::cout << "Answer" << current->answer << std::endl;
		std::cout << "Hint";
		if (current->hints.size()==0) {
			std::cout << "No RIddle!" << std::endl;
		}
		else {
			for (size_t i = 0; i < current->hints.size(); i++)
			{
				std::cout << " - " << current->hints[i] << std::endl;
			}
		}
		// Move to the next riddle in the list
		current = current->next;
	}
}

// Function to check if the entered password is correct for an administrator
bool isAdmin() {
	std::string password;
	std::string correctPassword = "admin";
	std::cout << "Enter admin password: ";
	std::cin >> password;
	if (password == correctPassword) {
		return true;
	}
	else {
		std::cout << "Incorrect password!";
		return false;
	}
}

void saveRiddlesToFile(Riddle* head, std::string& filename) {
	if (!isAdmin()) {
		return;
	}
	std::ofstream file(filename);
	// JSON array that will store the riddles
	json riddlesJson = json::array();
	Riddle* current = head;

	while (current) {
		// Add each riddle as a JSON object to the array
		riddlesJson.push_back({
			{"question", current->question},
			{"answer", current->answer},
			{"hints", current->hints}
			});
		current = current->next;
	}

	// Write the JSON data to the file, indented by 4 spaces for better formatting
	file << riddlesJson.dump(4);
	file.close();
	std::cout << "The new riddles were added";
}
