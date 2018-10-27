#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int fail_count = 0;


void compareVal(int a, int b)
{
	if( a == b)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
		fail_count++;
	}
}

int main() {
    int seed = 1000;
    int numPlayer = 2;
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
   

    printf ("TESTING isGameOver()\n");

    //test if game has ended if no supplies are at 0
    printf("\nTest case: No supplies are empty\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    r = isGameOver(&G);
    printf("return = %d,  expected = 0\n", r);
    compareVal(0, r);

    //test if game has ended if province supply is empty
    printf("\nTest case: Province supply is empty\n");
    G.supplyCount[province] = 0;
    r = isGameOver(&G);
    printf("return = %d,  expected = 1\n", r);
    compareVal(1, r);

    //test if game has ended if 3 of the supplies are at 0
    printf("\nTest case: 3 of the supplies are empty\n");
    G.supplyCount[province] = 10;
    G.supplyCount[adventurer] = 0;
    G.supplyCount[gardens] = 0;
    G.supplyCount[feast] = 0;
    r = isGameOver(&G);
    printf("return = %d,  expected = 1\n", r);
    compareVal(1, r);

    //test if game has ended if 2 of the supplies are at 0
    printf("\nTest case: 2 of the supplies are empty\n");
    G.supplyCount[feast] = 10;
    r = isGameOver(&G);
    printf("return = %d,  expected = 0\n", r);
    compareVal(0, r);

    //test if the other players state is unchanged
    printf("\nTest case: Other players state remain the same as before playing card\n");
    for(int i = 0; i < numPlayer; i++)
    {
        if(i != 0)
        {
            printf("Hand count of player %d before = 0, after = %d - ", i, G.handCount[i]);
            compareVal(0, G.handCount[i]);
            printf("Deck count of plater %d before = 10, after = %d - ", i, G.deckCount[i]);
            compareVal(10, G.deckCount[i]);
        }
    }


    if(!fail_count)
    {
        printf("\nALL TEST CASES PASSED!\n");
    }
    else
    {
        printf("\nFAILED TEST CASES: %d\n", fail_count);
    }

    return 0;
}