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
    cout << endl << selectedRiddle["introduction"].get<string>() << endl;

    list<string> facts;
    for (const auto& fact : selectedRiddle["facts"]) {
        facts.push_back(fact.get<string>());
    }
    cout << "\nFacts:\n";
    for (const auto& fact : facts) {
        cout << "- " << fact << endl;
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
        cout << endl<<"Final chance! Enter your last answer: ";
        getline(cin, userAnswer);
        if (userAnswer == selectedRiddle["answer"].get<string>()) {
            correct = true;
        }
    }
    if (correct) {
        cout << "Congratulations! Your answer is correct!"<<endl;
    }
    else {
        cout << "Wrong answer. The correct one is: " << selectedRiddle["answer"].get<string>() << endl;
    }

}