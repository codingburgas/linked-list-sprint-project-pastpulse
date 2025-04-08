#include "Simulator.h"
#include "Menu.h"
#include "Riddle.h"
#include "Questions.h"

void leading() {
    system("cls");
    int score = 0;
    int choice;
    string filename = "riddles.json";
    Riddle* riddlesHead = loadRiddlesFromFile(filename);
    
    vector<Question> questions = loadQuestions("questions.txt");
    for (const auto& q : questions) {  //Iterate through each question in the vector
        cout << "\n" << q.text << endl;
        for (int i = 0; i < q.answers.size(); i++) {
            cout << i + 1 << ". " << q.answers[i] << endl;  //Display the possible answers
        }
        while (true) {  // Loop until the user enters a valid choice
            cout << "Enter your choice (1-3): ";
            cin >> choice;
            if (choice < 1 || choice > 3) {
                cout << "Invalid choice! Please choose a valid option (1-3).";
            }
            else {
                score += choice;
                break;
            }

        }
    }

    cout << "\nCalculating your leadership success...\n";
    this_thread::sleep_for(chrono::seconds(2));  //Pause the execution for 2 seconds to simulate calculation

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

    if (choice == 1)
    {
        startFilteredRiddle(riddlesHead);
    }
    else if (choice == 2)
    {
        menu();
    }
    else
    {
        cout << "Invalid choice! Try again: " << endl;
        cin >> choice;
    }
}