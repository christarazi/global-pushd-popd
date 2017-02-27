#ifndef HELPER_H
#define HELPER_H

#include <cstdlib>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include "stack.h"

/*
 * The following functions are wrappers for the shared memory system calls.
 * This is for cleaner code and less clutter.
 */
int getSharedMemory(const key_t key, const int flags);
Stack* attachSharedMemory(const int shmid, const StackAction action);
void deallocateSharedMemory(const int shmid);

#endif /* HELPER_H */
