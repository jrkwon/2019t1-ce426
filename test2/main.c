

/**
 * main.c
 *
 *
 *  stack overflow
 */
int main(void)
{
    int big[5000]; // a big array
    int c = 4;
    big[499] = 2;

    big[4999] = c; // change the last element --> access to the outside of the stack.

    // another test for the 2nd projet
	return 0;
}
