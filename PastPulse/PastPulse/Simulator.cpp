#include "Simulator.h"
#include "Menu.h"
#include "Riddle.h"
#include "Questions.h"
#include "Colors.h"

void leading() {
    system("cls");
    int score = 0;
    string choice;
    string filename = "riddles.json";
    Riddle* riddlesHead = loadRiddlesFromFile(filename);
    
    vector<Question> questions = loadQuestions("questions.txt");
    printCentered("  _                    _               _         __          ___       ", 1);
    printCentered(" | |                  | |             | |        \\ \\        / (_)      ", 2);
    printCentered(" | |     ___  __ _  __| |  _   _ ___  | |_ ___    \\ \\  /\\  / / _ _ __  ", 3);
    printCentered(" | |    / _ \\/ _` |/ _` | | | | / __| | __/ _ \\    \\ \\/  \\/ / | | '_ \\ ", 4);
    printCentered(" | |___|  __/ (_| | (_| | | |_| \\__ \\ | || (_) |    \\  /\\  /  | | | | |", 5);
    printCentered(" |______\\___|\\__,_|\\__,_|  \\__,_|___/  \\__\\___/      \\/  \\/   |_|_| |_|", 6);
     
    newLine(2);
    for (const auto& q : questions) {
        setColor(YELLOW, BLACK);
        cout << "\n" << q.text << endl;
        resetColor();
        for (int i = 0; i < q.answers.size(); i++) {
            cout << i + 1 << ". " << q.answers[i] << endl;
        }

        while (true) {
            setColor(YELLOW, BLACK);
            cout << "Enter your choice (1-3): ";
            resetColor();
            cin >> choice;

            try {
                int userChoice = stoi(choice);
                if (userChoice < 1 || userChoice > 3) {
                    throw out_of_range("Invalid choice! Please choose a valid option (1-3).");
                }
                score += userChoice;
                break;
            }
            catch (invalid_argument&) {
                cout << "Invalid input! Please enter a number between 1 and 3.\n";
            }
            catch (out_of_range& e) {
                cout << e.what() << endl;
            }
        }
    }

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

    else {
        cout << "Low success rate. Your strategies need improvement." << endl;
    }

    while (true) {
        cout << "\n1. Take a New Riddle" << endl;
        cout << "2. Return to Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            int finalChoice = stoi(choice);
            if (finalChoice == 1) {
                startFilteredRiddle(riddlesHead);
                break;
            }

            else if (finalChoice == 2) {
                menu();
                break;
            }

            else {
                throw out_of_range("Invalid choice! Please choose 1 or 2.");
            }
        }

        catch (invalid_argument&) {
            cout << "Invalid input! Please enter 1 or 2.\n";
        }

        catch (out_of_range& e) {
            cout << e.what() << endl;
      }
    }
}

