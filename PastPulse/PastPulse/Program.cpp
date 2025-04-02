#include "User.h"
#include "Admin.h"
#include "Menu.h"
#include "Riddle.h"
#include "Simulator.h"


using json = nlohmann::json;

void gotoxy(int x, int y) {
	COORD coord = { static_cast<SHORT>(x),static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() 
{
	menu();
	bool userLogged = false;
	vector<string> options = { "Login as ADMIN" , "Login as USER" };
	int selected = 0;
	bool running = true;
	hideCursor();

	json users = readUsersFromJson("users.json");

	while (running) {
		int key = _getch();
		if (key == 0 || key == 224) {
			key = _getch();
			switch (key)
			{
			case 72:
				selected = (selected > 0) ? selected - 1 : options.size() - 1;
				break;
			case 80:
				selected = (selected < options.size() - 1) ? selected + 1 : 0;
				break;
			}
		}
		else if (key == 13) {
			system("cls");
			if (selected == 0) {
				string username, password;
				cout << "=== Admin ===\n";
				cout << "Enter admin username: ";
				cin >> username;
				cout << "Enter admin password: ";
				cin >> password;
				if (adminLogin(username, password)) {
					cout << "Admin login successful!" << endl;
					userLogged = true; //Trqbva da se naravi nova promenliva za admi,koqto da vodi kum modifyinga
					//admin func
				}
				else {
					cout << "Admin login failed." << endl;
				}
			}
			else if (selected == 1) {
				vector<string> userOptions = { "Login", "Register" };
				int userSelected = 0;
				bool userRunning = true;

				while (userRunning) {
					int userKey = _getch();
					if (userKey == 0 || userKey == 224) {
						userKey = _getch();
						switch (userKey) {
						case 72:
							userSelected = (userSelected > 0) ? userSelected - 1 : userOptions.size() - 1;
							break;
						case 80:
							userSelected = (userSelected < userOptions.size() - 1) ? userSelected + 1 : 0;
							break;
						}
					}
					else if (userKey == 13) {
						system("cls");
						if (userSelected == 0) {
							if (userLogin(users)) {
								cout << "Login successful!\n";
								userLogged = true;
							}
							else {
								cout << "Failed to login!\n";
							}
						}
						else if (userSelected == 1) {
							int result = userRegister(users);
							if (result == 1) {
								cout << "Registration successful!\n";
							}
							else if (result == 0) {
								cout << "Registration failed: Username already exists.\n";
							}
							else if (result == -1) {
								cout << "Registration failed: Could not save the user data.\n";
							}
						}
						userRunning = false;
					}
				}
			}
			cout << "\nPress enter to continue...";
			cin.get();
			if (userLogged)
			{
				simulator();
			}


		}

	}
	string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
}
