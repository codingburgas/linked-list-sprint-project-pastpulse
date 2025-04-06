#include "Menu.h"
#include "User.h"
#include "Admin.h"
#include "Riddle.h"
#include "Validation.h"


enum ConsoleColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_AQUA = 11,
    LIGHT_RED = 12,
    LIGHT_PURPLE = 13,
    LIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(ConsoleColor text, ConsoleColor background = BLACK) {
    SetConsoleTextAttribute(hConsole, text + (background << 4));
}

void resetColor() {
    SetConsoleTextAttribute(hConsole, WHITE); 
}

using json = nlohmann::json;
using namespace std;

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

}

void printCentered(const string& text, int y) {
    int padding = (80 - text.length() + 35) / 2;
    COORD pos = { (SHORT)padding, (SHORT)y };
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

    setColor(YELLOW);
    printCentered("  _____          _   _____       _           ", 1);
    printCentered(" |  __ \\        | | |  __ \\     | |          ", 2);
    printCentered(" | |__) __ _ ___| |_| |__) _   _| |___  ___  ", 3);
    printCentered(" |  ___/ _` / __| __|  ___| | | | / __|/ _ \\ ", 4);
    printCentered(" | |  | (_| \\__ \\ |_| |   | |_| | \\__ \\  __/ ", 5);
    printCentered(" |_|   \\__,_|___/\\__|_|    \\__,_|_|___/\\___| ", 6);
    resetColor();

    newLine(2);

    int startY = 9;
    int leaveY = 13;


    if (selected == 0) {
        setColor(LIGHT_GREEN);
        printCentered("===============", startY);
        printCentered("=   >START<   =", startY + 1);
        printCentered("===============", startY + 2);
        resetColor();
    }
    else {
        setColor(GRAY);
        printCentered("===============", startY);
        printCentered("=    START    =", startY + 1);
        printCentered("===============", startY + 2);
        resetColor();
    }

    newLine(1);


    if (selected == 1) {
        setColor(LIGHT_RED);
        printCentered("===============", leaveY);
        printCentered("=   >LEAVE<   =", leaveY + 1);
        printCentered("===============", leaveY + 2);
        resetColor();
    }
    else {
        setColor(GRAY);
        printCentered("===============", leaveY);
        printCentered("=    LEAVE    =", leaveY + 1);
        printCentered("===============", leaveY + 2);
        resetColor();
    }
}

void displayRoleMenu(int selected) {
    system("cls");

    setColor(YELLOW); 
    printCentered("   _____      _           _     _____       _      ", 1);
    printCentered("  / ____|    | |         | |   |  __ \\     | |     ", 2);
    printCentered(" | (___   ___| | ___  ___| |_  | |__) |___ | | ___ ", 3);
    printCentered("  \\___ \\ / _ \\ |/ _ \\/ __| __| |  _  // _ \\| |/ _ \\", 4);
    printCentered("  ____) |  __/ |  __/ (__| |_  | | \\ \\ (_) | |  __/", 5);
    printCentered(" |_____/ \\___|_|\\___|\\___|\\__| |_|  \\_\\___/|_|\\___|", 6);
    resetColor();

    newLine(1);

    int adminOptionY = 9;
    int userOptionY = 12;

    if (selected == 0) {
        setColor(LIGHT_GREEN);
        printCentered("===============", adminOptionY);
        printCentered("=   >ADMIN<   =", adminOptionY + 1);
        printCentered("===============", adminOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY);
        printCentered("===============", adminOptionY);
        printCentered("=    ADMIN    =", adminOptionY + 1);
        printCentered("===============", adminOptionY + 2);
        resetColor();
    }

    newLine(1);


    if (selected == 1) {
        setColor(LIGHT_RED);
        printCentered("===============", userOptionY);
        printCentered("=   >USER<   =", userOptionY + 1);
        printCentered("===============", userOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY);
        printCentered("===============", userOptionY);
        printCentered("=    USER    =", userOptionY + 1);
        printCentered("===============", userOptionY + 2);
        resetColor();
    }
}

void adminMenu(Riddle* riddlesHead, string& filename) {
    int selected = 0;
    bool adminRunning = true;

    while (adminRunning) {
        system("cls");

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

        char key = _getch(); 

        if (key == 72) {  
            selected = (selected > 0) ? selected - 1 : 3;
        }
        else if (key == 80) {  
            selected = (selected < 3) ? selected + 1 : 0;
        }
        else if (key == 13) { 
            switch (selected) {
            case 0:
                addRiddle(riddlesHead, filename);
                break;
            case 1:
                editRiddle(riddlesHead, filename);
                break;
            case 2:
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
                running = false;

                system("cls");

                int roleSelected = 0; 
                bool roleRunning = true;

                while (roleRunning) {
                    displayRoleMenu(roleSelected);

                    char keyRole = _getch();

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
                                running = true;
                            }
                            else {
                                cout << "Log in filed" << endl;
                            }
                        }
                        else if (roleSelected == 1) {  
                            vector<string> userOptions = { "Login", "Register" };
                            int userSelected = 0;
                            bool userRunning = true;

                            while (userRunning) {
                            system("cls");  
                            cout << "=== User Options ===\n";
                            for (int i = 0; i < userOptions.size(); ++i) {
                                if (i == userSelected)
                                    cout << "> " << userOptions[i] << " <\n";
                                else
                                    cout << userOptions[i] << endl;
                            }

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
                                            userRunning = false;
                                            startFilteredRiddle(riddlesHead);
                                          
                                        }
                                        else {
                                            cout << "Failed to login!\n";
                                            system("pause");
                                        }
                                    }
                                        else if (userSelected == 1) {  
                                        int result = userRegister(users);
                                        if (result == 1) {
                                            cout << "Registration successful!\n";
                                        }
                                        else if (result == 0) {
                                            cout << "Username already exists.\n";
                                        }
                                        else if (result == -1) {
                                            cout << "Error saving user data.\n";
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

