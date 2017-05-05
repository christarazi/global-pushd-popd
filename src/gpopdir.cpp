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

#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../include/helper.h"
#include "../include/stack.h"

using namespace std;

/*
 * This file is responsible for handling the popping functionality of this
 * utility.
 */

void printUsageHelp(char const *name)
{
	cerr << "Usage: " << name << " [-h | -l | -r]\n" <<
	        "\n" <<
	        "Options:\n" <<
	        " -h            Print this help.\n" <<
	        " -l            List contents on the stack.\n" <<
	        " -r            Deallocate shared memory (stack).\n";
}

int main(int argc, char *argv[])
{
	// Sanity checks arguments
	if (argc > 2) {
		printUsageHelp(argv[0]);
		exit(-1);
	}

	int shmid;
	StackAction const action = POP;

	// Get key for shared memory
	key_t const key = ftok(KEYPATHNAME, KEYRANDBYTE);

	// Process command line arguments
	bool removeFlag = false;
	bool listFlag = false;
	int option = 0;
	while ((option = getopt(argc, argv, "lrh")) != -1) {
		switch (option) {
		case 'l':
			listFlag = true;
			break;
		case 'r':
			removeFlag = true;
			break;
		case 'h':
			printUsageHelp(argv[0]);
			exit(0);
		default:
			printUsageHelp(argv[0]);
			exit(-1);
		}
	}

	// Get shared memory and attach to stack.
	shmid = getSharedMemory(key, IPC_EXCL);
	Stack * const stack = attachSharedMemory(shmid, action);

	if (removeFlag) {
		deallocateSharedMemory(shmid);
		cerr << "shmid " << shmid << " deallocated\n";
		exit(0);
	}

	if (listFlag) {
		stackList(stack);
		exit(0);
	}

	/*
	 * Pop a directory from the stack and print it out.
	 * The gpopdir() function we added to the bashrc (with configure script)
	 * file will take this output and feed it into the cd built-in command.
	 * If the stack is empty, it will just return the current directory (".").
	 */
	ElemStack elem = stackPop(stack);
	cout << elem.path;

	return 0;
}
