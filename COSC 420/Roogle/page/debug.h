#include <assert.h>
#ifndef DEBUG
#define DEBUG

static bool debug = true;
static bool logtofile = true;

bool argvContainsInt(int argc, char** argv, int query) {
	for(int a = 1; a < argc; a++) {
		if(query == atoi(argv[a]))
			return true;
	}
	return false;
}
bool argvContainsString(int argc, char** argv, char* query) {
	for(int a = 1; a < argc; a++) {
		if(strcmp(query, argv[a]) == 0)
			return true;
	}
	return false;
}
bool debugMode(int argc, char** argv) {
	char* str = "-d";
	if(argvContainsString(argc, argv, str))
		return true;
	return false;
}

#endif
