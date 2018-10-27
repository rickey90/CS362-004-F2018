

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
    

    printf ("TESTING buyCard()\n");

    //testing if buy card is called when there is no buys left for the round
    printf("\nTest case: No buys.\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.numBuys = 0;
    G.whoseTurn = 0;
    r = buyCard(adventurer, &G);
    printf("return = %d,  expected = -1\n", r);
    compareVal(-1, r);

    //test if we try to buy a card when we dont have enough coins
    printf("\nTest case: Not enough coins.\n");
    G.numBuys = 1;
    G.coins = 2;
    r = buyCard(adventurer, &G);
    printf("return = %d,  expected = -1\n", r);
    compareVal(-1, r);

    //test if supply of card is out
    printf("\nTest case: No supply of card\n");
    G.coins = 50;
    G.supplyCount[feast] = 0;
    r = buyCard(feast, &G);
    printf("return = %d,  expected = -1\n", r);
    compareVal(-1, r);

    //test supply count
    printf("\nTest case: Supply count after buy\n");
    G.supplyCount[feast] = 10;
    r = buyCard(feast, &G);
    printf("count = %d,  expected = 9\n", G.supplyCount[feast]);
    compareVal(9, G.supplyCount[feast]);

    //test number of buys
    printf("\nTest case: Number of buys after buy\n");
    G.numBuys = 1;
    r = buyCard(feast, &G);
    printf("buys = %d,  expected = 0\n", G.numBuys);
    compareVal(0, G.numBuys);

    //test number of coins 
    printf("\nTest case: Number of coins after buy\n");
    G.numBuys = 5;
    G.coins = 20;
    r = buyCard(adventurer, &G);
    printf("coins = %d,  expected = 14\n", G.coins);
    compareVal(14, G.coins);

    //test discard card count
    printf("\nTest case: Number of discard cards after buy\n");
    G.discardCount[0] = 5;
    G.coins = 20;
    r = buyCard(adventurer, &G);
    printf("count = %d,  expected = 6\n", G.discardCount[0]);
    compareVal(6, G.discardCount[0]);

     //test if bought card has been added to discard pile
    printf("\nTest case: Bought card added to discard pile.\n");
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    G.numBuys = 2;
    G.coins = 20;
    G.whoseTurn = 0;
    r = buyCard(gardens, &G);
    printf("card = %d,  expected = 10\n", G.discard[0][0]);
    compareVal(10, G.discard[0][0]);

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
