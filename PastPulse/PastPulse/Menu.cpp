#include "Menu.h"
#include "User.h"
#include "Admin.h"
#include "Riddle.h"
#include "Validation.h"
#include "Colors.h"
#include "DrawText.h"

using json = nlohmann::json;  //Use the nlohmann json namespace
using namespace std;

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;  //Cursor visibility to false
    SetConsoleCursorInfo(consoleHandle, &info);

}

void printCentered(const string& text, int y) {
    int padding = (80 - text.length() + 35) / 2;  //Calculate the padding needed
    COORD pos = { (SHORT)padding, (SHORT)y };  //Structure to specify the position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    cout << text;
}
void newLine(int newLines)
{
	for (int i = 0; i < newLines; i++)
	{
		cout << endl;
	}
}
void displayMenu(int selected) {
    system("cls");

    pastPulse();

    newLine(2);

    options("START","LEAVE",selected,10,14);


}

void displayRoleMenu(int selected) {
    system("cls");

    selectRole();

    newLine(1);

    options("ADMIN", "USER ", selected, 9, 13);
}
void displayUserOptions(int selected) {
    system("cls");

    userOptions();

    newLine(1);

    options("LOGIN", "SIGNUP", selected,11,15);
}

void displayLoginTitle() {
    system("cls");

    loginText();

    newLine(1);
}

void displaySignUpTitle() {
    system("cls");

    signupText();

    newLine(1);
}

void displayRiddleTitle() {
    system("cls");

    riddleText();

    newLine(1);
}

void displayAdminTitle() {
    system("cls");

    adminText();

    newLine(1);
}

void displaySelectTitle() {
    system("cls");

    selectText();

    newLine(1);
}

void displayFactsTitle() {
    system("cls");

    factText();

    newLine(1);
}


void adminMenu(Riddle* riddlesHead, string& filename) {
    int selected = 0;
    bool adminRunning = true;

    while (adminRunning) {
        system("cls");
        displayAdminTitle();

        for (int i = 0; i < 4; i++) {
            if (i == selected)
                cout << "> ";
            else
                cout << "  ";

            if (i == 0) cout << "Add Riddle\n";
            if (i == 1) cout << "Edit Riddle\n";
            if (i == 2) cout << "Delete Riddle\n";
            if (i == 3) cout << "Exit Admin Menu\n";
        }

        char key = _getch(); //Read a single character

        if (key == 72) {
            selected = (selected > 0) ? selected - 1 : 3;
        }
        else if (key == 80) {
            selected = (selected < 3) ? selected + 1 : 0;
        }
        else if (key == 13) { //Enter
            switch (selected) {
            case 0:
                system("cls");
                addRiddle(riddlesHead, filename);
                break;
            case 1:
                system("cls");
                editRiddle(riddlesHead, filename);
                break;
            case 2:
                system("cls");
                deleteRiddle(riddlesHead, filename);
                break;
            case 3:
                cout << "Exiting Admin Menu...\n";
                adminRunning = false;
                break;
            }
        }
    }
}

void menu() {
    int selected = 0; 
    bool running = true;
    string filename = "riddles.json";
    Riddle* riddlesHead = loadRiddlesFromFile(filename);
    while (running) {
        displayMenu(selected);

        char key = _getch();  
        switch (key) {
        case 72:  
            selected = (selected == 0) ? 1 : 0;
            break;
        case 80: 
            selected = (selected == 1) ? 0 : 1; 
            break;
        case 13:  
            if (selected == 0) {
                system("cls");
                printCentered("Game Starting...", 10);
                running = false;  //Exit the main menu

                system("cls");

                int roleSelected = 0; 
                bool roleRunning = true;

                while (roleRunning) {
                    displayRoleMenu(roleSelected);

                    char keyRole = _getch();  //Get user input for role selection

                    switch (keyRole) {
                    case 72:  
                        roleSelected = (roleSelected == 0) ? 1 : roleSelected - 1;
                        break;
                    case 80:  
                        roleSelected = (roleSelected == 1) ? 0 : roleSelected + 1;
                        break;
                    case 13:  
                        if (roleSelected == 0) {  
                            system("cls");
                            if (isAdmin()) {
                                cout << "Admin login successful!" << endl;
                                adminMenu(riddlesHead, filename);
                                running = true;  //Go back to the main menu
                            }
                            else {
                                cout << "Log in failed" << endl;
                                running = true;
                            }
                        }
                        else if (roleSelected == 1) {  //"USER" is selected

                            int userSelected = 0;
                            bool userRunning = true;

                            while (userRunning) {
                            system("cls");  
                            displayUserOptions(userSelected);
                                int userKey = _getch();
                                if (userKey == 0 || userKey == 224) {
                                    userKey = _getch();  //Get user input for user options
                                    switch (userKey) {
                                    case 72:  
                                        userSelected = (userSelected > 0) ? userSelected - 1 :2 - 1;
                                        break;
                                    case 80:  
                                        userSelected = (userSelected < 2 - 1) ? userSelected + 1 : 0;
                                        break;
                                    }
                                }
                                else if (userKey == 13) {  
                                    system("cls");
                                    if (userSelected == 0) {  //"LOGIN" is selected
                                        if (userLogin(users)) {
                                            cout << "Login successful!" << endl;
                                            userRunning = false;
                                            system("clr");
                                            displaySelectTitle();
                                            startFilteredRiddle(riddlesHead);
                                          
                                        }
                                        else {
                                            cout << "Failed to login!" << endl;
                                            system("pause");
                                        }
                                    }
                                        else if (userSelected == 1) {  //"SIGNUP" is selected
                                        int result = userRegister(users);
                                        if (result == 1) {
                                            cout << "Registration successful!" << endl;
                                        }
                                        else if (result == -1) {
                                            cout << "Error saving user data." << endl;
                                        }
                                        userRunning = false;
                                    }
                                    }
                                }
                            }
                            roleRunning = false; 
                            break;
                        }
                    }
                }
            else {
                system("cls");
                printCentered("Goodbye! You can close the app by pressing any key button...", 10);
                running = false;
                break;
            }
           
        }
    }
}

