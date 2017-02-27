#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <iostream>

#include "stack.h"
#include "helper.h"

using namespace std;

/*
 * This file is responsible for handling the pushing functionality of this utility.
 */

void printUsageHelp(const char *name)
{
	cerr << "usage: <" << name << "> [-r] <dirpath>\n";
}

int main(int argc, char* argv[])
{
	// Sanity checks arguments
	if (argc < 2)
	{
		printUsageHelp(argv[0]);
		exit(-1);
	}

	int shmid;
	key_t key;
	Stack* stack;
	StackAction action = PUSH;

	// Get key for shared memory
	key = ftok(KEYPATHNAME, KEYRANDBYTE);

	// Process command line arguments
	bool removeFlag = false;
	int option = 0;
	while ((option = getopt(argc, argv, "r")) != -1)
	{
		switch (option)
		{
		case 'r':
			removeFlag = true;
			break;
		default:
			printUsageHelp(argv[0]);
			exit(-1);
		}
	}

	// If -r option was supplied then deallocate the shared memory
	if (removeFlag)
	{
		shmid = getSharedMemory(key, IPC_CREAT | 0666);
		deallocateSharedMemory(shmid);
		cerr << "shmid " << shmid << " deallocated\n";
		exit(0);
	}

	// Sanity check on the argument if it's a valid directory or file
	struct stat info;
	if (stat(argv[1], &info) != 0)
	{
		perror("stat");
		exit(-1);
	}

	// Produce error if argv[1] is not a directory.
	if (!info.st_mode & S_IFDIR)
	{
		cerr << "error: '" << argv[1] << "' is not a directory\n";
		exit(-1);
	}

	shmid = getSharedMemory(key, IPC_CREAT | 0666);
	stack = attachSharedMemory(shmid, action);

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
