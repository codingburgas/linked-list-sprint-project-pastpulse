#include "Simulator.h"
#include "Menu.h"
#include "Riddle.h"
void leading() {
    system("cls");
    int score = 0;
    int choice;
    string filename = "riddles.json";
    Riddle* riddlesHead = loadRiddlesFromFile(filename);
    cout << "\nHow many rebels will you have?" << endl;
    cout << "1. Up to 20,000 " << endl;
    cout << "2. Between 20,000 and 60,000 " << endl;
    cout << "3. More than 60,000 " << endl;
    cin >> choice;
    score += choice;

    cout << "\nWhat weapons and supplies will you have?" << endl;
    cout << "1. Personal firearms " << endl;
    cout << "2. Bombs and firearms " << endl;
    cout << "3. Modern weapons from allies " << endl;
    cin >> choice;
    score += choice;

    cout << "\nWhat will be your main strategy?" << endl;
    cout << "1. Small battle groups, decentralized command " << endl;
    cout << "2. Guerilla squads with central command " << endl;
    cout << "3. Attacking key locations " << endl;
    cin >> choice;
    score += choice;

    cout << "\nHow will the rebels communicate?" << endl;
    cout << "1. Committees " << endl;
    cout << "2. Couriers " << endl;
    cout << "3. Centralized command " << endl;
    cin >> choice;
    score += choice;

    cout << "\nWill you have external support?" << endl;
    cout << "1. Limited support " << endl;
    cout << "2. Secret backing " << endl;
    cout << "3. Russian support " << endl;
    cin >> choice;
    score += choice;

    cout << "\nHow will you handle betrayal?" << endl;
    cout << "1. Suppress information " << endl;
    cout << "2. Increase security measures " << endl;
    cout << "3. Disciplinary actions " << endl;
    cin >> choice;
    score += choice;

    cout << "\nAre you willing to take responsibility?" << endl;
    cout << "1. Avoid responsibility " << endl;
    cout << "2. Admit guilt but avoid punishment " << endl;
    cout << "3. Take full responsibility " << endl;
    cin >> choice;
    score += choice;

    cout << "\nHow will you keep morale high?" << endl;
    cout << "1. Present the cause as just " << endl;
    cout << "2. Celebrate small victories " << endl;
    cout << "3. Conduct educational campaigns " << endl;
    cin >> choice;
    score += choice;

    cout << "\nCalculating your leadership success...\n";
    this_thread::sleep_for(chrono::seconds(2));

    if (score >= 21) {
        cout << "99% chance of winning the war! You are a great strategist!" << endl;
    }
    else if (score >= 16 && score < 21) {
        cout << "High chance of success! You have strong leadership qualities." << endl;
    }
    else if (score >= 13 && score <= 15) {
        cout << "Moderate success. Your choices are decent, but you may struggle." << endl;
    }
    else if (score <= 12) {
        cout << "Low success rate. Your strategies need improvement." << endl;
    }

    cout << "1. Take a New Riddle" << endl;
    cout << "2. Return to Menu" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
        displayRiddles(riddlesHead);
        break;
    case 2:
        menu();
        break;
    default:
        cout << "Invalid choice! Try again: ." << endl;
        cin >> choice;
        break;
    }
}