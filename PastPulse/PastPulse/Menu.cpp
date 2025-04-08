#include "Menu.h"
#include "User.h"
#include "Admin.h"
#include "Riddle.h"
#include "Validation.h"
#include "Colors.h"

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
    setColor(YELLOW, BLACK);
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
        setColor(LIGHT_PURPLE, BLACK);
        printCentered("...............", startY);
        printCentered(":  > START <  :", startY + 1);
        printCentered("...............", startY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", startY);
        printCentered(":    START    :", startY + 1);
        printCentered("...............", startY + 2);
        resetColor();
    }

    newLine(1);


    if (selected == 1) {
        setColor(LIGHT_PURPLE, BLACK);
        printCentered("...............", leaveY);
        printCentered(":  > LEAVE <  :", leaveY + 1);
        printCentered("...............", leaveY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", leaveY);
        printCentered(":    LEAVE    :", leaveY + 1);
        printCentered("...............", leaveY + 2);
        resetColor();
    }
}

void displayRoleMenu(int selected) {
    system("cls");

    setColor(YELLOW, BLACK);
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
        setColor(LIGHT_BLUE, BLACK);
        printCentered("...............", adminOptionY);
        printCentered(":  > ADMIN <  :", adminOptionY + 1);
        printCentered("...............", adminOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", adminOptionY);
        printCentered(":    ADMIN    :", adminOptionY + 1);
        printCentered("...............", adminOptionY + 2);
        resetColor();
    }

    newLine(1);


    if (selected == 1) {
        setColor(LIGHT_BLUE, BLACK);
        printCentered("...............", userOptionY);
        printCentered(":  > USER <   :", userOptionY + 1);
        printCentered("...............", userOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", userOptionY);
        printCentered(":    USER    :", userOptionY + 1);
        printCentered("...............", userOptionY + 2);
        resetColor();
    }
}
void displayUserOptions(int selected) {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("   _    _                  ____        _   _                 ", 1);
    printCentered("  | |  | |                / __ \\      | | (_)                ", 2);
    printCentered("  | |  | |___  ___ _ __  | |  | |_ __ | |_ _  ___  _ __  ___ ", 3);
    printCentered("  | |  | / __|/ _ \\ '__| | |  | | '_ \\| __| |/ _ \\| '_ \\/ __|", 4);
    printCentered("  | |__| \\__ \\  __/ |    | |__| | |_) | |_| | (_) | | | \\__ \\", 5);
    printCentered("   \\____/|___/\\___|_|     \\____/| .__/ \\__|_|\\___/|_| |_|___/", 6);
    printCentered("                                | |                          ", 7);
    printCentered("                                |_|                          ", 8);
    resetColor();

    newLine(1);

    int loginOptionY = 11;
    int registerOptionY = 14;

    if (selected == 0) {
        setColor(LIGHT_YELLOW, BLACK);
        printCentered("...............", loginOptionY);
        printCentered(":  > LOGIN <  :", loginOptionY + 1);
        printCentered("...............", loginOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", loginOptionY);
        printCentered(":    LOGIN    :", loginOptionY + 1);
        printCentered("...............", loginOptionY + 2);
        resetColor();
    }

    newLine(1);

    if (selected == 1) {
        setColor(LIGHT_YELLOW, BLACK);
        printCentered("...............", registerOptionY);
        printCentered(":  > SIGNUP < :", registerOptionY + 1);
        printCentered("...............", registerOptionY + 2);
        resetColor();
    }
    else {
        setColor(GRAY, BLACK);
        printCentered("...............", registerOptionY);
        printCentered(":    SIGNUP   :", registerOptionY + 1);
        printCentered("...............", registerOptionY + 2);
        resetColor();
    }
}

void displayLoginTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("   __       _____     ______ _______ __   __  ", 1);
    printCentered("  |  |    /  ___  \\ /  _____|__   __ |  \\ |  |  ", 2);
    printCentered("  |  |   |  |   |  |  | ____   |  |  |   \\|  |  ", 3);
    printCentered("  |  |   |  |   |  |  ||_   |  |  |  |  .    |  ", 4);
    printCentered("  |  |___|  |___|  |  |__|  |__|  |__|  |\\   |  ", 5);
    printCentered(" |______ \\_______/ \\_______|________|__| \\__|  ", 6);
    printCentered("                                              ", 8);
    resetColor();

    newLine(1);
}

void displaySignUpTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("      ______ ______ _____ _   _ _    _ _____", 1);
    printCentered("      / _____|_  __/  ____| \\ | | |  | |  __ \\", 2);
    printCentered("     |  (__    | ||  |  __|  \\| | |  | | |__) |", 3);
    printCentered("     \\___  \\  | ||  | |_ | . ` | |  | |  ___/", 4);
    printCentered(" _____) |_| ||  |__| | |\\  | |__| | |", 5);
    printCentered("|______/|_____\\______|_| \\_|\\____/|_|", 6);
    printCentered("                                              ", 8);
    resetColor();

    newLine(1);
}

void displayRiddleTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("  _____  _____ _____  _____  _      ______ ", 1);
    printCentered(" |  __ \\|_   _|  __ \\|  __ \\| |    |  ____|", 2);
    printCentered(" | |__) | | | | |  | | |  | | |    | |__   ", 3);
    printCentered(" |  _  /  | | | |  | | |  | | |    |  __|  ", 4);
    printCentered(" | | \\ \\ _| |_| |__| | |__| | |____| |____ ", 5);
    printCentered(" |_|  \\_\\_____|_____/|_____/|______|______|", 6);
    printCentered("                                              ", 8);
    resetColor();

    newLine(1);
}

void displayAdminTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("           _____  __  __ _____ _   _ ", 1);
    printCentered("     /\\   |  __ \\|  \\/  |_   _| \\ | |", 2);
    printCentered("    /  \\  | |  | | \\  / | | | |  \\| |", 3);
    printCentered("   / /\\ \\ | |  | | |\\/| | | | | . ` |", 4);
    printCentered("  / ____ \\| |__| | |  | |_| |_| |\\  |", 5);
    printCentered(" /_/    \\_\\_____/|_|  |_|_____|_| \\_|", 6);
    printCentered("                                              ", 8);
    resetColor();

    newLine(1);
}

void displaySelectTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered("    _____ ______ _      ______ _____ _______", 1);
    printCentered("  / ____|  ____| |    |  ____/ ____|__   __|", 2);
    printCentered("  | (___ | |__  | |    | |__ | |       | |  ", 3);
    printCentered("  \\___ \\|  __| | |    |  __|| |       | |   ", 4);
    printCentered("  ____) | |____| |____| |___| |____   | |   ", 5);
    printCentered(" |_____/|______|______|______\\_____|  |_|   ", 6);
    printCentered("                                              ", 8);
    resetColor();

    newLine(1);
}

void displayFactsTitle() {
    system("cls");

    setColor(YELLOW, BLACK);
    printCentered(" ______      _____ _______ _____ ", 1);
    printCentered("|  ____/\\   / ____|__   __/ ____|", 2);
    printCentered("| |__ /  \\ | |       | | | (___  ", 3);
    printCentered("|  __/ /\\ \\| |       | |  \\___ \\ ", 4);
    printCentered(" | | / ____ \\ |____   | |  ____) |", 5);
    printCentered(" |_|/_/    \\_\\_____|  |_| |_____/ ", 6);
    printCentered("                                              ", 8);
    resetColor();

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

