#include "include/assetmanager.h"

QuestionBank easy;
QuestionBank medium;
QuestionBank hard;
QuestionBank ohfuck;

// difficulty mode
Leaderboard normal;

// progressive mode
Leaderboard group;

// additive time mode
Leaderboard countdown;

bool AssetManager::getApplicationDirectory(void) {
/**
	Cross-platform garbage goes here

	aber ich muss schneller sein
**/
#ifdef __WIN32__
	// because windows is weird
	appDir = ".\\";
#else
	appDir = "./";
#endif
	return true;
}

bool AssetManager::loadQuestionbanks(void) {
	std::string eF = appDir + cDir("assets/easyQuestions"),
				mF = appDir + cDir("assets/mediumQuestions"),
				hF = appDir + cDir("assets/hardQuestions");

	if(!easy.loadFromFile(eF)) {
		logger(FATALERROR, "Couldn't load easy questions!");
		return false;
	}
	easy.n = "Lagana pitanja";
	if(!medium.loadFromFile(mF)) {
		logger(FATALERROR, "Couldn't load medium questions!");
		return false;
	}
	medium.n = "Umjereno teška pitanja";
	if(!hard.loadFromFile(hF)) {
		logger(FATALERROR, "Couldn't load hard questions!");
		return false;
	}
	hard.n = "Teška pitanja";

	return true;
}

bool AssetManager::loadLeaderboards(void) {
	std::string nLF = appDir + cDir("leaderboards/normal"),
				gLF = appDir + cDir("leaderboards/group"),
				cLF = appDir + cDir("leaderboards/countdown");

	if(!normal.loadFromFile(nLF)) {
		logger(ERROR, "Couldn't load "+nLF+" leaderboard!");
		return false;
	}
	if(!group.loadFromFile(gLF)) {
		logger(ERROR, "Couldn't load "+gLF+" leaderboard!");
		return false;
	}
	if(!countdown.loadFromFile(cLF)) {
		logger(ERROR, "Couldn't load "+cLF+" leaderboard!");
		return false;
	}

	return true;
}

AssetManager::AssetManager() {
	// open and parse file from here
	if(!getApplicationDirectory()) {
		logger(FATALERROR, "Make sure that your OS actually works!");
		exit(EXIT_FAILURE);
	}

	if(!loadQuestionbanks()) exit(EXIT_FAILURE);

	loadLeaderboards();
}

AssetManager::~AssetManager() {
	normal.write();
	group.write();
	countdown.write();
}
