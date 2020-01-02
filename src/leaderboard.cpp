#include "include/leaderboard.h"
#include "include/shared.h"

Leaderboard::Leaderboard() {
	names = static_cast<std::string*>(malloc(1));
	scores = static_cast<int32*>(malloc(1));
	filename = "";
	count = 0;
}

Leaderboard::~Leaderboard() {
	// C and C++ pointers are incompatible perhaps
	//free(names);
	//free(scores);
}

bool Leaderboard::loadFromFile(std::string file) {
	filename = file;
	FILE *f = fopen(filename.c_str(), "rb");
	if(!f) {
		logger(ERROR, "Couldn't open " + filename + " for reading");
		return false;
	}

	char *line = nullptr;
	size_t size = 0;
	while(getline(&line, &size, f) != -1) {
		count++;
		std::string *n = static_cast<std::string*>(calloc(count, sizeof(std::string)));
		if(!n) {
			logger(ERROR, "Realloc fails at __LINE__");
			return false;
		}
		memcpy(n, names, sizeof(std::string)*(count-1));
		free(names);
		// getline reads newlines as well, so this is just to avoid fuckups
#ifndef __WIN32__
		line[strlen(line)-1] = 0x00;
#endif
		n[count-1] = line;

		delete line;
		line = nullptr;
		size = 0;

		int32 *s = static_cast<int32*>(calloc(count, sizeof(int32)));
		if(!s) {
			logger(ERROR, "Realloc fails at __LINE__");
			return false;
		}
		memcpy(s, scores, sizeof(int32)*(count-1));
		free(scores);

		if(getline(&line, &size, f) == -1) {
			logger(ERROR, "Reading score at __LINE__");
			return false;
		}
		if(sscanf(line, "%d", &s[count-1]) != 1) {
			logger(ERROR, "Parsing number at __LINE__");
			return false;
		}

		names=n;
		scores=s;

		delete line;
		line = nullptr;
		size = 0;
	}

	fclose(f);
	return true;
}

// no need for sorting because it's already done by this function,
// unless the DB is unreliable, in which case, stop corrupting the f-ing files
bool Leaderboard::append(std::string name, int32 score) {
	// first we search if the name exists in the leaderboard
	uint32 whoMatches = UINT_MAX;
	for(uint32 i=0; i<count; i++) {
		if(name == names[i]) {
			whoMatches = i;
			break;
		}
	}

	std::string *n = nullptr;
	int32 *s = nullptr;

	// get the first person whos below the new score
	uint32 whosMax = UINT_MAX;
	for(uint32 i=0; i<count; i++) {
		if(scores[i] < score) {
			whosMax = i;
			break;
		}
	}

	if(whoMatches == UINT_MAX) {
		if(whosMax == UINT_MAX) whosMax = count;

		n = static_cast<std::string*>(calloc(++count, sizeof(std::string)));
		if(!n) {
			logger(ERROR, "Realloc fails at __LINE__");
			return false;
		}
		memcpy(n, names, sizeof(std::string)*whosMax);
		memcpy(&n[whosMax+1], &names[whosMax], sizeof(std::string)*(count-whosMax-1));
		n[whosMax] = name;
		free(names);

		s = static_cast<int32*>(calloc(count, sizeof(int32)));
		if(!n) {
			logger(ERROR, "Realloc fails at __LINE__");
			return false;
		}
		memcpy(s, scores, sizeof(int32)*whosMax);
		memcpy(&s[whosMax+1], &scores[whosMax], sizeof(int32)*(count-whosMax-1));
		s[whosMax] = score;
		free(scores);

		names = n;
		scores = s;
		return true;
	}

	// if the user already has a higher score, gtfo
	if(scores[whoMatches] >= score)
		return true;

	// move everyone one unit down
	if(whosMax-whoMatches>0) {
		for(uint32 i=whosMax; i<whoMatches; i++) {
			names[i+1] = names[i];
			scores[i+1] = scores[i];
		}
	}

	// and put the new entry
	names[whosMax] = name;
	scores[whosMax] = score;

	return true;
}

bool Leaderboard::write(void) {
	FILE *f = fopen(filename.c_str(), "w");
	if(!f) {
		logger(ERROR, "Couldn't open " + filename + " for writing");
		return false;
	}

	for(uint32 i=0; i<count; i++) {
		fprintf(f, "%s\n%d\n", names[i].c_str(), scores[i]);
	}

	fclose(f);
	return true;
}

// these functions exists so accidental writes don't happen
int32 Leaderboard::getScore(uint32 entry) {
	return scores[entry];
}

std::string Leaderboard::getName(uint32 entry) {
	return names[entry];
}

uint32 Leaderboard::getCount(void) {
	return count;
}
