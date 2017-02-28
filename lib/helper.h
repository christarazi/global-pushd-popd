#ifndef LIB_HELPER_H_
#define LIB_HELPER_H_

#include <linux/limits.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdlib>

#include "stack.h"

// For ftok()
#define KEYPATHNAME "gpushd"
#define KEYRANDBYTE 'Q'

/*
 * The following functions are wrappers for the shared memory system calls.
 * This is for cleaner code and less clutter.
 */
int getSharedMemory(const key_t key, const int flags);
Stack* attachSharedMemory(const int shmid, const StackAction action);
void deallocateSharedMemory(const int shmid);

#endif  // LIB_HELPER_H_
