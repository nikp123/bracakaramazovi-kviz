#ifndef SHARED_H
#define SHARED_H

#include <iostream>

// Abbreviations so that my life becomes way easier
#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned long
#define umax unsigned long long

#define int8 char
#define int16 short
#define int32 int
#define int64 long
#define imax long long

#define f32 float
#define f64 double

#define TIME 120

#define INFO 0
#define ERROR 1
#define FATALERROR 2
#define WARNING 3
#define CRITICALWARN 4
#define LOGLVL1 5
#define LOGLVL2 6
#define LOGLVL3 7

struct questionStruct {
	std::string text;
	std::string answer[4];
	uint8 correct;
};

typedef struct questionStruct question;

// define a pile of functioins

#ifdef __WIN32__
	extern ssize_t getline(char **lineptr, size_t *n, FILE *stream);
#endif

extern void logger(uint32 STATUS, std::string message);
extern std::string ReplaceString(std::string subject,
								 const std::string& search,
								 const std::string& replace);

// convert directory
extern std::string cDir(std::string dir);

#endif // SHARED_H
