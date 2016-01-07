#include <linux/limits.h>

#define MAX_STACK_SIZE 100

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

void stackInitialize(Stack *s)
{
	s->size = 0;
}

ElemStack stackPop(Stack *s)
{
	if (s->size == 0)
	{
		ElemStack elem = {"."};
		return elem;
	}

	ElemStack elem = s->element[s->size - 1];
	s->size--;

	return elem;
}

void stackPush(Stack *s, ElemStack el)
{
	if (s->size < MAX_STACK_SIZE)
	{
		s->element[s->size++] = el;
	}
}

