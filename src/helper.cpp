/*
 * Copyright (C) 2017 Chris Tarazi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

