#include "User.h"
#include "Program.h"
#include "Validation.h"
#include "Riddle.h"
#include "Menu.h"
json users;  //Global json object to store user data
void initUsers() {
	users = readUsersFromJson("users.json");
}

json readUsersFromJson(const string& filename) {
	ifstream file(filename);  //Open the file for reading
	json j;  //Create a json object
	if (file.is_open()) {
		file >> j;  //Read the JSON data
		file.close();


	}
	else {
		j = { {"users", json::array()} };  //Initialize 'j' with an empty "users" array if the file could not be opened
	}
	return j;
}

int  userRegister(json& users) {
	string username;
	string password;
	string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
	displaySignUpTitle();
	cout << "Enter username: ";
	cin >> username;

	for (const auto& user : users["users"]) {  //Iterate through the existing users
		if (user["username"] == username) {
			cout << "Error: username already exists!\n";
			return 0;
		}
	}

	bool validPassword = false;
	while (!validPassword) {
		cout << "Enter password: ";
		cin >> password;

		validPassword = isValidPassword(password);
	}

	json newUser = { {"username", username}, {"password", password} };  //Create a new json object for the new user
	users["users"].push_back(newUser);  //Add the new user

	ofstream outFile("users.json");  //Open the "users.json" file for writing
	if (outFile.is_open()) {
		outFile << users.dump(4);  //Write the updated object to the file with an indentation of 4 for readability
		outFile.close();
		cout << "Successful registration!\n";
		startFilteredRiddle(riddlesHead);
	}
	else {
		cout << "Error saving user data.\n";
		return -1;
	}


	system("pause");
}
bool userLogin(const json& users) {
	string username;
	string password;
	string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
	displayLoginTitle();
	cout << "Enter username: ";
	cin >> username;
	cout << "Enter password: ";
	cin >> password;

	return autehnticate(users, username, password);
}
