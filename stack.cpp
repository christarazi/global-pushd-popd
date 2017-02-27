#include "stack.h"

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
void stackPush(Stack *s, const ElemStack el)
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
	if (s->size > 0)
	{
		std::cout << "Top\n";
		for (int i = s->size - 1; i >= 0; --i)
			std::cout << "\t" << s->element[i].path << "\n";
		std::cout << "Bottom\n";
	}
}
