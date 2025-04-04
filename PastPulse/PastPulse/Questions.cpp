#include "Questions.h"
#include "pch.h"



vector<Question> loadQuestions(const string& filename) {
	vector <Question> questions;
	ifstream file(filename);
	string line;

	while (getline(file, line)) {
		if (line.empty()) continue;
		Question q;
		q.text = line;

		for (int i = 0; i < 3; i++) {
			if (getline(file, line)) {
				q.answers.push_back(line);
			}
		}

		questions.push_back(q);

	}

	return questions;
}
