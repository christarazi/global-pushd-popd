#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <linux/limits.h>

#define MAX_STACK_SIZE 100

enum StackAction
{
	PUSH,
	POP
};

// This struct represents an element of our stack.
// Our path is bounded by the Linux path limit.
struct ElemStack
{
	char path[PATH_MAX];
};

// This struct represents our stack where all the directories will be pushed to.
struct Stack
{
	ElemStack element[MAX_STACK_SIZE];
	int size;
};

void stackInitialize(Stack *s);

/**
 * Pop an element from the stack and return it.
 * @param s: the instance of the Stack.
 * @return:  return the popped element.
 */
ElemStack stackPop(Stack *s);

/**
 * Push an element to the stack.
 * @param s: the instance of the Stack.
 * @param el: the element to push to the stack.
 */
void stackPush(Stack *s, ElemStack el);

/**
 * List the contents of the stack top to bottom.
 * @param s: the instance of the Stack.
 */
void stackList(Stack *s);

#endif /* STACK_H */
