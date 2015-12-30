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
	printf("getting stack ptr from memory\n");
	stack = (Stack*) shmat(shmid, NULL, 0);
	printf("stack->size = %i\n", stack->size);
	if (stack->size == 0)
	{
		printf("initializing new stack\n");
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

int main(int argc, char* argv[])
{
	// Sanity checks arguments
	if (argc < 2)
	{
		printf("usage: <%s> [-r] <%s>\n", argv[0], "directory path");
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
				printf("usage: <%s> [-r] <%s>\n", argv[0], "directory path");
				exit(-1);
		}
	}

	// If -r option was supplied then deallocate the shared memory
	if (removeFlag)
	{
		getSharedMemory();
		deallocateSharedMemory();
		printf("shmid %i deallocated\n", shmid);
		exit(0);
	}

	// Sanity check on the argument if it's a valid directory or file
	struct stat info;
	if (stat(argv[1], &info) != 0)
	{
		//perror("stat");
		printf("error: '%s' is not a file or directory\n", argv[1]);
		exit(-1);
	}

	if (info.st_mode & S_IFDIR)
		printf("is directory\n");
	else
	{
		printf("error: '%s' is not a directory\n", argv[1]);
		exit(-1);
	}

	getSharedMemory();
	attachSharedMemory();

	// Convert relative path to full path
	ElemStack elem;
	char resolvedPath[PATH_MAX];

	realpath(argv[1], resolvedPath);
	printf("resolvedPath = %s\n", resolvedPath);

	// Copy resolved path to instance of stack element
	strncpy(elem.path, resolvedPath, strlen(resolvedPath)+1);

	// Push full path to stack
	stackPush(stack, elem);
	printf("stack size: %i\n", stack->size);

	return 0;
}