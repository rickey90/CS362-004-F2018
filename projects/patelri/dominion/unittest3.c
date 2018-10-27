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
    int before;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
   

    printf ("TESTING discardCard()\n");

    //test if discarded card is added to the discard pile
    printf("\nTest case: Count of discard pile after discarding card\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.whoseTurn = 0;
    discardCard(0, 0, &G, 0);
    printf("count = %d,  expected = 1\n", G.discardCount[0]);
    compareVal(1, G.discardCount[0]);

    //test hand count after discarding card
    printf("\nTest case: Count of hand after discarding card from hand\n");
    printf("count = %d,  expected = 4\n", G.handCount[0]);
    compareVal(4, G.handCount[0]);

    //test discard count if card from hand is trashed
    printf("\nTest case: Count of discard pile after trashing card\n");
    G.discardCount[0] = 0;
    discardCard(0, 0, &G, 1);
    printf("count = %d,  expected = 0\n", G.discardCount[0]);
    compareVal(0, G.discardCount[0]);

    //test if the supply count for the kingdom cards and victory are not changed 
    printf("\nTest case: Supply of kingdom and victory cards have not changed\n");
    for(int i = 0; i < 10; i++)
    {
        if(k[i] == great_hall || k[i] == gardens) //set before for kingdom or victory card
        {
            before = 8;
        }
        else
        {
            before = 10;
        }

        printf("Supply count for %d card before = %d, after = %d - ", i, before, G.supplyCount[k[i]]);
        compareVal(before, G.supplyCount[k[i]]);
    }

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