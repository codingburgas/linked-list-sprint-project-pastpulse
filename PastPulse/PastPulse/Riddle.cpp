#include "Riddle.h"
#include "Validation.h"
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
		newRiddle->lastQuestion = item["lastQuestion"];
		newRiddle->facts = item["facts"];
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
		std::cout << "Final question" << current->lastQuestion << std::endl;
		for (size_t i = 0; i < current->facts.size(); i++)
		{
			std::cout << " - " << current->facts[i] << std::endl;
		}
		// Move to the next riddle in the list
		current = current->next;
	}
}

// Function to check if the entered password is correct for an administrator


void saveRiddlesToFile(Riddle* head, std::string& filename) {
	std::ofstream file(filename);
	// JSON array that will store the riddles
	json riddlesJson = json::array();
	Riddle* current = head;

	while (current) {
		// Add each riddle as a JSON object to the array
		riddlesJson.push_back({
			{"question", current->question},
			{"answer", current->answer},
			{"hints", current->hints},
			{"lastQuestion", current->lastQuestion},
			{"facts", current->facts}
			});
		current = current->next;
	}

	// Write the JSON data to the file, indented by 4 spaces for better formatting
	file << riddlesJson.dump(4);
	file.close();
	std::cout << "The new riddles were added";
}

void addRiddle(Riddle* head, std::string& filename) {
	if (!isAdmin()) {
		return;
	}
	Riddle* newRiddle = new Riddle;
	std::cout << "Add the riddle here: ";
	std::getline(std::cin, newRiddle->question);
	std::cin.ignore();
	std::cout << "Write the corect answer: ";
	std::getline(std::cin, newRiddle->answer);
	std::cin.ignore();

	int hintNumber;
	std::cout << "How many hints they are?";
	std::cin >> hintNumber;
	if(std::cin.fail()) {
		// Resets the error flag so that he can accept input again
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		// Ignore up to 1000 characters or until a newline '\n' is encountered to clear out bad input
		std::cout << "Invalid try again ";
		std::cin >> hintNumber;
	}
	// Clears the input buffer of residual characters (such as newlines)
	std::cin.ignore();

	for (int i = 0; i < hintNumber; i++) {
		std::string hint;
		std::cout << "Hint " << i + 1 << ": " << std::endl;
		std::getline(std::cin, hint);
		// Add the hint to the hint vector
		newRiddle->hints.push_back(hint);
	}
	std::cout << "Write the valid final answer";
	std::getline(std::cin, newRiddle->lastQuestion);

	int factsNumber;
	std::cout << "How many fun facts they are?";
	std::cin >> factsNumber;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invalid try again ";
		std::cin >> factsNumber;
	}

	std::cin.ignore();
	for (int i = 0; i < factsNumber; i++) {
		std::string funFact;
		std::cout << "Fact " << i + 1 << ": " << std::endl;
		std::getline(std::cin, funFact);

		newRiddle->facts.push_back(funFact);
	}
	std::cout << "Successful added!" << std::endl;
	// Change the pointer of the new riddle to point to the current first element
	newRiddle->next = head;
	head = newRiddle;

	saveRiddlesToFile(head, filename);
}

// Function to release all riddles from memory
void freeRiddles(Riddle* head) {
	while (head) {
		Riddle* temp = head;
		head = head->next;
		delete temp;
	}
	std::cout << "You seccessfully stop the game" << std::endl;
}
