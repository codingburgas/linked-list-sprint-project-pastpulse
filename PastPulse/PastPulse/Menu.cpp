#include "Menu.h"
#include "User.h"

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

    printCentered("  _____          _   _____       _           ", 1);
    printCentered(" |  __ \\        | | |  __ \\     | |          ", 2);
    printCentered(" | |__) __ _ ___| |_| |__) _   _| |___  ___  ", 3);
    printCentered(" |  ___/ _` / __| __|  ___| | | | / __|/ _ \\ ", 4);
    printCentered(" | |  | (_| \\__ | |_| |   | |_| | \\__ |  __/ ", 5);
    printCentered(" |_|   \\__,_|___/\\__|_|    \\__,_|_|___/\\___| ", 6);
    newLine(2);

    int startY = 9;
    int leaveY = 13;

    printCentered("===============", startY);
    printCentered("=    START    =", startY + 1);
    printCentered("===============", startY + 2);
    newLine(1);

    printCentered("===============", leaveY);
    printCentered("=    LEAVE    =", leaveY + 1);
    printCentered("===============", leaveY + 2);

    
    if (selected == 0) {
        printCentered("> START <", startY + 1);
    }
    else {
        printCentered("> LEAVE <", leaveY + 1);
    }
}


void menu() {
    int selected = 0; 
    bool running = true;

    while (running) {
        displayMenu(selected);

        char key = _getch();  
        switch (key) {
        case 72:  
            selected = (selected == 0) ? 1 : 0;
        case 80: 
            selected = (selected == 1) ? 0 : 1; 
            break;
        case 13:  
            if (selected == 0) {
                system("cls");
                printCentered("Game Starting...", 10);
                running = false;
            }
            else {
                system("cls");
                printCentered("Goodbye! You can close the app by pressing any key button...", 10);
                running = false;
            }
            break;
        }
    }
}
