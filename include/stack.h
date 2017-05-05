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

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

#include <linux/limits.h>

#include <iostream>

#define MAX_STACK_SIZE 100

enum StackAction {
	PUSH,
	POP
};

/*
 * This struct represents an element of our stack.
 * Our path is bounded by the Linux path limit.
 * The reason C-style strings are being used instead of std::string is because
 * storing std::string in shared memory is problematic, so it makes more sense
 * to use C-style strings.
 */
struct ElemStack {
	char path[PATH_MAX];
};

// This struct represents our stack where all the directories will be pushed to.
struct Stack {
	ElemStack element[MAX_STACK_SIZE];
	size_t size;
};

void stackInitialize(Stack * const s);

/**
 * Pop an element from the stack and return it.
 * @param s: the instance of the Stack.
 * @return:  return the popped element.
 */
ElemStack stackPop(Stack * const s);

/**
 * Push an element to the stack.
 * @param s: the instance of the Stack.
 * @param el: the element to push to the stack.
 */
void stackPush(Stack * const s, const ElemStack el);

/**
 * List the contents of the stack top to bottom.
 * @param s: the instance of the Stack.
 */
void stackList(Stack * const s);

#endif  // INCLUDE_STACK_H_
