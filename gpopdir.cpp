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
 * This file is responsible for handling the popping functionality of this utility.
 */

void printUsageHelp(const char *name)
{
	cerr << "usage: <" << name << "> [-l]\n";
}

int main(int argc, char* argv[])
{
	// Sanity checks arguments
	if (argc < 1 || argc > 2)
	{
		printUsageHelp(argv[0]);
		exit(-1);
	}

	int shmid;
	key_t key;
	Stack* stack;
	StackAction action = POP;

	// Get key for shared memory
	key = ftok("gpushd", 'Q');

	// Get shared memory and attach to stack.
	shmid = getSharedMemory(key, IPC_EXCL);
	stack = attachSharedMemory(shmid, action);

	// Process command line arguments
	int option = 0;
	while ((option = getopt(argc, argv, "l")) != -1)
	{
		switch (option)
		{
		case 'l':
			stackList(stack);
			exit(0);
		default:
			printUsageHelp(argv[0]);
			exit(-1);
		}
	}

	/*
	 * Pop a directory from the stack and print it out.
	 * The gpopdir() function we added to the bashrc (with configure script)
	 * file will take this output and feed it into the cd built-in command.
	 * If the stack is empty, it will just return the current directory (".").
	 */
	ElemStack elem = stackPop(stack);
	cout << elem.path;

	return 0;
}
