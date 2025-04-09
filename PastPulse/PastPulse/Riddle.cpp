#include "Riddle.h"
#include "Validation.h"
#include "Menu.h"
#include "Simulator.h"
#include "Colors.h"
#include "DrawText.h"

bool openFile(ifstream& file, const string& filename) {
	file.open(filename);
	if (file.fail()) {
		cout << "Unable to open file " << filename << endl;
		return false;
	}
	return true;
}

Riddle* loadRiddlesFromFile(string& filename) {
	Riddle* head = nullptr;
	ifstream file;
	if (!openFile(file, filename)) {
		return nullptr;
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
		newRiddle->next = head;
		head = newRiddle;
	}
	return head;
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
	displayRiddleTitle();
	Riddle* newRiddle = new Riddle;
	cin.ignore();
	// Add riddle name
	cout << "Enter the riddle name: ";
	while (true) {
		getline(cin, newRiddle->name);
		if (!newRiddle->name.empty()) {
			break;
		}
		else {
			cout << "Riddle name cannot be empty ";
		}
	}
	// Add riddle introduction
	cout << "Enter the riddle introduction: ";
	while (true) {
		getline(cin, newRiddle->introduction);
		if (!newRiddle->introduction.empty()) {
			break;
		}
		else {
			cout << "Riddle introduction cannot be empty ";
		}
	}
	// Add riddle hints and answers
	int hintNumber = 4;
	cout << "Enter 4 hints" << endl;
	for (int i = 0; i < hintNumber; i++) {
		string hint;
		string answerHint;
		cout << "Hint " << i + 1 << ": " << endl;
		while (true) {
			getline(cin, hint);
			if (!hint.empty()) {
				break;
			}
			else {
				cout << "Hint cannot be empty" << endl;
			}
		}
		// Add the hint to the hint vector
		newRiddle->hints.push_back(hint);

		cout << "Enter the correct answer";
		while (true) {
			getline(cin, answerHint);
			if (!answerHint.empty()) {
				break;
			}
			else {
				cout << "Answer hint cannot be empty" << endl;
			}
		}
		newRiddle->answerHints.push_back(answerHint);
	}
	// Add riddle final answer
	cout << "Write the valid final answer: ";
	while (true) {
		getline(cin, newRiddle->answer);
		if (!newRiddle->answer.empty()) {
			break;
		}
		else {
			cout << "Final answer cannot be ampty" << endl;
		}
	}
	// Add riddle facts
	cout << "How many facts they are?";
	int factsNumber;
	while (true) {
		cin >> factsNumber;
		if (cin.fail() || factsNumber < 1) {
			// Remove the newline, leaving the buffer clean for subsequent 'getline()' operations
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid try again ";
			cin >> factsNumber;
		}
		else {
			break;
		}
	}
	cin.ignore();
	for (int i = 0; i < factsNumber; i++) {
		string funFact;
		cout << "Fact " << i + 1 << ": " << endl;
		while (true) {
			getline(cin, funFact);
			if (!funFact.empty()) {
				break;
			}
			else {
				cout << "Fact cannot be empty" << endl;
			}
		}
		newRiddle->facts.push_back(funFact);
	}
	//Add period and complexity
	string period;
	cout << "Enter period(Before WWI or After WWI): ";
	while (true) {
		getline(cin, period);
		if (period == "Before WWI" || period == "After WWI") {
			newRiddle->period = period;
			break;
		}
		else {
			cout << "Try again: ";
		}
	}
	cout << "Enter complexity from 1 to 3: " << endl;
	while (true) {
		cin >> newRiddle->complexity;
		if (cin.fail() || newRiddle->complexity > 3 || newRiddle->complexity < 1) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input!";
			cin >> newRiddle->complexity;
		}
		else {
			break;
		}
	}

	cout << "Successful added!" << endl;
	// Change the pointer of the new riddle to point to the current first element
	newRiddle->next = head;
	head = newRiddle;
	// Save the riddle into the json file
	saveRiddlesToFile(head, filename);
}

