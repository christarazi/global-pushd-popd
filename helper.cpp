#include "lib/helper.h"

int getSharedMemory(const key_t key, const int flags)
{
	int ret;
	if ((ret = shmget(key, sizeof(Stack), flags)) == -1)
	{
		perror("shmget");
		exit(ret);
	}

	return ret;
}

Stack* attachSharedMemory(const int shmid, const StackAction action)
{
	Stack* stack = reinterpret_cast<Stack*>(shmat(shmid, NULL, 0));
	switch (action)
	{
	case PUSH:
		if (!stack)
		{
			perror("shmat");
			exit(-1);
		}
		break;
	case POP:
		if (stack->size == 0)
			stackInitialize(stack);
		break;
	default:
		exit(-1);
	}

	return stack;
}

void deallocateSharedMemory(const int shmid)
{
	int err;
	if ((err = shmctl(shmid, IPC_RMID, NULL)) == -1)
	{
		perror("shmctl");
		exit(err);
	}
}

