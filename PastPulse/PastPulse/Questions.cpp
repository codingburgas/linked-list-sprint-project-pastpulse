#include "Questions.h"
#include "pch.h"



vector<Question> loadQuestions(const string& filename) {
	vector <Question> questions;  //Create an empty vector to store the loaded questions
	ifstream file(filename);  //Open the file for reading
	string line;

	while (getline(file, line)) {  //Read the file line by line
		if (line.empty()) continue;
		Question q;
		q.text = line;

		for (int i = 0; i < 3; i++) {
			if (getline(file, line)) {
				q.answers.push_back(line);
			}
		}

		questions.push_back(q);  //Add the fully populated Question object


	}

	return questions;
}
