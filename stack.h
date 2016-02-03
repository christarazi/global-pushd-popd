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

/**
 * Pop an element from the stack and return it.
 * @param s: the instance of the Stack.
 * @return:  return the popped element. 
 */
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

/**
 * Push an element to the stack.
 * @param s: the instance of the Stack.
 * @param el: the element to push to the stack.
 */
void stackPush(Stack *s, ElemStack el)
{
	if (s->size < MAX_STACK_SIZE)
	{
		s->element[s->size++] = el;
	}
}

/**
 * List the contents of the stack top to bottom.
 * @param s: the instance of the Stack.
 */
void stackList(Stack *s)
{
	if (s->size != 0)
	{
		printf("Top\n");
		for (int i = s->size - 1; i >= 0; --i)
		{
			printf("\t%s\n", s->element[i].path);
		}
		printf("Bottom\n");
	}
}
