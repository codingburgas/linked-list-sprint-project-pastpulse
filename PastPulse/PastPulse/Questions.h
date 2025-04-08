#pragma once
#include "pch.h"

struct Question
{

	string text;
	vector<string> answers;
};

vector<Question> loadQuestions(const string& filename);




