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
		newRiddle->name = item["name"];
		newRiddle->introduction = item["introduction"];

		for (int i = 0; i < 4 && i < item["hints"].size(); i++) {
			newRiddle->hints.push_back(item["hints"][i]);
		}

		newRiddle->answer = item["answer"];
		newRiddle->facts = item["facts"];
		newRiddle->period = item["period"];
		newRiddle->complexity = item["complexity"];
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
		std::cout << "Riddle Name: " << current->name << std::endl;
		std::cout << "Introduction: " << current->introduction << std::endl;
		std::cout << "Answer" << current->answer << std::endl;
		std::cout << "Hints: ";
		if (current->hints.empty()) {
			std::cout << "No hints available!" << std::endl;
		}
		else {
			for (size_t i = 0; i < 4; i++) {
				if (i < current->hints.size()) {
					std::cout << " - " << current->hints[i] << std::endl;
				}
			}
		}
		std::cout << "Correct Answer: " << current->answer << std::endl;
		for (size_t i = 0; i < current->facts.size(); i++)
		{
			std::cout << " - " << current->facts[i] << std::endl;
		}
		std::cout << "Period " << current->period << std::endl;
		std::cout << "Complexity " << current->complexity << std::endl;
		// Move to the next riddle in the list
		current = current->next;
		std::cout << "__________________________________" << std::endl;
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
			{"name", current->name},
			{"introduction", current->introduction},
			{"hints", current->hints},
			{"answer", current->answer},
			{"facts", current->facts},
			{"period", current->period},
			{"complexity", current->complexity}
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
	std::cout << "Enter the riddle name: ";
	std::getline(std::cin, newRiddle->name);
	std::cout << "Enter the introduction to the riddle: ";
	std::getline(std::cin, newRiddle->introduction);
	int hintNumber = 4;
	std::cout << "Enter 4 hints:" << std::endl;

	for (int i = 0; i < hintNumber; i++) {
		std::string hint;
		std::cout << "Hint " << i + 1 << ": ";
		std::getline(std::cin, hint);
		newRiddle->hints.push_back(hint);
	}
	std::cout << "Write the corect answer: ";
	std::getline(std::cin, newRiddle->answer);

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


	std::cout << "Enter period(Before WWI or After WWI): ";
	while (true) {
		std::getline(std::cin, newRiddle->period);
		if (newRiddle->period == "Before WWI" || newRiddle->period == "After WWI") {
			break;
		}
		std::cout << "Invalid input!";
	}


	std::cout << "Enter complexity from 1 to 10: ";
	std::cin >> newRiddle->complexity;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invalid input!";
		std::cin >> newRiddle->complexity;
	}

	std::cout << "Successful added!" << std::endl;
	// Change the pointer of the new riddle to point to the current first element
	newRiddle->next = head;
	head = newRiddle;

	saveRiddlesToFile(head, filename);
}

bool compareByPeriod(Riddle* a, Riddle* b) {
	if (a->period == "Before" && b->period == "After") {
		return true;
	}
	else {
		return false;
	}
	// If the period is the same, we sort by complexity
	return a->complexity < b->complexity;
}

Riddle* merge(Riddle* left, Riddle* right) {
	// If one of the lists is empty, return the other one
	if (!left) {
		return right;
	}
	if (!right) {
		return left;
	}

	// Compare the first elements of the two lists
	if (compareByPeriod(left, right)) {
		left->next = merge(left->next, right);
		return left;
	}
	else {
		right->next = merge(left, right->next);
		return right;
	}
}


Riddle* mergeSort(Riddle* head) {
	if (!head || !head->next) {
		return head;
	}
	// middle will point to the middle of the list
	Riddle* middle = head;
	// fast moves twice as fast as middle
	Riddle* fast = head->next;

	// Fast and slow pointer to find the middle of the list
	while (fast && fast->next) {
		middle = middle->next;
		fast = fast->next->next;
	}
	// Split the list into two parts
	Riddle* left = head;
	Riddle* right = middle->next;
	middle->next = nullptr;

	left = mergeSort(left);
	right = mergeSort(right);

	// Merge the two sorted parts and return the result
	return merge(left, right);
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


