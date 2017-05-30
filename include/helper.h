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
