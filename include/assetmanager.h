#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "questionbank.h"
#include "leaderboard.h"
#include "shared.h"

class AssetManager
{
	public:
		AssetManager();
		~AssetManager();

	private:
		std::string appDir;
		std::string questionBankFile = "questions.data";
		bool getApplicationDirectory(void);
		bool loadQuestionbanks(void);
		bool loadLeaderboards(void);
};

#endif // ASSETMANAGER_H

extern QuestionBank easy;
extern QuestionBank medium;
extern QuestionBank hard;

// difficulty mode
extern Leaderboard normal;

// progressive mode
extern Leaderboard group;

// additive time mode
extern Leaderboard countdown;
