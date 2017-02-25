#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "stack.h"

using namespace std;

/*
 * This file is responsible for handling the pushing functionality of this utility.
 */

// Global variables
key_t key;
int shmid;
Stack* stack;

/*
 * The following functions: getSharedMemory(), attackSharedMemory(), and deallocateSharedMemory()
 * are wrappers for the shared memory system calls. This is for cleaner code and less clutter.
 */
void getSharedMemory()
{
	if ((shmid = shmget(key, sizeof(Stack), IPC_CREAT | 0666)) == -1)
	{
		perror("shmget");
		exit(-1);
	}
	return;
}

void attachSharedMemory()
{
	stack = (Stack*) shmat(shmid, NULL, 0);
	if (stack->size == 0)
	{
		stackInitialize(stack);
	}
	return;
}

void deallocateSharedMemory()
{
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl");
		exit(-1);
	}
	return;
}

void printUsageHelp()
{
	cerr << "usage: <" << argv[0] << "> [-r] <dirpath>\n";
}

int main(int argc, char* argv[])
{
	// Sanity checks arguments
	if (argc < 2)
	{
		printUsageHelp();
		exit(-1);
	}

	// Get key for shared memory
	key = ftok("gpushd", 'Q');

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
			printUsageHelp();
			exit(-1);
		}
	}

	// If -r option was supplied then deallocate the shared memory
	if (removeFlag)
	{
		getSharedMemory();
		deallocateSharedMemory();
		cerr << "shmid " << shmid << " deallocated\n";
		exit(0);
	}

	// Sanity check on the argument if it's a valid directory or file
	stat info;
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

	getSharedMemory();
	attachSharedMemory();

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
