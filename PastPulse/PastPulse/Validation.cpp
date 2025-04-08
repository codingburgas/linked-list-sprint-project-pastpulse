#include "Validation.h"
#include "Admin.h"
#include "Menu.h"

bool autehnticate(const json& users, const string& username, const string& password) {  //Authenticate a user based on the provided username and password
	for (const auto& user : users["users"]) {
		if (user["username"] == username && user["password"] == password) {
			return true;
		}
	}
	return false;
}

bool isValidPassword(const string& password) {
	if (password.length() < 6) {
		cout << "Password must be at least 6 characters long.\n";
		return false;
	}

	bool hasUpper = false;
	bool hasDigit = false;
	bool hasSpecial = false;

	for (char c : password) {  //Iterate through each character in the password string
		if (isupper(c)) {
			hasUpper = true;
		}
		if (isdigit(c)) {
			hasDigit = true;
		}
		if (ispunct(c)) {
			hasSpecial = true;
		}
	}

	if (!hasUpper || !hasDigit || !hasSpecial) {
		cout << "Password must contain at least: \n";
		cout << "* one uppercase letter \n";
		cout << "* one digit \n";
		cout << "one special character(!, @, #, $, %) \n";
		return false;
	}
	return true;
}

bool isAdmin() {
	displayLoginTitle();
	string username;
	string password = "admin-123";
	int attempts = 0;
	while (attempts < 3) {  //Allow up to 3 login attempts
		cout << "Enter admin username: ";
		cin >> username;
		cout << "Enter admin password: ";
		cin >> password;
		if (adminLogin(username, password)) {
			return true;
		}
		else {
			attempts++;
			cout << "Incorrect password!"<<endl;
		}
	}
	return false;
}