#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "lib/helper.h"
#include "lib/stack.h"

using namespace std;

/*
 * This file is responsible for handling the pushing functionality of this
 * utility.
 */

void printUsageHelp(char const *name)
{
	cerr << "Usage: " << name << " [-h | -r] <dirpath>\n" <<
	        "\n" <<
	        "Options:\n" <<
	        " -h            Print this help.\n" <<
	        " -r            Deallocate shared memory (stack).\n";
}

int main(int argc, char *argv[])
{
	// Sanity checks arguments
	if (argc < 2) {
		printUsageHelp(argv[0]);
		exit(-1);
	}

	int shmid;
	StackAction const action = PUSH;

	// Get key for shared memory
	key_t const key = ftok(KEYPATHNAME, KEYRANDBYTE);

	// Process command line arguments
	bool removeFlag = false;
	int option = 0;
	while ((option = getopt(argc, argv, "rh")) != -1) {
		switch (option) {
		case 'r':
			removeFlag = true;
			break;
		case 'h':
			printUsageHelp(argv[0]);
			exit(0);
		default:
			printUsageHelp(argv[0]);
			exit(-1);
		}
	}

	// If -r option was supplied then deallocate the shared memory
	if (removeFlag) {
		shmid = getSharedMemory(key, IPC_CREAT | 0666);
		deallocateSharedMemory(shmid);
		cerr << "shmid " << shmid << " deallocated\n";
		exit(0);
	}

	// Sanity check on the argument if it's a valid directory or file
	struct stat info;
	if (stat(argv[1], &info) != 0) {
		perror("stat");
		exit(-1);
	}

	// Produce error if argv[1] is not a directory.
	if (!S_ISDIR(info.st_mode)) {
		cerr << "error: '" << argv[1] << "' is not a directory\n";
		exit(-1);
	}

	shmid = getSharedMemory(key, IPC_CREAT | 0666);
	Stack * const stack = attachSharedMemory(shmid, action);

	// Convert relative path to full path
	ElemStack elem;
	char resolvedPath[PATH_MAX];

	realpath(argv[1], resolvedPath);

	// Copy resolved path to instance of stack element
	// Don't forget to copy over the null terminator as well.
	strncpy(elem.path, resolvedPath, strlen(resolvedPath)+1);

	// Push full path to stack
	stackPush(stack, elem);

	return 0;
}