void editRiddle(Riddle* head, string& filename) {
	displayRiddleTitle();
	if (head == nullptr) {
		cout << "Empty list!" << endl;
	}

	cout << "Pick riddle to edit:" << endl;
	int count = 1;
	Riddle* current = head;
	vector<Riddle*> riddlesList;
	// Traverse the list to display available riddles
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
	// Get the riddle to edit
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
	file << j.dump(4);
	file.close();
	cout << "Riddle has been updated!" << endl;
}

void deleteRiddle(Riddle* head, string& filename) {
	displayRiddleTitle();
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

	file << riddlesArray.dump(4);
	file.close();
	cout << "Riddle was deleted" << endl;
}

bool askHint(Riddle* riddle) {
	// Iterate over each hint in the riddle's hint list
	for (size_t i = 0; i < riddle->hints.size(); i++)
	{
		string userAnswer;
		setColor(YELLOW, BLACK);
		cout << "Hint " << i + 1 << ": " << riddle->hints[i] << endl;
		resetColor();
		cout << "Your asnwer for this(HINT): ";
		// Clear the remaining newline character in the buffer at the first hint
		if (i == 0) {
			cin.ignore();
		}
		getline(cin, userAnswer);
		if (userAnswer != riddle->answerHints[i]) {
			setColor(RED,BLACK);
			cout << "Wrong asnwer. The correct answer is: " << riddle->answerHints[i] << endl;
			this_thread::sleep_for(chrono::seconds(2));
			newLine(1);
			resetColor();
		}
		else {
			setColor(GREEN, BLACK);
			cout << "Correct answer: " << endl;
			this_thread::sleep_for(chrono::seconds(2));
			newLine(1);
			resetColor();
		}
	}
	return true;
}

void displayRiddles(Riddle* head) {
	system("cls");
	if (!head) {
		cout << "There aren't any riddles!";
		return;
	}
	// Pointer to the current list item
	Riddle* current = head;
	solveTheRiddleText();
	newLine(3);
	setColor(YELLOW, BLACK);
	cout << "Riddle Name: " << current->name << endl;
	resetColor();
	newLine(1);
	cout << "Introduction: " << current->introduction << endl;
	newLine(1);

	this_thread::sleep_for(chrono::seconds(2));

	askHint(current);
	string finalAnswer;
	cout << "Correct Answer (RIDDLE): ";
	getline(cin, finalAnswer);

	if (finalAnswer == current->answer) {
		setColor(GREEN, BLACK);
		cout << "Congratulations, your final answer is correct!" << endl;
		resetColor();
	}
	else {
		setColor(RED,BLACK);
		cout << "Your final answer is wrong. The correct answer is: " << current->answer << endl;
		resetColor();
	}
	system("clr");
	displayFactsTitle();
	//cout << "Fun facts for " << current->name;
	for (size_t i = 0; i < current->facts.size(); i++)
	{
		cout << " - " << current->facts[i] << endl;
		this_thread::sleep_for(chrono::seconds(1));

	}
	cin.ignore();
	// Move to the next riddle in the list
	current = current->next;
	newLine(2);
	const char* options[] = { "Lead this uprising", "Solve new riddle", "Go back to the main menu" };
	int selected = 0;
	int totalOptions = 3;

	while (true) {
		system("cls");
		printCentered("Use Arrow Keys to Navigate and Enter to Select", 5);
		for (int i = 0; i < totalOptions; i++) {
			if (i == selected) {
				printCentered("> " + string(options[i]), 7 + i);
			}
			else {
				printCentered("  " + string(options[i]), 7 + i);
			}
		}

		char key = _getch();

		if (key == 72) { // Up arrow key
			if (selected > 0) selected--;
		}
		else if (key == 80) { // Down arrow key
			if (selected < totalOptions - 1) selected++;
		}
		else if (key == 13) { // Enter key
			switch (selected) {
			case 0:
				leading();
				break;
			case 1:
				system("cls");
				startFilteredRiddle(head);
				break;
			case 2:
				menu();
				break;
			}
		}
	}

}


