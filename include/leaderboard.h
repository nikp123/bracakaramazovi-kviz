#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define _GNU_SOURCE
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include "shared.h"

class Leaderboard
{
	public:
		Leaderboard();
		~Leaderboard();

		int32 getScore(uint32 entry);
		std::string getName(uint32 entry);
		uint32 getCount(void);

		bool loadFromFile(std::string filename);
		bool append(std::string name, int32 score);
		bool write(void);
	private:
		uint32 count = 0;
		std::string filename;
		std::string *names;
		int32 *scores;
};

#endif // LEADERBOARD_H
