#include "../include/helper.h"

int getSharedMemory(key_t const key, int const flags)
{
	int ret;
	if ((ret = shmget(key, sizeof(Stack), flags)) == -1) {
		perror("shmget");
		exit(ret);
	}

	return ret;
}

Stack *attachSharedMemory(int const shmid, StackAction const action)
{
	Stack * const stack = reinterpret_cast<Stack*>(shmat(shmid, NULL, 0));
	switch (action) {
	case PUSH:
		if (!stack) {
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

void deallocateSharedMemory(int const shmid)
{
	int err;
	if ((err = shmctl(shmid, IPC_RMID, NULL)) == -1) {
		perror("shmctl");
		exit(err);
	}
}

