#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "stack.h"

using namespace std;

/*
 * This file is responsible for handling the popping functionality of this utility.
 */

key_t key;
int shmid;
Stack* stack;

/* 
 * The following functions: getSharedMemory(), attackSharedMemory(), and deallocateSharedMemory()
 * are wrappers for the shared memory system calls. This is for cleaner code and less clutter.
 */
void getSharedMemory()
{
	if ((shmid = shmget(key, sizeof(Stack), IPC_EXCL)) == -1)
	{
		perror("shmget");
		fprintf(stderr, "%s\n", "stack may not have been allocated, push to stack first");
		exit(-1);
	}
	return;
}

void attachSharedMemory()
{
	stack = (Stack*) shmat(shmid, NULL, 0);
	if (stack == NULL)
	{
		perror("shmat");
		exit(-1);
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
	// Get key for shared memory
	key = ftok("gpushd", 'Q');

	// Get shared memory and attach it to <stack> 
	getSharedMemory();	
	attachSharedMemory();

	/* 
	 * Pop a directory from the stack and print it out.
	 * The gpopdir() function we added to the bashrc (with configure script)
	 * file will take this output and feed it into cd.
	 * If the stack is empty, it will just return the current directory (".").
	 */
	ElemStack elem = stackPop(stack);
	printf("%s", elem.path);

	return 0;
}