void startFilteredRiddle(Riddle* riddlesHead) {
	string chosenPeriod;
	int chosenComplexity;

	cout << "Enter period (Before/After): ";
	cin >> chosenPeriod;
	while (chosenPeriod != "Before" && chosenPeriod != "After") {
		cout << "Invalid period. Enter 'Before' or 'After': ";
		cin >> chosenPeriod;
	}

	cout << "Enter desired complexity (1-3): ";
	cin >> chosenComplexity;
	while (chosenComplexity < 1 || chosenComplexity > 3) {
		cout << "Please enter a valid complexity (1-3): ";
		cin >> chosenComplexity;
	}
	// Call the function to filter riddles by period and complexity
	vector<Riddle*> filteredVec = filterByPeriodAndComplexity(riddlesHead, chosenPeriod, chosenComplexity);
	if (filteredVec.size() == 0) {
		cout << "No riddles match that period and complexity";
	}
	Riddle* filteredList = nullptr;
	Riddle* last = nullptr;
	// Create a new list of riddles by copying from the filtered vector
	for (size_t i = 0; i < filteredVec.size(); ++i) {
		// Create a new node for each riddle
		Riddle* newNode = new Riddle(*filteredVec[i]);
		newNode->next = nullptr;
		if (!filteredList) {
			filteredList = newNode;
		}
		else {
			last->next = newNode;
		}
		last = newNode;
	}
	filteredList = mergeSortByComplexity(filteredList);
	cout << "Filtered riddles: " << endl;
	int count = 1;
	Riddle* current = filteredList;
	// A vector that contains the riddles the user can choose from
	vector<Riddle*> toChoose;

	while (current) {
		cout << count << ". " << current->name << endl;
		// Add the current riddle to the vector
		toChoose.push_back(current);
		current = current->next;
		count++;
	}

	int choice;
	while (true) {
		cout << "Choose a riddle to play (1-" << toChoose.size() << "): ";
		cin >> choice;

		if (choice >= 1 && choice <= toChoose.size()) {
			displayRiddles(toChoose[choice - 1]);
			break;
		}
		else {
			cout << "Invalid choice. Please try again" << endl;
		}
	}
}

vector<Riddle*> filterByPeriodAndComplexity(Riddle* head, const string& period, int complexity) {
	// An empty vector is created that will contain riddles that meet the criteria
	vector<Riddle*> result;
	Riddle* current = head;
	// Iterate through all the riddles in the list
	while (current) {
		if (current->period == period && current->complexity == complexity) {
			// If it matches, add the riddle to the result
			result.push_back(current);
		}
		current = current->next;
	}
	return result;
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

Riddle* mergeSortByPeriod(Riddle* head) {
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

	left = mergeSortByPeriod(left);
	right = mergeSortByPeriod(right);

	// Merge the two sorted parts and return the result
	return merge(left, right);
}

Riddle* splitComplexity(Riddle* head) {
	// Checks if the list is empty or contains only one element. In that case, it cannot be split
	if (head == nullptr || head->next == nullptr) {
		return nullptr;
	}

	Riddle* slow = head;
	Riddle* fast = head->next;

	// The position of the two pointers changes, with fast moving twice as fast as slow
	while (fast != nullptr && fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next->next;
	}
	// Once the fast pointer reaches the end the slow pointer will be in the middle of the list
	Riddle* middle = slow->next;
	slow->next = nullptr;
	return middle;
}

Riddle* mergeByComplexity(Riddle* left, Riddle* right) {
	if (left == nullptr) return right;
	if (right == nullptr) return left;

	if (left->complexity < right->complexity) {
		// If the left element has less complexity we put it at the beginning and recursively concatenate the rest
		left->next = mergeByComplexity(left->next, right);
		return left;
	}
	else {
		// If the right element has less or equal complexity, we put it at the beginning and recursively concatenate the remainder
		right->next = mergeByComplexity(left, right->next);
		return right;
	}
}

Riddle* mergeSortByComplexity(Riddle* head) {
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	Riddle* middle = splitComplexity(head);
	Riddle* left = mergeSortByComplexity(head);
	Riddle* right = mergeSortByComplexity(middle);

	// Merge the sorted halves by complexity
	return merge(left, right);
}

