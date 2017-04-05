#ifndef INCLUDE_HELPER_H_
#define INCLUDE_HELPER_H_

#include <linux/limits.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdlib>

#include "../include/stack.h"

// For ftok()
#define KEYPATHNAME "gpushd"
#define KEYRANDBYTE 'Q'

/*
 * The following functions are wrappers for the shared memory system calls.
 * This is for cleaner code and less clutter.
 */
int getSharedMemory(key_t const key, int const flags);
Stack *attachSharedMemory(int const shmid, StackAction const action);
void deallocateSharedMemory(int const shmid);

#endif  // INCLUDE_HELPER_H_
