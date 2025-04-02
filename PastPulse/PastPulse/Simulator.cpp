#include "Simulator.h"
#include "Menu.h"
void simulator()
{
    system("cls");
    hideCursor();
    ifstream file("riddles.json");
    if (!file) {
        cout << "Failed to open the file";
    }

    json j;
    file >> j;
    srand(time(nullptr));
    int randomIndex = rand() % j.size();
    json selectedRiddle = j[randomIndex];
    printCentered("  _________      .__                ___________.__             __________.__    .___  .___.__          ", 5);
    printCentered(" /   _____/ ____ |  |___  __ ____   \\__    ___/|  |__   ____   \\______   \\__| __| _/__| _/|  |   ____  ", 6);
    printCentered(" \\_____  \\ /  _ \\|  |\\  \\/ // __ \\    |    |   |  |  \_/ __ \\   |       _/  |/ __ |/ __ | |  | _/ __ \\ ", 7);
    printCentered(" /        (  <_> )  |_\\   /\\  ___/    |    |   |   Y  \\  ___/   |    |   \\  / /_/ / /_/ | |  |_\\  ___/ ", 8);
    printCentered("/_______  /\____/|____/\\_/  \\___  >   |____|   |___|  /\\___  >  |____|_  /__\\____ \\____ | |____/\\___  >", 9);
    printCentered("        \\/                      \\/                  \\/     \\/          \\/        \\/    \\/           \\/ ", 10);
    cout << endl << selectedRiddle["introduction"].get<string>() << endl;

    list<string> facts;
    for (const auto& fact : selectedRiddle["facts"]) {
        facts.push_back(fact.get<string>());
    }

    string userAnswer;
    bool correct = false;
    list<string> hints;
    for (const auto& hint : selectedRiddle["hints"]) {
        hints.push_back(hint.get<string>());
    }
    cout << endl << "Hints:" << endl;
    for (const auto& hint : hints) {
        cout << "- " << hint << endl;
        cout << "Your answer: ";
        getline(cin, userAnswer);
        if (userAnswer == selectedRiddle["answer"].get<string>()) {
            correct = true;
            break;
        }
    }
    if (!correct) {
        cout << endl << "Final chance! Enter your last answer: ";
        getline(cin, userAnswer);
        if (userAnswer == selectedRiddle["answer"].get<string>()) {
            correct = true;
        }
    }
    if (correct) {
        cout << "Congratulations! Your answer is correct!" << endl;
    }
    else {
        cout << "Wrong answer. The correct one is: " << selectedRiddle["answer"].get<string>() << endl;
    }
    cout << "\nHere is some additional information about the uprising:\n";
    for (const auto& fact : facts) {
        cout << "- " << fact << endl;
    }
}