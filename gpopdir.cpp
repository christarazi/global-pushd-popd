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

key_t key;
int shmid;
Stack* stack;

void getSharedMemory()
{
	if ((shmid = shmget(key, sizeof(Stack), IPC_EXCL)) == -1)
	{
		perror("shmget");
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

	getSharedMemory();
	attachSharedMemory();

	//printf("got stack size = %i\n", stack->size);
	// for (int i = 0; i < stack->size; ++i)
	// {
	// 	ElemStack elem = stackPop(stack);
	// 	printf("%s\n", elem.path);
	// }

	ElemStack elem = stackPop(stack);
	// if (chdir(elem.path) == -1)
	// {
	// 	perror("chdir");
	// }
	printf("%s", elem.path);

	return 0;
}