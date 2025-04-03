#include "Riddle.h"
#include "Validation.h"
#include "Menu.h"
#include "Simulator.h"

Riddle* loadRiddlesFromFile(string& filename) {
	Riddle* head = nullptr;
	ifstream file(filename);
	if (file.fail()) {
		cout << "Unable to open file " << filename << endl;
	}
	// JSON object that will contain the data from the file
	json j;
	file >> j;
	srand(time(nullptr));
	int randomIndex = rand() % j.size();
	json selectedRiddle = j[randomIndex];
	file.close();

	// (range-based loop) to iterate over all elements in the JSON object 'riddlesJson'
	for (const auto& item : j) {
		// Create a new riddle
		Riddle* newRiddle = new Riddle;
		newRiddle->name = item["name"];
		newRiddle->introduction = item["introduction"];

		for (int i = 0; i < 4 && i < item["hints"].size(); i++) {
			newRiddle->hints.push_back(item["hints"][i]);
		}
		newRiddle->answerHints = item["answerHints"];
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
bool askHint(Riddle* riddle) {


	bool allHintsCorrect = true;
	for (size_t i = 0; i < riddle->hints.size(); i++)
	{
		string userAnswer;
		cout << "Hint " << i + 1 << ": " << riddle->hints[i] << endl;
		cout << "Your asnwer: ";
		getline(cin, userAnswer);
		if (userAnswer != riddle->answerHints[i]) {
			allHintsCorrect = false;
			cout << "Wrong asnwer. The correct answer is: "<< riddle->answerHints[i] << endl;
		}
	}
	return allHintsCorrect;
}

void displayRiddles(Riddle* head) {
	system("cls");
	if (!head) {
		cout << "There aren't any riddles";
		return;
	}
	// Pointer to the current list item
	Riddle* current = head;
	printCentered("  _________      .__                ___________.__             __________.__    .___  .___.__          ", 5);
	printCentered(" /   _____/ ____ |  |___  __ ____   \\__    ___/|  |__   ____   \\______   \\__| __| _/__| _/|  |   ____  ", 6);
	printCentered(" \\_____  \\ /  _ \\|  |\\  \\/ // __ \\    |    |   |  |  \_/ __ \\   |       _/  |/ __ |/ __ | |  | _/ __ \\ ", 7);
	printCentered(" /        (  <_> )  |_\\   /\\  ___/    |    |   |   Y  \\  ___/   |    |   \\  / /_/ / /_/ | |  |_\\  ___/ ", 8);
	printCentered("/_______  /\____/|____/\\_/  \\___  >   |____|   |___|  /\\___  >  |____|_  /__\\____ \\____ | |____/\\___  >", 9);
	printCentered("        \\/                      \\/                  \\/     \\/          \\/        \\/    \\/           \\/ ", 10);
	newLine(2);
		cout << "Riddle Name: " << current->name << endl;
		cout << "Introduction: " << current->introduction << endl;
		cout << "Hints: ";
		if (current->hints.empty()) {
			cout << "No hints available!" << endl;
		}
		else {
			// The function for checking the answers to the clues is called
			bool allHintsCorrect = askHint(current);
		}
		cout << "Correct Answer: " << current->answer << endl;
		cout << "Answer" << current->answer << endl;
		for (size_t i = 0; i < current->facts.size(); i++)
		{
			cout << " - " << current->facts[i] << endl;
		}
		cout << "Period " << current->period << endl;
		cout << "Complexity " << current->complexity << endl;
		// Move to the next riddle in the list
		current = current->next;
		newLine(2);
		cout << "1.Lead this uprising" << endl;
		cout << "2.Solve new riddle" << endl;
		cout << "3.Go back to the main menu" << endl;
		int choice;
		cout << "Enter your choice here: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			leading(); break;
		case 2:
			displayRiddles(head); break;
		case 3:
			menu(); break;
		}
	
}


void saveRiddlesToFile(Riddle* head, string& filename) {
	ofstream file(filename);
	// JSON array that will store the riddles
	json riddlesJson = json::array();
	Riddle* current = head;

	while (current) {
		// Add each riddle as a JSON object to the array
		riddlesJson.push_back({
			{"name", current->name},
			{"introduction", current->introduction},
			{"hints", current->hints},
			{"answerHints", current->answerHints},
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
	cout << "The new riddles were added";
}

void addRiddle(Riddle* head, string& filename) {
	if (!isAdmin()) {
		return;
	}
	Riddle* newRiddle = new Riddle;
	cout << "Enter the riddle name: ";
	getline(cin, newRiddle->name);
	cout << "Enter the introduction to the riddle: ";
	getline(cin, newRiddle->introduction);
	
	int hintNumber = 4;
	cout << "Enter 4 hints" << endl;

	for (int i = 0; i < hintNumber; i++) {
		string hint;
		string answerHint;
		cout << "Hint " << i + 1 << ": " << endl;
		getline(cin, hint);
		// Add the hint to the hint vector
		newRiddle->hints.push_back(hint);

		cout << "Enter the correct answer";
		getline(cin, answerHint);
		newRiddle->answerHints.push_back(answerHint);
	}
	cout << "Write the valid final answer";

	int factsNumber;
	cout << "How many fun facts they are?";
	cin >> factsNumber;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid try again ";
		cin >> factsNumber;
	}

	cin.ignore();
	for (int i = 0; i < factsNumber; i++) {
		string funFact;
		cout << "Fact " << i + 1 << ": " << endl;
		getline(cin, funFact);

		newRiddle->facts.push_back(funFact);
	}


	cout << "Enter period(Before WWI or After WWI): ";
	while (true) {
		getline(cin, newRiddle->period);
		if (newRiddle->period == "Before WWI" || newRiddle->period == "After WWI") {
			break;
		}
		cout << "Invalid input!";
	}


	cout << "Enter complexity from 1 to 10: ";
	cin >> newRiddle->complexity;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid input!";
		cin >> newRiddle->complexity;
	}

	cout << "Successful added!" << endl;
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
	cout << "You seccessfully stop the game" << endl;
}


void deleteRiddle(Riddle* head, string& filename) {
	if (head == nullptr) {
		cout << "Empty list" << endl;
		return;
	}

	// Display all available riddles to choose from
	cout << "Pick riddle to delete" << endl;
	int count = 1;
	Riddle* current = head;
	vector<Riddle*> riddlesList;

	while (current != nullptr) {
		// Displays the sequence number and name of the riddle
		cout << count << ". " << current->name << endl;
		riddlesList.push_back(current);
		// Moving on to the next riddle
		current = current->next;
		count++;
	}

	int choice;
	cout << "Enter the number of the riddle: ";
	cin >> choice;

	if (choice < 1 || choice > riddlesList.size()) {
		cout << "Incorrect choice" << endl;
		return;
	}
	// Select the riddle from the list
	Riddle* toDelete = riddlesList[choice - 1];
	
	// If it removes the first riddle, the head pointer is changed
	if (toDelete == head) {
		head = head->next;
	}
	else {
		// Search for the previous element in the list to connect to the next one
		current = head;
		while (current != nullptr && current->next != toDelete) {
			current = current->next;
		}
		if (current != nullptr) {
			current->next = toDelete->next;
		}
	}

	delete toDelete;

	ofstream file(filename);
	// An empty JSON array in which the riddles will be stored
	json riddlesArray = json::array();  

	current = head;
	while (current != nullptr) {
		json riddleJson;
		riddleJson["name"] = current->name;
		riddleJson["introduction"] = current->introduction;
		riddleJson["answer"] = current->answer;
		riddleJson["facts"] = current->facts;
		riddleJson["hints"] = current->hints;
		riddleJson["asnwerHints"] = current->answerHints;
		riddleJson["period"] = current->period;
		riddleJson["complexity"] = current->complexity;

		riddlesArray.push_back(riddleJson); 
		current = current->next;
	}

	file.close();
	cout << "Riddle was deleted" << endl;
}

void editRiddle(Riddle* head, string& filename) {
	if (head == nullptr) {
		cout << "Empty list!" << endl;
	}

	cout << "Pick riddle to edit:" << endl;
	int count = 1;
	Riddle* current = head;
	vector<Riddle*> riddlesList;
	while (current != nullptr) {
		cout << count << ". " << current->name << endl;
		riddlesList.push_back(current);
		current = current->next;
		count++;
	}

	int choice;
	cout << "Enter the number of the riddle: ";
	cin >> choice;

	if (choice < 1 || choice > riddlesList.size()) {
		cout << "Incorrect choice!" << endl;
	}

	Riddle* toEdit = riddlesList[choice - 1];
	
	// Edit name
	cout << "Edit the riddle details" << endl;
	cout << "Current name: " << toEdit->name << endl;
	cout << "Enter new name: ";
	string newName;
	cin.ignore();
	getline(cin, newName);
	if (!newName.empty()) {
		toEdit->name = newName;
	}
	// Edit the introduction
	cout << "Current introduction: " << toEdit->introduction << endl;
	cout << "Enter new introduction: ";
	string newIntroduction;
	getline(cin, newIntroduction);
	if (!newIntroduction.empty()) {
		toEdit->introduction = newIntroduction;
	}

	// Edit the answer
	cout << "Current answer: " << toEdit->answer << endl;
	cout << "Enter new answer: ";
	string newAnswer;
	getline(cin, newAnswer);
	if (!newAnswer.empty()) {
		toEdit->answer = newAnswer;
	}

	// Edit the facts
	cout << "Current facts: " << endl;
	for (size_t i = 0; i < toEdit->facts.size(); ++i) {
		cout << i + 1 << ". " << toEdit->facts[i] << endl;
	}

	cout << "Enter the number of the fact you want to edit: ";
	int factChoice;
	cin >> factChoice;
	cin.ignore();

	// Edit the selected fact
	if (factChoice > 0 && factChoice <= toEdit->facts.size()) {
		cout << "Enter new fact: ";
		string newFact;
		getline(cin, newFact);
		// Replace the old fact with the new one
		toEdit->facts[factChoice - 1] = newFact; 
	}
	// Edit hints
	cout << "Current hints: " << endl;
	for (size_t i = 0; i < toEdit->hints.size(); ++i) {
		cout << i + 1 << ". " << toEdit->hints[i] << endl;
	}

	cout << "Enter the number of the hint you want to edit : ";
	int hintChoice;
	cin >> hintChoice;
	cin.ignore();

	if (hintChoice > 0 && hintChoice <= toEdit->hints.size()) {
		cout << "Enter new hint: ";
		string newHint;
		getline(cin, newHint);
		toEdit->hints[hintChoice - 1] = newHint;
	}


	// Edit the answer for the seleted hint
	cout << "Current answer for the selected hint: " << endl;
	cout << "Enter new answer for the hint: ";
	string newAnswerHint;
	getline(cin, newAnswerHint);
	// Replace the old answer for the hint with the new one
	if (newAnswerHint.size() > 0) {
		if (hintChoice > 0 && hintChoice <= toEdit->answerHints.size()) {
			toEdit->answerHints[hintChoice - 1] = newAnswerHint;
		}
		else {
			// Add a new answer if it's a new hint
			toEdit->answerHints.push_back(newAnswerHint);
		}
	}

	// Edit the period
	cout << "Current period: " << toEdit->period << endl;
	cout << "Enter new period: ";
    string newPeriod;
	getline(cin, newPeriod);
	if (!newPeriod.empty()) {
		toEdit->period = newPeriod;
	}
	// Edit complexity
	cout << "Current complexity: " << toEdit->complexity << endl;
	cout << "Enter new complexity: ";
	int newComplexity;
	cin >> newComplexity;
	if (newComplexity > 0) {
		toEdit->complexity = newComplexity;
	}
	ofstream file(filename);
	json j;
	current = head;
	while (current != nullptr) {
		json riddleJson;
		riddleJson["name"] = current->name;
		riddleJson["introduction"] = current->introduction;
		riddleJson["answer"] = current->answer;
		riddleJson["facts"] = current->facts;
		riddleJson["hints"] = current->hints;
		riddleJson["answerHints"] = current->answerHints;
		riddleJson["period"] = current->period;
		riddleJson["complexity"] = current->complexity;
		j.push_back(riddleJson);

		current = current->next;
	}
	file.close();
	cout << "Riddle has been updated!" << endl;
}