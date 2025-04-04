#ifndef QUESTIONS_H
#define QUESTIONS_H
#include "pch.h"


struct Question
{

	string text;
	vector<string> answers;
};

vector<Question> loadQuestions(const string& filename);


#endif // QUESTIONS_H


