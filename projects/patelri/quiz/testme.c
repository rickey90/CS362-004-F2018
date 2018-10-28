/***************************************************************************************************************************
*Name: Rickey Patel
*Description: Random Testing Quiz
Due: 10-28-18
****************************************************************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// lowest char we need to test for is space which = 32 in ASCII and highest char we need to test for is '}' which = 125
	// we will return a char between that range (32-125)
    return rand() % (125 - 32 + 1) + 32;
}

char *inputString()
{
	//make variable globally accessible 
	static char str[6]; //we need length to be 6, because are test is length 6 which includes the null terminator

	//this will be the pool of chars where the random chars will be chosen
	char target[6] = { 'r', 'e', 's', 't', 'f', 'g' };  //contains all the letters in the target "reset" along with a few other ones
	int i;

	memset(str, '\0', sizeof(str)); //clear out str

	//loop to fill in str with random chars from the target pool
	for (i = 0; i < 5; i++)
	{
		str[i] = target[rand() % 6]; //get a random char from target pool and assign to index i of str
	}

	return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
