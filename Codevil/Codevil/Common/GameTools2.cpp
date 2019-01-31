#include "all.h"

#define POUND_FIRST_DELAY 17
#define POUND_DELAY 4

int isPound(int counter)
{
	return counter == 1 || POUND_FIRST_DELAY < counter && (counter - POUND_FIRST_DELAY) % POUND_DELAY == 1;
}
