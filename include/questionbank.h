#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H
#include <iostream>
#include <cstring>
#include <climits>
#include "shared.h"

class QuestionBank
{
	public:
		QuestionBank();
		~QuestionBank();

		bool loadFromFile(std::string filename);

		void clear(void);
		uint32 number(void);

		bool addQuestion(const std::string& question, const std::string answers[4], uint8 correct);
		question* getQuestion(uint32 number);
		bool deleteQuestion(uint32 number);

		bool initQuestionList(void);
		uint32 getRandomQuestion(void);

		std::string n;

	private:
		uint32 qC;
		question *q;
		bool *activ;
};

#endif // QUESTIONBANK_H
