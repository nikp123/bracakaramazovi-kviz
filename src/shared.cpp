#include <cstring>
#include "include/shared.h"

#ifdef __WIN32__
	// a shitty getline substitute function
	ssize_t getline(char **lineptr, size_t *n, FILE *stream) {
		// fuck windows, it gets the shitty security exploits
		char *buffer = static_cast<char*>(malloc(1000));
		uint16 count = 0;
		ssize_t retVal = 0;
		while(1) {
			int16 a = fgetc(stream);
			switch(a) {
				default:
					buffer[count] = a;
					break;
				case '\n':
				case '\r':
				case '\0':
					buffer[count] = 0x00;
					break;
				case EOF:
					buffer[count] = 0x00;
					retVal = -1;
					break;
			}
			if(!buffer[count]) break;
			count++;
		}

		char *k = static_cast<char*>(realloc(buffer, strlen(buffer)));
		buffer = k;

		(*n) = count;
		(*lineptr) = buffer;
		return retVal ? retVal : count;
	}
#endif

static std::string errorMsgs[] = {"[INFO] ", "[ERROR] ",
   "[FATAL ERROR] ", "[WARN] ", "[CRITICAL WARNING]", "[LOG] "
   "[LOG] ", "[LOG] "};

void logger(uint32 STATUS, std::string message) {
	std::cout << errorMsgs[STATUS] << message << std::endl;

	if(STATUS == FATALERROR) exit(EXIT_FAILURE);
}

std::string ReplaceString(std::string subject,
								 const std::string& search,
								 const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

// convert directory
std::string cDir(std::string dir) {
#ifdef __WIN32__
	return ReplaceString(dir, "/", "\\");
#else
	return dir;
#endif
}
